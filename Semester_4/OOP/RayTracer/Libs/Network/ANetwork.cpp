/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ANetwork
*/

#include "ANetwork.hpp"

ANetwork::ANetwork(int port, std::string ip)
{
    _port = port;
    _ip = ip;
}

ANetwork::~ANetwork()
{
}

// void ANetwork::init()
void ANetwork::init(const char *ip, int port)
{
    _address.sin_family = AF_INET;
    _address.sin_port = htons(port != _port && port != 0 ? port : _port);
    (!ip) ? printf("setup anny\n") : ((!strcmp(ip, "")) ? printf("default value: %s\n", _ip.c_str()) : printf("setup ip: %s\n", ip));
    _address.sin_addr.s_addr = (!ip) ? htonl(INADDR_ANY) : ((!strcmp(ip, "")) ? inet_addr(_ip.c_str()) : inet_addr(ip));
}

std::vector<std::string> ANetwork::receive(int receiverFd)
{
    Packet packet;
    // printf("recv socket: %d\n", receiverFd);
    int receivedSocket = 0;
    // int first = 1;

    while (receivedSocket != sizeof(packet)) {
        int sizeRead = read(receiverFd, (void *) &packet + receivedSocket, sizeof(packet) - receivedSocket);
        if (sizeRead <= 0) {
            throw std::runtime_error("\033[1;31mError: receive failed\033[0m");
        } else {
            receivedSocket += sizeRead;
        }
    }

    // printf("received socket size : %d\n", receivedSocket);
    // printf("------------------------------------------\nreceived packet: |%s|\n-------------------------------------\n", packet.getBody().c_str());

    return packet.deserialize();
}

void ANetwork::closefd(int fd)
{
    printf(" lcose socket: %d\n", fd);
    close(fd);
}

int ANetwork::getPort() const
{
    return _port;
}

std::string ANetwork::getIp() const
{
    return _ip;
}
