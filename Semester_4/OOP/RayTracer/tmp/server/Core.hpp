/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#pragma once
    #include "../Include/Include.hpp"
    #include "Network/ServerNetwork.hpp"
    #include "Graphical/Sfml.hpp"
    #include "../../ExternClient/src/Core/Core.hpp"

#define CLIENT_READY "ready"
#define CLIENT_NB_ARG 0 //? 1 the number f the socket client

#define CLIENT_FINISHED "mores"
#define CLIENT_FINISHED_NB_ARG 0 //? 1 the number of the socket client

typedef struct pixel_s {
    int r;
    int g;
    int b;
} pixel_t;

namespace RT {
    class Raytracer {
        public:
            Raytracer();
            ~Raytracer();
            void run();
            void errorHandling(int ac, char **av);
            void settingsVerification();

            //* function for arguments
            void getNbThreads(char **av, int &i);
            void help(char **av, int &i);
            void loadFile(char **av, int &i);
            void saveFile(char **av, int &i);
            void activatepreview(char **av, int &i);
            void activeSfml(char **av, int &i);

            std::string openConfigFile();

            //* function for network setup
            void connectToAllExternClient();

            //* function for local render
            void startLocalClientThread();
            void startLocalClient();

            //* function for std::fonction
            void sfmlRender();
            void ppmRender();

            //* farmer thread (the thread wo will send the work to the client)
            void farmerThread();
            void farmer();

            //* function for message handling
            void getMessagesWithSelect(bool activeTimeout = false, int timeS = 0, int timeMs = 0);
            void handleMessages(std::vector<std::string> &data, const int socket);

            //* function for message parsing
            void clientReady(std::vector<std::string> &data, int &i, int socket);
            void clientFinished(std::vector<std::string> &data, int &i, int socket);

            // static const std::map<std::string, void (Raytracer::*)(char **, int &)> _arguments;

        protected:
        private:
            std::unique_ptr<RT::Server> _server;

            //? list of ip by name
            static const std::map<std::string, std::string> _list_of_ip_by_name;
            std::map<int, std::string> _list_of_ip_by_socket;
            int _nbClient;
            int _nbClientReady;

            //? autorized arguments for the program
            static const std::map<std::string, void (Raytracer::*)(char **, int &)> _arguments;

            //? config infos
            int _nbThreads;
            std::string _configFilePath;
            std::string _configFileContent;
            std::string _saveFilePath;
            bool _preview;

            //? safe mode is used when no client is connected
            bool _safeMode;
            Core _localClient = Core(false);
            std::thread _localClientThread;

            //? std function pointing to the class functions rendering
            std::function<void ()> _renderFunction;
            int _isSfmlActive;

            //? farmer thread
            std::mutex _mutex;
            std::thread _farmerThread;

            //? map for message handling
            //? first string is the message second int is the number of argument autorized
            static const std::map<std::pair<std::string, int>, void (Raytracer::*)(std::vector<std::string> &, int &, int)> _authorizedMessages;
            fd_set _readfds;
            int _max_sd;
            timeval _timeout;
    };
}
