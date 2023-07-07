/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#include "Core.hpp"

const std::map<std::string, std::string> RT::Raytracer::_list_of_ip_by_name = {
    {"tom appart fix", "192.168.1.32"},
    {"tom appart portable", "192.168.1.19"},
    {"tom tech", "10.18.207.144"},
    {"antoine tech", "10.18.204.130"},
    {"prevot tech", "10.18.208.8"},
    {"raccoon tech", "10.18.207.215"}
};

const std::map<std::string, void (RT::Raytracer::*)(char **, int &)> RT::Raytracer::_arguments = {
    {"-h", &Raytracer::help},
    {"-f", &Raytracer::loadFile},
    {"-s", &Raytracer::saveFile},
    {"--help", &Raytracer::help},
    {"--threads", &Raytracer::getNbThreads},
    {"--file", &Raytracer::loadFile},
    {"--save", &Raytracer::saveFile},
    {"--preview", &Raytracer::activatepreview},
    {"--graphics", &Raytracer::activeSfml},
};

const std::map<std::pair<std::string, int>, void (RT::Raytracer::*)(std::vector<std::string> &, int &, int)> RT::Raytracer::_authorizedMessages = {
    {{CLIENT_READY, CLIENT_NB_ARG}, &Raytracer::clientReady},
    {{CLIENT_FINISHED, CLIENT_FINISHED_NB_ARG}, &Raytracer::clientFinished},
};

RT::Raytracer::Raytracer()
{
    _nbClient = 0;
    _nbThreads = 3;
    _configFilePath = "";
    _saveFilePath = "";
    _configFileContent = "";
    _preview = false;
    _isSfmlActive = false;
    _safeMode = false;
    _max_sd = 0;
    _nbClientReady = 0;

    _renderFunction = std::bind(&Raytracer::ppmRender, this);

    _server = std::make_unique<RT::Server>();
}

RT::Raytracer::~Raytracer()
{
    if (_safeMode) {
        this->_localClientThread.join();
    }
    this->_farmerThread.join();
}

void RT::Raytracer::run()
{
    try {
        this->connectToAllExternClient();
    } catch (const std::exception &e) {
        throw;
    }

    this->farmerThread();
    this->_renderFunction();
}

void RT::Raytracer::errorHandling(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (_arguments.find(av[i]) == _arguments.end()) {
            throw std::runtime_error(ERROR("Error 1: invalid argument"));
        }
        // (this->*_arguments[av[i]])(av, i);
        (this->*_arguments.at(av[i]))(av, i);
    }
    this->settingsVerification();
}

void RT::Raytracer::settingsVerification()
{
    if (_configFilePath == "") {
        throw std::runtime_error(ERROR("Error: no config file specified please specify with entered --file or -f"));
    } else if (_saveFilePath == "" && !_isSfmlActive) {
        throw std::runtime_error(ERROR("Error: no save file specified please specify with entered --save or -s or set Sfml mode with --graphics"));
    } else if (_nbThreads <= 0) {
        throw std::runtime_error(ERROR("Error: invalid number of threads"));
    }
    this->_configFileContent = this->openConfigFile();
}

//! ----functions for arguments handling----

void RT::Raytracer::help(char **av, int &i)
{
    (void) av;
    (void) i;
    std::cout << "USAGE: ./raytracer [OPTIONS]" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "\t-h\t\t\tDisplay this help" << std::endl;
    std::cout << "\t-f [configFile]\t\tSet the config file" << std::endl;
    std::cout << "\t-s [saveFile]\t\tSet the save file" << std::endl;
    std::cout << "\t--help\t\t\tDisplay this help" << std::endl;
    std::cout << "\t--threads [nbThreads]\tSet the number of threads" << std::endl;
    std::cout << "\t--file [configFile]\tSet the config file" << std::endl;
    std::cout << "\t--save [saveFile]\tSet the save file" << std::endl;
    std::cout << "\t--preview\t\tActivate preview mode" << std::endl;
    std::cout << "\t--graphics\t\tActivate Sfml mode" << std::endl;
    exit(0);
}

void RT::Raytracer::getNbThreads(char **av, int &i)
{
    if (av[i + 1] == NULL) {
        throw std::runtime_error(ERROR("Error 2: invalid argument"));
    }
    std::cout << "getNbThreads flag" << av[i + 1] << std::endl;
    i++;
    _nbThreads = atoi(av[i]);
}

