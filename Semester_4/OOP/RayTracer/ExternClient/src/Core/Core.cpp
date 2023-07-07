/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#include "Core.hpp"

const std::map<std::pair<std::string, int>, void (RT::Core::*)(std::vector<std::string> &data, int &index)> RT::Core::_packetParsingFunctions = {
    {{THREADS, RT::Core::PacketParsingArg::THREAD}, &RT::Core::getNbThreads},
    {{AREA, RT::Core::PacketParsingArg::AREA_ARG}, &RT::Core::getArea},
    {{CONFIG, RT::Core::PacketParsingArg::CONFIG_FILE}, &RT::Core::getConfigFile},
    {{START, RT::Core::PacketParsingArg::START_WORK}, &RT::Core::getStartWork},
    {{STOP, RT::Core::PacketParsingArg::STOP_WORK}, &RT::Core::getStopWork},
    {{SCALING, RT::Core::PacketParsingArg::SCALING_ARG}, &RT::Core::getScaling},
    {{END, RT::Core::PacketParsingArg::END_WORK}, &RT::Core::getEndWork}
};

RT::Core::Core(bool isExternal) : _isExternal(isExternal), _scaling(0), _nbThreadsFinished(0), _isStarted(false), _stopWork(false), _resolutionCam({0, 0}), _background(0, 0, 0), _resolution({0, 0}), _rayPerPixel(3), _maxDepth(3)
{
    this->_client = std::make_unique<ClientNetwork>();
    this->_parser = std::make_unique<Parser>();
    this->_utils = std::make_unique<Utils>();
    this->_factory = std::make_unique<Factory>();
    // this->_cameraParser = std::make_unique<RT::Parsing::Camera>();
}

RT::Core::~Core()
{
    for (auto &it : this->_threads)
        if (it.joinable())
            it.join();
    this->_client->sendMessage(this->_client->getConnectedSocket(), END);
    sleep(3);
    this->_client.reset();
    this->_parser.reset();
    this->_utils.reset();
}

void RT::Core::initConnection()
{
    this->_client->setup(nullptr);
    this->_client->acceptClient();

    this->initializationPattern();
}

void RT::Core::initializationPattern()
{
    // first we need to get the first data from the server
    std::vector<std::string> data;
    try {
        data = this->_client->receive(this->_client->getConnectedSocket());
    } catch (const std::exception &e) {
        printf("Error: Server disconnected\n");
        exit(84);
    }

    // then we need to parse it
    this->handlePacket(data);
}

void RT::Core::run()
{
    // lunch the threads
    this->lunchWorkerThreads();

    sleep(5);
    // notify the server that we are ready
    this->_client->sendMessage(this->_client->getConnectedSocket(), I_AM_READY);

    // wait the server to send us to start
    std::vector<std::string> data;
    try {
        data = this->_client->receive(this->_client->getConnectedSocket());
    } catch (const std::exception &e) {
        printf("Error: Server disconnected\n");
        exit(84);
    }
    this->handlePacket(data);

    while (!this->_stopWork) {
        if (!this->_isStarted) {
            printf("Waiting for the server to send us to start\n");
            try {
                data = this->_client->receive(this->_client->getConnectedSocket());
                this->handlePacket(data);
            } catch (const std::exception &e) {
                printf("receive error\n");
            }
            continue;
        }
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_cvMain.wait(lock, [this] {
                // printf("nbThreadsFinished: %d\n", this->_nbThreadsFinished);
                if (this->_nbThreadsFinished != 0) {
                    // printf("ndThreadsFinished :%d\n", this->_nbThreadsFinished);
                    return true;
                }
                // printf("principal thread paused\n");
                return false;
            });
        if (this->_stopWork) {
            lock.unlock();
            break;
        }
        if (!this->_newArea.size()) {
            // printf("no more area to treat\n");
            this->_client->sendMessage(this->_client->getConnectedSocket(), ASK_MORE);
            try {
                data = this->_client->receive(this->_client->getConnectedSocket());
                this->handlePacket(data);
            } catch (const std::exception &e) {
                printf("\033[1;31m![receive error]\033[0m\n");
            }
        } else {
            // printf("new area to treat\n");
            this->_cvThread.notify_one();
            this->_nbThreadsFinished -= 1;
        }
        while (this->_areaFinished.size()) {
            // for (auto &it : this->_areaFinished.back())
                // printf("areaFinished: %d | %d | %d | %d | %d\n", it.first.first, it.first.second, it.second.r, it.second.g, it.second.b);
            this->_client->sendMessage(this->_client->getConnectedSocket(), SEND_PIXEL, this->_areaFinished.back());
            this->_areaFinished.pop_back();
        }
        lock.unlock();
    }
}

