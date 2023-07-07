/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Network
*/

#pragma once
#include "../../../Libs/Network/ANetwork.hpp"

namespace RT {
    class Server : public ANetwork {
        public:
            // Server(std::string ip = "127.0.0.1", int port = 8081);
            Server();
            ~Server();
            int connectToExternClient(std::string ip, int port = 8080);
            int connexion(int socket, struct sockaddr *address, socklen_t address_len);
            int setSocketToNonBlocking(int &socket);
            int setSocketToBlocking(int &socket);
            int verifyConnectionWithSelect(int &socket);
            int getConnectedSocket(int &socketNb) const;
            size_t getConnectedSocketListSize() const;
        protected:
        private:
            std::vector<int> _connectedSocketList;
    };
}