std::string RT::Raytracer::openConfigFile()
{

    std::ifstream file(this->_configFilePath);
    std::string str;

    if (!file.is_open()) {
        throw std::runtime_error(ERROR("Error: can't open config file"));
    }

    std::string line;
    while (std::getline(file, line))
        str += line + "\n";
    file.close();

    return str;
}

void RT::Raytracer::loadFile(char **av, int &i)
{
    if (av[i + 1] == NULL) {
        throw std::runtime_error(ERROR("Error 3: invalid argument"));
    }
    std::cout << "loadFile flag" << av[i + 1] << std::endl;
    i++;
    _configFilePath = av[i];
}

void RT::Raytracer::saveFile(char **av, int &i)
{
    if (av[i + 1] == NULL) {
        throw std::runtime_error(ERROR("Error 4: invalid argument"));
    }
    std::cout << "saveFile flag" << av[i + 1] << std::endl;
    i++;
    _saveFilePath = av[i];
}

void RT::Raytracer::activatepreview(char **av, int &i)
{
    (void) av;
    (void) i;
    std::cout << "activatepreview flag" << std::endl;
    _preview = true;
}

void RT::Raytracer::activeSfml(char **av, int &i)
{
    (void) av;
    (void) i;
    std::cout << "activeSfml flag" << std::endl;
    _renderFunction = std::bind(&Raytracer::sfmlRender, this);
    _isSfmlActive = true;
}

//! ----functions for arguments handling----



//! ----function for the std::function----

//* temporary function for the graphic render ----

static void myFunction(std::vector<std::vector<sf::Color>> &_tab, Sfml::sfml_class &Sfml)
{
    srand(time(NULL));
    int z = 0;
    while (Sfml.getWindow()) {
        for (size_t i = 0; i < _tab.size(); i++) {
            for (size_t j = 0; j < _tab.at(i).size(); j++) {
                int r = rand() % 255 + z;
                int g = rand() % 255 + z;
                int b = rand() % 255 + z;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                _tab.at(i)[j] = sf::Color(r, g, b);
            }
        }
        if (z < 255)
            z += 3;
    }
}

