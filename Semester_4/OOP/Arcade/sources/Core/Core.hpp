/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Core
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <dlfcn.h>
#include <chrono>
#include <filesystem>

// Project includes
#include "../Interface/IGame.hpp"
#include "../Interface/IGraphical.hpp"
#include "../Interface/IData.hpp"
#include "../Interface/IAudio.hpp"
#include "../Core/DataGame.hpp"
#include "../Core/DLLoader.hpp"

namespace arcade {
    class Core {
        public:
            enum IN {MENU, GAME};
            Core();
            ~Core();
            /**
             * @brief Get the Inputs from the user
             * @param retVal
             * @return the return value of the helper
             */
            int helper(int retVal);
            /**
             * @brief Run the game
             * @param lib The graphical library to use
             */
            void runGame(char *lib);
            /**
             * @brief Load the libraries
             */
            void loadLibs();
            /**
             * @brief Get the list of the all libraries
             * @return A vector of string that represent the all libraries
             */
            std::vector<std::string> getLibs();
            /**
             * @brief Get the list of the actual graphical libraries
             * @return A vector of string that represent the actual graphical libraries
             */
            void getActualLib(char *lib);
            /**
             * @brief the main loop of the game
             */
            int manageCore(std::vector<int> inputs);
            /**
             * @brief Perform the reset of the game
             */
            void resetGame();
            /**
             * @brief Perform the return to the menu
             */
            void returnToMenu();
            /**
             * @brief Perform the next graphical library
             */
            void nextGraphicalLib();
            /**
             * @brief Perform the next Audio library
             */
            void nextAudioLib();
            /**
             * @brief Perform the next game
             */
            void nextGame();
            void initCore(char *lib);

            class CoreException : public std::exception {
                public:
                    CoreException(std::string const &message) : _message(message) {};
                    const char *what() const noexcept { return _message.c_str(); };
                private:
                    std::string _message;
            };
        private:
            std::shared_ptr<IData> data;
            std::vector<std::string> gameLibs;
            std::vector<std::string> graphicalLibs;
            std::vector<std::string> audioLibs;
            int actualLib;
            int actualGame;
            int actualAudio;
            std::unique_ptr<DLLoader> loaderGraphical;
            std::unique_ptr<DLLoader> loaderGame;
            std::unique_ptr<DLLoader> loaderAudio;
            std::unique_ptr<IGraphical> graphicalLib;
            std::unique_ptr<IGame> gameLib;
            std::unique_ptr<IAudio> audioLib;
            IN in_value;
    };
}
