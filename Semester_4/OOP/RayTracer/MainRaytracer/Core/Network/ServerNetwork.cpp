/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ServerNetwork
*/

#include "ServerNetwork.hpp"

RT::Server::Server()
{
}

RT::Server::~Server()
{
    printf("Server destructor\n");
    for (auto &it : _connectedSocketList)
        close(it);
}

int RT::Server::getConnectedSocket(int &socketNb) const
{
    if (socketNb < 0 || socketNb >= (int) _connectedSocketList.size())
        return -1;
    return _connectedSocketList[socketNb];
}

int RT::Server::connectToExternClient(std::string ip, int port)
{
    this->init(ip.c_str(), port);

    int newSocket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (newSocket == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        exit(84);
    }

    int selectReturn = 0;

    this->setSocketToNonBlocking(newSocket);

    if (this->connexion(newSocket, (struct sockaddr *)&_address, sizeof(_address)) == -1) {
        if (errno == EINPROGRESS || errno == EWOULDBLOCK) {
            selectReturn = this->verifyConnectionWithSelect(newSocket);
        } else {
            printf("Error connecting %d - %s\n", errno, strerror(errno));
            perror("connect");
            close(newSocket);
            return -1;
        }
    }
    if (selectReturn == -1) {
        std::cerr << "WARNING: connection failed" << std::endl;
        close(newSocket);
        return -1;
    }
    this->setSocketToBlocking(newSocket);

    std::cout << "Connected to client: " << newSocket << std::endl;
    _connectedSocketList.push_back(newSocket);

    return newSocket;
}

int RT::Server::connexion(int socket, struct sockaddr *address, socklen_t address_len)
{
    if (socket == -1) {
        throw std::runtime_error("Error : Wrong socket");

    }
    if (address == NULL || !address_len) {
        throw std::runtime_error("Error : Wrong address");
    }

    return ::connect(socket, address, address_len);
}

size_t RT::Server::getConnectedSocketListSize() const
{
    return _connectedSocketList.size();
}

int RT::Server::setSocketToNonBlocking(int &socket)
{
    if (socket == -1) {
        throw std::runtime_error("Error : Wrong socket");
    }
    // récupération des flags existants
    int flags = ::fcntl(socket, F_GETFL, 0);

    if (flags == -1) {
        throw std::runtime_error("Error : can't get socket flags");
    }

    // ajout du flag O_NONBLOCK
    int result = ::fcntl(socket, F_SETFL, flags | O_NONBLOCK);

    if (result == -1) {
        throw std::runtime_error("Error :can't set socket to non blocking");
    }

    return 0;
}

int RT::Server::setSocketToBlocking(int &socket)
{
    if (socket == -1) {
        throw std::runtime_error("Error : Wrong socket");
    }
    // récupération des flags existants
    int flags = ::fcntl(socket, F_GETFL, 0);

    if (flags == -1) {
        throw std::runtime_error("Error 1: can't get socket flags");
    }

    // ajout du flag O_NONBLOCK
    int result = ::fcntl(socket, F_SETFL, flags & ~O_NONBLOCK);

    if (result == -1) {
        throw std::runtime_error("Error :can't set socket to non blocking");
    }

    return 0;
}

int RT::Server::verifyConnectionWithSelect(int &newSocket)
{
    if (newSocket == -1) {
        throw std::runtime_error("Error : Wrong socket");
    }

    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(newSocket, &write_fds);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int select_result = ::select(newSocket+1, NULL, &write_fds, NULL, &timeout);

    if (select_result == -1) {
        perror("select");
        close(newSocket);
        return -1;
    }
    else if (select_result == 0) {
        fprintf(stderr, "select timeout\n");
        close(newSocket);
        return -1;
    }else {
        int optval;
        socklen_t optlen = sizeof(optval);

        if (::getsockopt(newSocket, SOL_SOCKET, SO_ERROR, &optval, &optlen) == -1) {
            perror("getsockopt");
            close(newSocket);
            return -1;
        }
        else if (optval != 0) {
            errno = optval;
            printf("Error in delayed connection() %d - %s\n", errno, strerror(errno));
            perror("connect");
            close(newSocket);
            return -1;
        }
    }
    return 0;
}
