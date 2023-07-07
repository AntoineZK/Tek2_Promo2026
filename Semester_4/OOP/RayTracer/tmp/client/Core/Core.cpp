/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#include "Core.hpp"

RT::Core::Core(bool isExternal)
{
    _isExternal = isExternal;
    _configFile = "";
    _nbThreads = 0;
    tmpList.resize(0);
    _nbThreadsWaiting = 0;
    _jobStatus = STOPPED;
    _needInfoWait = false;

    _packetParsing[{"vector", NB_VECTOR_ARG}] = &RT::Core::vectorParsing;
    _packetParsing[{"thread", NB_THREADS_ARG}] = &RT::Core::threadParsing;
    _packetParsing[{"config", NB_CONFIG_ARG}] = &RT::Core::configParsing;
    _packetParsing[{"start", 0}] = &RT::Core::startParsing;
    _packetParsing[{"stop", 0}] = &RT::Core::stopParsing;

}

RT::Core::~Core()
{
}

int RT::Core::helper(int retValue)
{
    std::cout << "Usage: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE: scene configuration." << std::endl;
    return (retValue);
}

void RT::Core::initConnection()
{
    this->_client.setup(nullptr);
    this->_client.acceptClient();

    this->initializationPattern();
}

void RT::Core::initializationPattern()
{
    // first we need to get the config file from the server
    std::vector<std::string> data = this->_client.receive(this->_client.getConnectedSocket());
    // then we need to parse it

    usleep(1000);
    this->packetParsing(data);

    // start the threads
    for (int i = 0; i < this->_nbThreads; i++) {
        this->_threads.push_back(std::thread(&RT::Core::calculate, this, i));
    }
}

void RT::Core::strartparssingConfig()
{
    printf("parsing config file\n%s\n", this->_configFile.c_str());
    // exit(0);
    this->_parser.init(this->_configFile);
    this->_parser.getInfo();
}

void RT::Core::run()
{
    printf("run\n");
    //? c'est ici qu'on va faire le lien entre le sercveur et les threads

    std::unique_lock<std::mutex> lock(this->_mtx);
    //? on va envoyer un message au serveur pour lui dire qu'on est pret
    printf("sending message to server we are ready\n");
    this->_client.sendMessage(this->_client.getConnectedSocket(), CLIENT_READY);
    lock.unlock();

    // attendre que le serveur noud donne le feu vert
    printf("waiting for the server to give us the green light\n");
    std::vector<std::string> data = this->_client.receive(this->_client.getConnectedSocket());
    this->packetParsing(data);

    // lock.unlock();

    while (1) {
        std::unique_lock<std::mutex> lock(this->_mtx);
        // wait if all threads are not waiting
        this->_cvRun.wait(lock, [this] {
            printf("waiting for all threads to be waiting\nsize: %lu\n", this->tmpList.size());
            if (this->tmpList.empty() && this->_jobStatus == STARTED) {
                if (this->_nbThreadsWaiting >= this->_nbThreads)
                    this->_nbThreadsWaiting = 0;
                return true;
            }
            return false;
        });
        printf("all threads are waiting and the list is empty\n");

        // lock the mutex infos to be sure that no other thread is using it
        std::unique_lock<std::mutex> lockInfos(this->_mtxInfo);
        this->_needInfoWait = true;

        // std::unique_lock<std::mutex> lock(this->_mtx);
        // send message to server to ask for more work
        printf("sending message to server to ask for more work\n");
        this->_client.sendMessage(this->_client.getConnectedSocket(), "mores");
        // lock.unlock();

        // receive the work
        std::vector<std::string> data = this->_client.receive(this->_client.getConnectedSocket());

        for (auto it = data.begin(); it != data.end(); it++) {
            printf("data: %s\n", (*it).c_str());
        }

        // parse the work
        this->packetParsing(data);
        lockInfos.unlock();

        // notify all threads if there is work to do
        if (this->tmpList.empty() == false) {
            printf("notify all threads\n");
            this->_cvCalc.notify_all();
        }
        lock.unlock();
    }
}

