/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ClientNetwork
*/

#pragma once
#include "../../../Libs/Network/ANetwork.hpp"
#include "../../../MainRaytracer/Include/Include.hpp"
#include <map>

namespace RT {
    class ClientNetwork : public ANetwork {
        public:
            ClientNetwork();
            ~ClientNetwork();
            /*
            ** @brief Setup the server socket and bind it
            ** @param ip The ip to connect to set to nullptr if you want to be the server
            ** @param port The port to connect to set to 0 if you want to use the default port
            */
            void setup(const char *ip = "", int port = 0);
            // void setup();
            void acceptClient();
            // int getConnectedSocket(int socketNb) const;
            int getConnectedSocket() const;
        protected:
        private:
            int _referenceSocket;
            int _connectedSocket;
            // void bindSocket();
            void bindSocket(const char *ip = "", int port = 0);
            void listenToClient();

            // std::map<std::string, void (ClientNetwork::*)(std::vector<std::string> &, int &)> _functionMap;

    };
}