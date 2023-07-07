/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Core
*/

#pragma once
#include "../../Include/Include.hpp"
#include "../Parssing/Parser.hpp"
#include "../Network/ClientNetwork.hpp"

#define NB_THREADS_ARG 1
#define NB_VECTOR_ARG 1
#define NB_CONFIG_ARG 1

#define STARTED 1
#define STOPPED 0

#define CLIENT_READY "ready"

namespace RT {
    class Core {
        public:
            Core(bool isExternal = true);
            ~Core();
            int helper(int retValue);
            void initConnection();
            void initializationPattern();
            void strartparssingConfig();

            //* Parsing functions
            std::vector<int> deserializeVector(std::string &data);
            void vectorParsing(std::vector<std::string> &data, int &i);
            void threadParsing(std::vector<std::string> &data, int &i);
            void configParsing(std::vector<std::string> &data, int &i);
            void startParsing(std::vector<std::string> &data, int &i);
            void stopParsing(std::vector<std::string> &data, int &i);

            void run();
            void calculate(int id = 0);

            //* packet parsing functions
            void packetParsing(std::vector<std::string> &data);
        protected:
        private:
            ClientNetwork _client;
            Parser _parser;

            bool _isExternal;

            std::string _configFile;

            int _jobStatus;

            //? the mutex is used to lock the threads
            //? the condition variable is used to pause the threads and resume them when they don't have any work to do
            std::mutex _mtx;
            std::condition_variable _cvCalc;
            std::condition_variable _cvRun;
            std::vector<std::thread> _threads;
            int _nbThreads;
            int _nbThreadsWaiting;

            std::vector<int> tmpList;

            std::thread _importantInfoServer;
            std::mutex _mtxInfo;
            std::condition_variable _cvInfo;
            bool _needInfoWait;

            //? first string is the message second int is the number of argument autorized
            std::map<std::pair<std::string, int>, void (RT::Core::*)(std::vector<std::string> &, int &)> _packetParsing;
    };
}