void RT::Core::handlePacket(std::vector<std::string> &data)
{
    //? parse all data
    // printf("handlePacket\n");

    int tmpX = 0;
    int isFind = 0;
    for (int x = 0; x != (int) data.size(); ++x) {
        tmpX = x;
        for (auto &packet : this->_packetParsingFunctions) {
            // printf("data[x] = %s | packet.first.first: %s\n", data[x].c_str(), packet.first.first.c_str());
            if (data[x] == packet.first.first) {
                isFind = 1;
                (this->*packet.second)(data, x);
                if (x - tmpX != packet.first.second) {
                    throw std::runtime_error("Error: not enough arguments for the packet");
                    // this->_client->sendMessage(this->_client->getConnectedSocket(), "Error");
                }
            }
        }
        if (!isFind) {
            throw std::runtime_error("Error: command not found");
            // this->_client->sendMessage(this->_client->getConnectedSocket(), "Error");
        }
    }
    // printf("end handlePacket\n");
}

void RT::Core::getNbThreads(std::vector<std::string> &data, int &index)
{
    if (index + 1 >= (int) data.size())
        throw std::runtime_error("Error: not enough arguments for the packet");
    this->_nbThreads = std::stoi(data[index + 1]);
    //! a enlever
    ++index;
}

void RT::Core::getArea(std::vector<std::string> &data, int &index)
{
    // printf("getArea\n");
    if (index + 1 >= (int) data.size())
        throw std::runtime_error("Error: not enough arguments for the packet");
    std::pair<std::pair<int, int>, std::pair<int, int>> tmp = this->deserialiseArea(data[index + 1]);
    this->_newArea.push_back(tmp);
    ++index;
}

std::pair<std::pair<int, int>, std::pair<int, int>> RT::Core::deserialiseArea(std::string &data)
{
    std::pair<int, int> tmpx = {0, 0};
    std::pair<int, int> tmpy = {0, 0};

    std::vector<std::string> tmp = this->_utils->split(data, ',');

    if (tmp.size() != 4)
        throw std::runtime_error("Error: not enough arguments for the packet");

    tmpx.first = std::atoi(tmp[0].c_str());
    tmpx.second = std::atoi(tmp[1].c_str());
    tmpy.first = std::atoi(tmp[2].c_str());
    tmpy.second = std::atoi(tmp[3].c_str());

    return std::make_pair(tmpx, tmpy);
}

void RT::Core::getScaling(std::vector<std::string> &data, int &index)
{
    if (index + 1 >= (int) data.size())
        throw std::runtime_error("Error: not enough arguments for the packet");
    this->_scaling = std::stoi(data[index + 1]);
    //*// todo utiliser la classe pour set le sampling de ray de la scene
    ++index;
}

void RT::Core::getConfigFile(std::vector<std::string> &data, int &index)
{
    if (index + 1 >= (int) data.size())
        throw std::runtime_error("Error: not enough arguments for the packet");
    this->_configFileName = data[index + 1];
    this->loadConfigFile();
    this->_parser->init(this->_configFileContent);

    this->_world = this->_factory->create(this->_parser->getInfo());
    // this->_parser->getInfoCam();
    this->_cameraParser = std::make_unique<RT::Parsing::Camera>(this->_parser->getInfoCam());
    double x = this->_cameraParser->getPosition()[0];
    double y = this->_cameraParser->getPosition()[1];
    double z = this->_cameraParser->getPosition()[2];
    // (x, y, z);
    this->_posCam = Point3D(x, y, z);
    double x_rot = this->_cameraParser->getRotation()[0];
    double y_rot = this->_cameraParser->getRotation()[1];
    double z_rot = this->_cameraParser->getRotation()[2];
    this->_rotCam = Point3D(x_rot, y_rot, z_rot);

    this->_resolutionCam = {this->_cameraParser->getResolution()[0], this->_cameraParser->getResolution()[1]};
    //posCam, rotCam, camera.getFov(), resolutionCam, camera.getMaxbounds(), camera.getRaypix(), camera.getAperture(), camera.getFocal()
    this->_camera = std::make_unique<RT::Camera>(this->_posCam, this->_rotCam, this->_cameraParser->getFov(), this->_resolutionCam, this->_cameraParser->getMaxbounds(), this->_cameraParser->getRaypix(), this->_cameraParser->getAperture(), this->_cameraParser->getFocal());

    double r = this->_cameraParser->getBackground()[0];
    double g = this->_cameraParser->getBackground()[1];
    double b = this->_cameraParser->getBackground()[2];
    this->_background = Color(r, g, b);
    this->_background.toDouble();

    this->_resolution = this->_camera->getResolution();
    this->_rayPerPixel = this->_camera->getRayPerPixel();
    this->_maxDepth = this->_camera->getMaxDepth();
    // this->_parser->getInfo();
    ++index;
}

void RT::Core::getStartWork(std::vector<std::string> &data, int &index)
{
    // printf("getStartWork\n");
    (void) data;
    (void) index;
    this->_isStarted = true;
}

