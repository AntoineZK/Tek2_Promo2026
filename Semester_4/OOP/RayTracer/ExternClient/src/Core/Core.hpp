/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#pragma once
    #include "../../../MainRaytracer/Include/Include.hpp"
    #include "../Raytracing/Camera.hpp"
    #include "../Factory.hpp"
    #include "../Raytracing/Primitives/PrimitivesList.hpp"
    #include "../Raytracing/Math/Vector3D.hpp"
    #include "../Raytracing/Utils/Utils.hpp"
    #include "../Raytracing/Include.hpp"
    #include "../Parssing/Parser.hpp"
    #include "../Network/ClientNetwork.hpp"
    #include "../../../MainRaytracer/Core/Utils/Utils.hpp"


namespace RT {
    class Core {
        public:
            Core(bool isExternal = true);
            ~Core();
            void initConnection();
            void initializationPattern();

            void run();

            //* Parsing functions
            void getNbThreads(std::vector<std::string> &data, int &i);
            void getArea(std::vector<std::string> &data, int &i);
            std::pair<std::pair<int, int>, std::pair<int, int>> deserialiseArea(std::string &data);
            void getScaling(std::vector<std::string> &data, int &i);
            void getStartWork(std::vector<std::string> &data, int &i);
            void getStopWork(std::vector<std::string> &data, int &i);
            void getConfigFile(std::vector<std::string> &data, int &i);
            void getEndWork(std::vector<std::string> &data, int &i);

            void loadConfigFile();
            std::string getFileContentByName(std::string &filename);

            void lunchWorkerThreads();
            void workerThread(int id);

            void render(std::pair<std::pair<int, int>, std::pair<int, int>> &area);
            std::vector<std::pair<std::pair<int, int>, Color>> calculateRender(int startY, int endY, int startX, int endX);

        protected:
        private:
            std::unique_ptr<ClientNetwork> _client;
            std::unique_ptr<Parser> _parser;
            std::unique_ptr<Utils> _utils;

            bool _isExternal;

            void handlePacket(std::vector<std::string> &data);
            static const std::map<std::pair<std::string, int>, void (RT::Core::*)(std::vector<std::string> &, int &)> _packetParsingFunctions;
            enum PacketParsingArg {
                AREA_ARG = 1,
                THREAD = 1,
                CONFIG_FILE = 1,
                START_WORK = 0,
                STOP_WORK = 0,
                SCALING_ARG = 1,
                END_WORK = 0
            };

            int _nbThreads;

            //? first pair is the start x and end x and the second pair is the start y and end y
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> _newArea;
            // std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>, std::pair<int, int>> _newArea;

            //? pair is for x and y of the pixel
            std::vector<std::vector<std::pair<std::pair<int, int>, Color>>> _areaFinished;

            int _scaling;

            std::string _configFileName;
            std::string _configFileContent;

            std::vector<std::thread> _threads;
            int _nbThreadsFinished;
            std::mutex _mutex;
            std::condition_variable _cvThread;
            std::condition_variable _cvMain;

            bool _isStarted;
            bool _stopWork;

            //? scene
            std::unique_ptr<RT::Factory> _factory;
            std::unique_ptr<RT::Camera> _camera;
            std::unique_ptr<RT::Parsing::Camera> _cameraParser;
            PrimitivesList _world;
            Point3D _posCam;
            Point3D _rotCam;
            std::pair<int, int> _resolutionCam;
            Color _background;
            std::pair<int, int> _resolution;
            int _rayPerPixel;
            int _maxDepth;
    };
}
