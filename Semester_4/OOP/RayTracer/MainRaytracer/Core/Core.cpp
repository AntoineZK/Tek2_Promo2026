/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#include "Core.hpp"

const std::map<std::string, std::string> RT::Raytracer::_ipList = {
    {"HERE the Name of the computer", "HERE the ip of the computer"},
};

const std::map<std::pair<std::string, int>, void (RT::Raytracer::*)(char **args, int &index)> RT::Raytracer::_authorizedArgList = {
    {{"--help", RT::Raytracer::nbArg::nbArgHelp}, &RT::Raytracer::help},
    {{"-h", RT::Raytracer::nbArg::nbArgHelp}, &RT::Raytracer::help},
    {{"-f", RT::Raytracer::nbArg::nbArgFile}, &RT::Raytracer::setConfigFile},
    {{"--file", RT::Raytracer::nbArg::nbArgFile}, &RT::Raytracer::setConfigFile},
    {{"-s", RT::Raytracer::nbArg::nbArgsave}, &RT::Raytracer::setSaveFile},
    {{"--save", RT::Raytracer::nbArg::nbArgsave}, &RT::Raytracer::setSaveFile},
    {{"--threads", RT::Raytracer::nbArg::nbArgThreads}, &RT::Raytracer::setNbThreads},
    {{"--preview", RT::Raytracer::nbArg::nbArgPreview}, &RT::Raytracer::setPreview},
    {{"--graphics", RT::Raytracer::nbArg::nbArgGraphics}, &RT::Raytracer::setGraphics},
    {{"--sizeX", RT::Raytracer::nbArg::nbArgSizeX}, &RT::Raytracer::setSizeX},
    {{"--sizeY", RT::Raytracer::nbArg::nbArgSizeY}, &RT::Raytracer::setSizeY}
};


const std::map<std::pair<std::string, int>, void (RT::Raytracer::*)(std::vector<std::string> &mesages, int &index, int &socket)> RT::Raytracer::_clientMessageList = {
    {{CLIENT_NEED_WORK, RT::Raytracer::nbArg::nbArgWork}, &RT::Raytracer::sendMoreWork},
    {{RECIVE_PIXEL, RT::Raytracer::nbArg::nbArgPixel}, &RT::Raytracer::recivePixel},
    {{CLIENT_READY, RT::Raytracer::nbArg::nbArgReady}, &RT::Raytracer::clientReady},
    {{WRONG_CONFIG, RT::Raytracer::nbArg::nbArgWrong}, &RT::Raytracer::wrongConfig},
    {{ALL_CLIENT_END, RT::Raytracer::nbArg::nbArgEnd}, &RT::Raytracer::allClientEnd}

};

RT::Raytracer::Raytracer() : _configFile(""), _saveFile(""), _nbThreads(3), _preview(false), _graphics(false), _nbClientReady(0), _nbClientEnd(0), _endOfRender(false), _nbArea(0), _sizeX(0), _sizeY(0)
{
    this->_maxFd = 0;
    // this->
    _server = std::make_unique<RT::Server>();
    _utils = std::make_unique<RT::Utils>();
    _renderingFunction = std::bind(&RT::Raytracer::ppmRender, this);
}

RT::Raytracer::~Raytracer()
{
    if (this->_localClientThread.joinable())
        this->_localClientThread.join();
    if (this->_graphicsThread.joinable())
        this->_graphicsThread.join();
    this->_endOfRender = true;
    if (this->_farmerThread.joinable())
        this->_farmerThread.join();
    if (!this->_graphics) {
        // print the content of _pixelsToRender in the save file
        std::ofstream file(this->_saveFile);
        if (!file.is_open()) {
            std::cerr << "Error: can't open the save file" << std::endl;
            return;
        }
        file << "P3" << std::endl;
        file << std::to_string(this->_sizeX) << " " << std::to_string(this->_sizeY) << std::endl;
        file << "255" << std::endl;
        for (auto &line : this->_pixelsToRender) {
            for (auto &pixel : line) {
                // printf("%d %d %d\n", pixel.r, pixel.g, pixel.b);
                file << std::to_string(pixel.r) << " " << std::to_string(pixel.g) << " " << std::to_string(pixel.b) << std::endl;
            }
        }
    }
    sleep(1);
    this->_server.reset();
    printf("Raytracer destroyed\n");
    this->_utils.reset();
}

void RT::Raytracer::tryConnectToAllExternClient()
{
    int socket = 0;
    for (auto &ip : this->_ipList) {
        socket = this->_server->connectToExternClient(ip.second);
        if (socket != -1) {
            this->_clientListWithSocket.push_back({ip.first, socket});
            std::cout << "Connected to " << ip.first << " on " << ip.second << std::endl;
            this->_server->sendMessage(socket, SEND_NB_THREADS, this->_nbThreads, SEND_CONFIG, this->_configFile);
        }
    }
    this->_nbClient = this->_clientListWithSocket.size();

    if (this->_nbClient == 0) {
        this->startLocalClient();
        usleep(100000);
        this->connectToLocalClient();
    }
}