void RT::Core::getStopWork(std::vector<std::string> &data, int &index)
{
    (void) data;
    (void) index;
    this->_isStarted = false;
}

void RT::Core::loadConfigFile()
{
    if (this->_configFileName.empty())
        throw std::runtime_error("Error: no config file specified");
    this->_configFileContent = this->getFileContentByName(this->_configFileName);
}

std::string RT::Core::getFileContentByName(std::string &fileName)
{
    std::ifstream file(fileName);
    std::string content;

    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");
    content.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    file.close();
    return content;
}

void RT::Core::getEndWork (std::vector<std::string> &data, int &index)
{
    (void) data;
    (void) index;
    // printf("getEndWork\n");
    this->_stopWork = true;
    this->_cvThread.notify_all();
    this->_cvMain.notify_all();
}

void RT::Core::workerThread(int id)
{
    //? worker thread
    while (!this->_stopWork) {
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_cvThread.wait(lock, [this ,id] {
                if (this->_stopWork)
                    return true;
                if (!this->_isStarted || this->_newArea.empty()) {
                    // printf("Thread %d is exiting\n", id);
                    this->_nbThreadsFinished++;
                    this->_cvMain.notify_one();
                    return false;
                }
                return true;
            });
        if (this->_stopWork) {
            lock.unlock();
            break;
        }
        // printf("Thread %d is working\n", id);
        std::pair<std::pair<int, int>, std::pair<int, int>> tmp = this->_newArea.back();
        this->_newArea.pop_back();
        lock.unlock();
        this->render(tmp);
    }
    return;
}

void RT::Core::lunchWorkerThreads()
{
    //? lunch the threads
    printf("lunchWorkerThreads :%d\n", this->_nbThreads);
    for (int x = 0; x != this->_nbThreads; ++x) {
        // printf("lunch Worker Thread nb %d\n", x);
        this->_threads.push_back(std::thread(&RT::Core::workerThread, this, x));
    }
}

void RT::Core::render(std::pair<std::pair<int, int>, std::pair<int, int>> &area)
{
    int x = area.first.first;
    int y = area.second.first;
    int xMax = area.first.second;
    int yMax = area.second.second;
    // printf("x: %d, y: %d, xMax: %d, yMax: %d\n", x, y, xMax, yMax);
    // std::vector<std::pair<std::pair<int, int>, pixel_t>> tmp_vector;
    // for (; y <= yMax; ++y) {
    //     for (int i = x; i <= xMax; ++i) {
    //         pixel_t pixel = {rand() % 255, rand() % 255, rand() % 255};
    //         std::pair<int, int> pos = {i, y};
    //         std::pair<std::pair<int, int>, pixel_t> tmp = {pos, pixel};
    //         tmp_vector.push_back(tmp);
    //     }
    // }
    //? render witvh raytracer code
    // printf("%d | %d | %d | %d\n", xMax, this->_resolution.first, yMax, this->_resolution.second);
    std::vector<std::pair<std::pair<int, int>, Color>> tmp_vector = this->calculateRender(y, (yMax + (yMax - y) < this->_resolution.second) ? yMax + 1 : yMax, x, (xMax  + (xMax - x) < this->_resolution.first) ? xMax + 1 : xMax);
    // for (auto &it : tmp_vector) {
    //     std::cout << it.first.first << " " << it.first.second << " " << it.second.getR() << " " << it.second.getG() << " " << it.second.getB() << std::endl;
    // }
    //? insert the calculated data in the _areaFinished vector
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_areaFinished.push_back(tmp_vector);
    lock.unlock();
    this->_cvMain.notify_one();
}

std::vector<std::pair<std::pair<int, int>, Color>> RT::Core::calculateRender(int startY, int endY, int startX, int endX)
{
    // printf("%d | %d | %d | %d\n", startX, endX, startY, endY);
    std::vector<std::pair<std::pair<int, int>, Color>> result;
    for (int y = startY; y <= endY; ++y) {
        std::cerr << "\rScanlines remaining: " << endY - y << ' ' << std::flush;
        for (int x = startX; x < endX; ++x) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < this->_rayPerPixel; ++s) {
                auto u = (x + Random::Utils::random_double()) / (this->_resolution.first - 1);
                auto v = ((this->_resolution.second - y) + Random::Utils::random_double()) / (this->_resolution.second - 1);
                Ray r = this->_camera->get_ray(u, v);
                pixel_color += Calcul::Utils::rayColor(r, this->_background, this->_world, this->_maxDepth);
            }
            pixel_color = Calcul::Utils::applyGamma(pixel_color, 1.0, this->_rayPerPixel);
            pixel_color = Calcul::Utils::toRGB(pixel_color);

            result.push_back({{x, y}, pixel_color});
            // Calcul::Utils::writeColor(std::cout, pixel_color);
        }
    }
    return result;
}