static std::vector<std::vector<sf::Color>> create_r_rab()
{
    srand(time(NULL));
    std::vector<std::vector<sf::Color>> _tab;
    for (size_t i = 0; i < 1920; i++) {
        std::vector<sf::Color> tmp;
        for (size_t j = 0; j < 1080; j++)
            tmp.push_back(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        _tab.push_back(tmp);
    }
    return (_tab);
}

//* temporary function for the graphic render ----

void RT::Raytracer::sfmlRender()
{
    printf("sfmlRender\n");
    //SFML
    Sfml::sfml_class Sfml;
    std::vector<std::vector<sf::Color>> _tab = create_r_rab();

    std::thread sfmlThread(myFunction, std::ref(_tab), std::ref(Sfml));

    Sfml.display(_tab);

    //Join the thread
    sfmlThread.join();
    return;
}

void RT::Raytracer::ppmRender()
{
    printf("ppmRender\n");

    return;
}

//! ----function for the std::function----

//! ----function for the network setup----

void RT::Raytracer::connectToAllExternClient()
{
    int newSocket = 0;
    // parse all ip and try to connect to them
    for (auto &it : this->_list_of_ip_by_name) {
        std::cout << "Trying to connect to " << it.first << std::endl;
        newSocket = this->_server->connectToExternClient(it.second);
        if (newSocket != -1) {
            _list_of_ip_by_socket[newSocket] = it.first;
            std::cout << "Connected to " << it.first << std::endl;
            _nbClient++;
        }
    }
    printf("nbClient = %d\n", _nbClient);

    char localMode = 0;
    if (!this->_nbClient) {
        printf("Warning:No client connected, rendering in local mode\nDo you want to render in local mode ? \033[1;32m(y/n)\033[0m\n");
        scanf("%c", &localMode);
        if (localMode == 'n')
            throw std::runtime_error(ERROR("Error: no client connected"));
        _safeMode = true;
        this->startLocalClientThread();
        std::string ip = "127.0.0.1";
        usleep(100000);
        newSocket = this->_server->connectToExternClient(ip);
        if (newSocket != -1) {
            _list_of_ip_by_socket[newSocket] = ip;
            std::cout << "Connected to localhost" << std::endl;
            _nbClient++;
        }
    }

    std::unique_lock<std::mutex> lock(_mutex);
    // parse all connected sockets and send preliminary data (nbThreads, config file)
    for (auto &it : _list_of_ip_by_socket) {
        std::cout << "Sending nbThreads to " << it.second << std::endl;
        this->_server->sendMessage(it.first, "thread",this->_nbThreads, "config", this->_configFileContent);
    }
    lock.unlock();
}

//! ----function for local render----

void RT::Raytracer::startLocalClient()
{
    printf("localRender\n");
    this->_localClient.initConnection();
    this->_localClient.run();
    return;
}

void RT::Raytracer::startLocalClientThread()
{
    printf("localRender thread\n");

    // create thread to start the client on with the method startLocalClient
    this->_localClientThread = std::thread(&Raytracer::startLocalClient, this);

    return;
}

//! ----function for local render----


//! ----function for the farmer thread----

void RT::Raytracer::farmer()
{
    printf("farmer\n");

    // wait for all clients to send us their are ready
    while (this->_nbClientReady != this->_nbClient) {
        printf("waiting ready client\n");
        this->getMessagesWithSelect(true, 1);
    }

    // all clients are ready so open new socket connection for each client for tunneling of the data
    // for (auto &it : _list_of_ip_by_socket) {
    //     std::cout << "Sending tunneling port to " << it.second << std::endl;
    //     this->_server->connectToExternClient(it.second, this->_tunnelingPort);
    // }

    std::unique_lock<std::mutex> lock(this->_mutex);
    // send the first message to all clients
    for (auto &it : _list_of_ip_by_socket) {
        this->_server->sendMessage(it.first, "start");

    }
    lock.unlock();
    while (1) {
        printf("farmer loop\n");
        this->getMessagesWithSelect(true , 1);
    }
    return;
}

void RT::Raytracer::farmerThread()
{
    printf("farmerThread\n");
    // create thread to manage the farme of all the clients
    this->_farmerThread = std::thread(&Raytracer::farmer, this);
    usleep(100000);

    return;
}

//! ----function for the message handler----

void RT::Raytracer::getMessagesWithSelect(bool activeTimeout, int timeS, int timeMs)
{

    // setup fd for select and waiting for client response

    FD_ZERO(&this->_readfds);

    for (auto &it : _list_of_ip_by_socket) {
        FD_SET(it.first, &this->_readfds);
        if (it.first > this->_max_sd)
            this->_max_sd = it.first;
    }

    int returnSelect = 0;
    if (activeTimeout) {
        this->_timeout.tv_sec = timeS;
        this->_timeout.tv_usec = timeMs;
        returnSelect = ::select(this->_max_sd + 1, &this->_readfds, NULL, NULL, &this->_timeout);

        // print if select timeout
        printf("returnSelect = %d\n", returnSelect);
        if (returnSelect == 0) {
            std::cout << "Select timeout" << std::endl;
        }

    } else {
        ::select(this->_max_sd + 1, &this->_readfds, NULL, NULL, NULL);
    }

    for (auto &it : _list_of_ip_by_socket) {
        if (FD_ISSET(it.first, &this->_readfds)) {
            std::vector<std::string> msg = this->_server->receive(it.first);

            for (auto &it2 : msg) {
                std::cout << "Received from " << it.second << ": " << it2 << std::endl;
            }

            this->handleMessages(msg, it.first);
        }
    }
}

void RT::Raytracer::handleMessages(std::vector<std::string> &data, const int socket)
{
    int tmpIndex = 0;
    for (int i = 0; i < (int) data.size(); i++) {
        tmpIndex = i;

        for (auto& [key, value] : this->_authorizedMessages) {
            if (key.first == data[i]) {
                (this->*value)(data, i, socket);

                if (i - tmpIndex != key.second) {
                    throw std::runtime_error(ERROR("Error: invalid number of arguments for " + key.first + " packet"));
                }
                break;
            }
        }
    }
}

//! ----function for the message handler----

//! ----function for the message parser----

void RT::Raytracer::clientReady(std::vector<std::string> &data, int &index, int socket)
{
    (void)data;
    (void)index;
    (void)socket;
    printf("clientReady\n");
    this->_nbClientReady++;
    return;
}

void RT::Raytracer::clientFinished(std::vector<std::string> &data, int &index, int socket)
{
    (void)data;
    (void)index;
    printf("clientFinished\n");
    // todo reassigner du travail et leur dire de dormir si il n'y a plus rien a faire

    // create random int between 0 and 255 and create random iteration of it (c'est temporaire)
    int iteration = rand() % 200 + 1;
    int random = 0;
    std::vector<int> randomVector;
    for (int x = 0; x < iteration; x++) {
        random = rand() % 255;
        randomVector.push_back(random);
    }
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_server->sendMessage(socket, "vector", randomVector);
    lock.unlock();
    return;
}