void RT::Raytracer::initRaytracer()
{
    this->tryConnectToAllExternClient();
}

//! ---- Render function ----

void RT::Raytracer::ppmRender()
{
    std::cout << "ppm render" << std::endl;
    this->startFarmerThread();
}

//* temporary function for the graphic render ----

// static void myFunction(std::vector<std::vector<sf::Color>> &_tab, std::shared_ptr<RT::Sfml::sfml_class> Sfml)
// {
//     srand(time(NULL));
//     int z = 0;
//     while (Sfml->getWindow()) {
//         for (size_t i = 0; i < _tab.size(); i++) {
//             for (size_t j = 0; j < _tab.at(i).size(); j++) {
//                 int r = rand() % 255 + z;
//                 int g = rand() % 255 + z;
//                 int b = rand() % 255 + z;
//                 if (r > 255)
//                     r = 255;
//                 if (g > 255)
//                     g = 255;
//                 if (b > 255)
//                     b = 255;
//                 _tab.at(i)[j] = sf::Color(r, g, b);
//             }
//         }
//         if (z < 255)
//             z += 3;
//     }
// }

// static std::vector<std::vector<sf::Color>> create_r_rab()
// {
//     srand(time(NULL));
//     std::vector<std::vector<sf::Color>> _tab;
//     for (size_t i = 0; i < 1920; i++) {
//         std::vector<sf::Color> tmp;
//         for (size_t j = 0; j < 1080; j++)
//             tmp.push_back(sf::Color(rand() % 255, rand() % 255, rand() % 255));
//         _tab.push_back(tmp);
//     }
//     return (_tab);
// }

//* temporary function for the graphic render ----

// void RT::Raytracer::sfmlRenderPreview()
// {
//     std::cout << "Sfml render preview" << std::endl;
//     int z = 0;
//     while (this->_sfml->getWindow()) {
//         for (size_t i = 0; i < this->_pixelsToRender.size(); i++) {
//             for (size_t j = 0; j < this->_pixelsToRender.at(i).size(); j++) {
//                 int r = rand() % 255 + z;
//                 int g = rand() % 255 + z;
//                 int b = rand() % 255 + z;
//                 if (r > 255)
//                     r = 255;
//                 if (g > 255)
//                     g = 255;
//                 if (b > 255)
//                     b = 255;
//                 // _tab.at(i)[j] = sf::Color(r, g, b);
//             }
//         }
//         if (z < 255)
//             z += 3;
//     }
// }

void RT::Raytracer::sfmlRender()
{
    std::cout << "Sfml render" << std::endl;
    this->startFarmerThread();

    // std::vector<std::vector<sf::Color>> _tab = create_r_rab();
    this->_sfml = std::make_shared<RT::Sfml::sfml_class>(this->_sizeX, this->_sizeY);
    // this->_graphicsThread = std::thread(sfmlRenderPreview, this);
    this->_sfml->display(this->_pixelsToRender);

}

//! ---- Render function ----

//! ---- Run function ----

void RT::Raytracer::run()
{
    this->initRaytracer();

    printf("Start rendering\n");
    this->_renderingFunction();
}

int RT::Raytracer::setMaxFd()
{
    int max_fd = 0;

    for (auto &it : _clientListWithSocket) {
        if (it.second > max_fd)
            max_fd = it.second;
    }
    return max_fd;
}

void RT::Raytracer::initScreenRange()
{
    // printf("initScreenRange\n");
    int nbPixel = this->findSmallestDivider(this->_sizeX, this->_sizeY);
    printf("nbPixel: %d\n", nbPixel);
    printf("nb area: %d\n", (this->_sizeX * this->_sizeY) / (nbPixel * nbPixel));
    // fill the _screenNotTreated
    int x = 0;
    for (int y = 0; y < this->_sizeY;) {
            this->createArea(x, y, nbPixel);
    }
    this->_nbArea = this->_screenNotTreated.size();
}

int RT::Raytracer::findSmallestDivider(int nbX, int nbY)
{
    int i = 8;
    while (i < (nbX < nbY ? nbX : nbY)) {
        if (nbX % i == 0 && nbY % i == 0)
            return i;
        i++;
    }
    printf("Warning: can't find a divider for %d | %d\n", nbX, nbY);
    return (nbX < nbY ? nbX : nbY);
}

void RT::Raytracer::createArea(int &x, int &y, int &nbPixel)
{
    std::pair<std::pair<int, int>, std::pair<int, int>> area;

    area.first.first = x;
    area.first.second = x + (nbPixel - 1);
    area.second.first = y;
    area.second.second = y + (nbPixel - 1);
    this->_screenNotTreated.push_back(area);

    x += nbPixel;
    if (x >= this->_sizeX) {
        x = 0;
        y += nbPixel;
    }
}
