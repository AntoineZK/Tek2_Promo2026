/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** LocalClient
*/

#include "Core.hpp"

void RT::Raytracer::startLocalClient()
{
    char localMode = 0;
    printf("Warning:No client connected, rendering in local mode\nDo you want to render in local mode ? \033[1;32m(y/n)\033[0m\n");
    ::scanf("%c", &localMode);
    if (localMode == 'n')
        throw std::runtime_error(ERROR("Error: no client connected"));
    _safeMode = true;

    std::cout << "Local client is starting ..." << std::endl;
    this->startLocalClientThread();
}

void RT::Raytracer::runLocalClient()
{
    printf("localRender\n");
    this->_localClient.initConnection();
    this->_localClient.run();
    return;
}

void RT::Raytracer::startLocalClientThread()
{
    printf("localRender thread\n");

    this->_localClientThread = std::thread(&Raytracer::runLocalClient, this);

    return;
}

void RT::Raytracer::connectToLocalClient()
{
    std::string ip = "127.0.0.1";
    int socket = this->_server->connectToExternClient(ip.c_str());

    if (socket == -1)
        throw std::runtime_error(ERROR("Error: no client connected"));
    this->_nbClient = 1;
    this->_clientListWithSocket.push_back({"local", 0});
    std::cout << "Local client connected: " << socket << std::endl;
}
