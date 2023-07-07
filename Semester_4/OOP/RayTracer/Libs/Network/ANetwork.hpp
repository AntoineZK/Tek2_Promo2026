/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ANetwork
*/

#pragma once
#include "INetwork.hpp"

class ANetwork : public INetwork{
    public:
        ANetwork(int port = 8080, std::string ip = "127.0.0.1");
        // ANetwork(int port = 8081, std::string ip = "127.0.0.1");
        ~ANetwork();
        /*
        ** @brief Init the socket
        ** @param ip The ip to connect to set to nullptr if you want to be the server
        ** @param port The port to connect to set to 0 if you want to use the default port
        */
        // void init();
        void init(const char *ip = "", int port = 0);
        std::vector<std::string> receive(int receiverFd);
        void closefd(int fd);
        template <typename... Args>
        void sendMessage(int sendToFd, Args... args) {
            Packet packet;

            packet.serialize('/', args...);
            int sentSocket = ::send(sendToFd, &packet, sizeof(packet), 0);

            if (sentSocket == -1) {
                throw std::runtime_error("\033[1;31mError: send failed\033[0m");
            }
        }
        int getPort() const;
        std::string getIp() const;

    protected:
        struct sockaddr_in _address;
        int _port;
        std::string _ip;
    private:

};