void RT::Core::calculate(int id)
{
    while (1)
    {
        std::unique_lock<std::mutex> lock(this->_mtx);
        this->_cvCalc.wait(lock, [this, id] {
            if (this->tmpList.empty()) {
                printf("thread %d: waiting...\n", id);
                this->_nbThreadsWaiting++;
                if (this->_nbThreadsWaiting == this->_nbThreads) {
                    printf("thread %d: all threads are waiting\n", id);
                    this->_cvRun.notify_one();
                    return false;
                }
            }
            return !this->tmpList.empty();
        });

        int tmp = this->tmpList.back();
        this->tmpList.pop_back();
        printf("thread %d: %d\n", id, tmp);

        lock.unlock();

        // todo do the work (calculate the image render)
        // todo when the work is finished relock the mutex and do your job
    }
}

std::vector<int> RT::Core::deserializeVector(std::string &data)
{
    std::vector<int> tmp;
    std::stringstream ss(data);
    std::string tmpStr;

    while(std::getline(ss, tmpStr, ',')) {
        tmp.push_back(std::stoi(tmpStr));
    }
    return tmp;
}

void RT::Core::vectorParsing(std::vector<std::string> &data, int &i)
{
    std::cout << "vector parsing" << std::endl;
    if (i + 1 < (int) data.size()) {
        std::vector<int> tmp = this->deserializeVector(data[i + 1]);
        for (int j = 0; j < (int) tmp.size(); j++) {
            this->tmpList.push_back(tmp[j]);
        }
        i++;
    }
    this->_cvCalc.notify_all();
}

void RT::Core::threadParsing(std::vector<std::string> &data, int &i)
{
    if (this->_nbThreads) {
        i++;
        return;
    }

    std::cout << "thread parsing" << std::endl;
    if (i + 1 < (int) data.size()) {
        this->_nbThreads = std::atoi(data[i + 1].c_str());
        if (this->_nbThreads <= 0)
            this->_nbThreads = 3;
        i++;
        this->_threads.reserve(this->_nbThreads);
    }
    printf("nb threads: %d\n", this->_nbThreads);
}

void RT::Core::configParsing(std::vector<std::string> &data, int &i)
{
    std::cout << "config parsing" << std::endl;
    if (i + 1 < (int) data.size()) {
        this->_configFile = data[i + 1];
        i++;
    }

    // then strat the config file parssing
    // if we did this here it's because wee need to update the config file if the server send us a new one
    this->strartparssingConfig();

    tmpList.clear();
}

void RT::Core::startParsing(std::vector<std::string> &data, int &i)
{
    (void) data;
    (void) i;
    std::cout << "start parsing" << std::endl;
    this->_jobStatus = STARTED;
    this->_cvCalc.notify_all();
}

void RT::Core::stopParsing(std::vector<std::string> &data, int &i)
{
    (void) data;
    (void) i;
    std::cout << "stop parsing" << std::endl;
    this->_jobStatus = STOPPED;
}

//! ----packet parsing----

void RT::Core::packetParsing(std::vector<std::string> &data)
{
    // int tmpIndex = 0;

    // print all the data
    for (auto it = data.begin(); it != data.end(); it++) {
        printf("data: %s\n", (*it).c_str());
    }

    for (int i = 0; i < (int) data.size(); i++) {
        // tmpIndex = i;

        for (auto& [key, value] : this->_packetParsing) {
            if (key.first == data[i]) {
                (this->*value)(data, i);

                // if (i - tmpIndex != key.second) {
                //     throw std::runtime_error(ERROR("Error: invalid number of arguments for " + key.first + " packet"));
                // }
                break;
            }
        }

        // if (_packetParsing.first.find(data[i]) != _packetParsing.end())
        //     (this->*_packetParsing[data[i]])(data, i);
    }
}