/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#pragma once
    #include "../Include/Include.hpp"
    #include "Network/ServerNetwork.hpp"
    #include "Graphical/sfml.hpp"
    #include "../../ExternClient/src/Core/Core.hpp"
    #include "Utils/Utils.hpp"

namespace RT {
    class Raytracer {
        public:
            Raytracer();
            ~Raytracer();

            //? function for server initiliazation
            void initRaytracer();
            void tryConnectToAllExternClient();

            //? function for error handling and config
            void errorHandling(int ac, char **av);
            void settingsVerification();
            void help(char **args, int &i);
            void setConfigFile(char **args, int &i);
            void setSaveFile(char **args, int &i);
            void setNbThreads(char **args, int &i);
            void setPreview(char **args, int &i);
            void setGraphics(char **args, int &i);
            void setSizeX(char **args, int &i);
            void setSizeY(char **args, int &i);

            //? function for rendering
            void ppmRender();
            void sfmlRender();
            void sfmlRenderPreview();

            //? run the raytracer
            void run();

            //? message handling
            void getMessagesWithSelect(bool timeout = false, int timeS = 0, int timeMs = 0);
            void handleMessages(std::vector<std::string> &messages, int &socket);
            void sendMoreWork(std::vector<std::string> &message, int &i, int &socket);
            void recivePixel(std::vector<std::string> &message, int &i, int &socket);
            void clientReady(std::vector<std::string> &message, int &i, int &socket);
            void wrongConfig(std::vector<std::string> &message, int &i, int &socket);
            void allClientEnd(std::vector<std::string> &message, int &i, int &socket);

            //? screen split


        protected:
        private:
            //? utils
            std::unique_ptr<RT::Utils> _utils;

            //? server for raytracer
            std::unique_ptr<RT::Server> _server;

            //? map of ip list sorted by name
            static const std::map<std::string, std::string> _ipList;

            //? function for error handling
            static const std::map<std::pair<std::string, int>, void (RT::Raytracer::*)(char **, int &)> _authorizedArgList;

            //? map for client message handling
            static const std::map<std::pair<std::string, int>, void (RT::Raytracer::*)(std::vector<std::string> &, int &, int &)> _clientMessageList;

            //? enum for error nb arg gestion
            enum nbArg {
                nbArgHelp = 0,
                nbArgFile = 1,
                nbArgsave = 1,
                nbArgThreads = 1,
                nbArgPreview = 0,
                nbArgGraphics = 0,
                nbArgSizeX = 1,
                nbArgSizeY = 1,

                nbArgStart = 0,
                nbArgWork = 0,
                nbArgPixel = 1,
                nbArgReady = 0,
                nbArgWrong = 0,
                nbArgEnd = 0
            };

            //? config execution
            std::string _configFile;
            std::string _saveFile;
            int _nbThreads;
            bool _preview;
            bool _graphics;

            //? function for rendering
            std::function<void()> _renderingFunction;
            std::vector<std::vector<pixel_t>> _pixels;

            //? connexion management
            int _nbClient;
            int _nbClientReady;
            int _nbClientEnd;
            std::vector<std::pair<std::string, int>> _clientListWithSocket;

            //? local client
            void startLocalClient();
            void runLocalClient();
            void startLocalClientThread();
            void connectToLocalClient();
            bool _safeMode;
            Core _localClient = Core(false);
            std::thread _localClientThread;

            //? farmer
            void startFarmerThread();
            void farmerThread();
            void waitClient();
            void waitClientStopped();
            void startClient();
            std::thread _farmerThread;

            //? select utils
            int _maxFd;
            fd_set _readFds;
            timeval _timeout;
            int setMaxFd();


            //? mutex and condition variable
            std::mutex _mutex;
            std::condition_variable _cv;

            //? graphical
            std::shared_ptr<Sfml::sfml_class> _sfml;
            std::thread _graphicsThread;
            bool _endOfRender;

            //? vector for screen range avancement
            std::pair<std::pair<int, int>, std::pair<int, int>> getScreenRange(int &index, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenList);
            /*
            ** moveScreenRange
            ** move a screen range from a vector to another
            ** @param screenListsrc: the vector where the screen range is
            ** @param screenListdest: the vector where the screen range will be
            ** @param index: the index of the screen range to move (if -1, the program will find alone with the pos parameter)
            ** @param pos: the position of the pixel this is what it use to find wich node move
            */
            void moveScreenRange(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListsrc, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListdest, int index = -1, std::pair<int, int> pos = {-1, -1});
            void moveAuto(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListsrc, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &screenListdest, std::pair<int, int> pos);
            void initScreenRange();
            int findSmallestDivider(int sizeX, int sizeY);
            void createArea(int &x, int &y, int &sizeBlock);
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> _screenNotTreated;
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> _screenInTreatement;
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> _screenTreated;

            std::vector<std::pair<std::pair<int, int>, pixel_t>> deserializePixel(std::string &message);
            void insertPixel(std::pair<int, int> &pos, pixel_t &pixel);
            void reserveVectorSize();
            std::vector<std::vector<pixel_t>> _pixelsToRender;
            int _nbArea;

            int _sizeX;
            int _sizeY;

    };
}