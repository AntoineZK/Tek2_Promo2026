/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ClientNetwork
*/

#include "ClientNetwork.hpp"

RT::ClientNetwork::ClientNetwork()
{
    _referenceSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (_referenceSocket == -1) {
        throw std::runtime_error(ERROR("Error: socket failed"));
    }
}

RT::ClientNetwork::~ClientNetwork()
{
    this->closefd(_referenceSocket);
}

int RT::ClientNetwork::getConnectedSocket() const
{
    return _connectedSocket;
}

void RT::ClientNetwork::bindSocket(const char *ip, int port)
{
    this->init(ip, port);
    int _reuse = 1;
    int returnValue = setsockopt(_referenceSocket, SOL_SOCKET, SO_REUSEADDR, &_reuse, sizeof(int));

    if (returnValue == -1) {
        throw std::runtime_error(ERROR("Error: setsockopt failed"));
    }

    if (::bind(_referenceSocket, (struct sockaddr *)&_address, sizeof(_address)) == -1) {
        std::cerr << "Error: bind failed: " << inet_ntoa(_address.sin_addr) << ":" << ntohs(_address.sin_port) << std::endl;
        throw std::runtime_error(ERROR("Error: bind failed"));
    }
}

void RT::ClientNetwork::listenToClient()
{
    if (listen(_referenceSocket, 1) == -1) {
        throw std::runtime_error(ERROR("Error: listen failed"));
    }
}

void RT::ClientNetwork::acceptClient()
{
    _connectedSocket = accept(_referenceSocket, NULL, NULL);

    if (_connectedSocket == -1) {
        throw std::runtime_error(ERROR("Error: accept failed"));
    }
}

void RT::ClientNetwork::setup(const char *ip, int port)
{
    this->bindSocket(ip, port);
    this->listenToClient();
}