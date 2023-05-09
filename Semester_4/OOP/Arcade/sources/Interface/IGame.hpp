/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** IGame
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <dlfcn.h>
#include <dirent.h>
#define CURRENT_TIME std::chrono::steady_clock::time_point

// Project includes
#include "IData.hpp"

namespace arcade {
    class IGame {
        public:
            virtual ~IGame() = default;
            /**
             * @brief Manage the game
             * @param inputs The inputs from the user
             * @param data The data of the game (live, score, etc...)
             * @param currentTime The current time of the game (in ms)
             * @return If the game is over, return 1, if the game is not over, return 0
             */
            virtual int manage(std::vector<int>, std::shared_ptr<IData>, CURRENT_TIME) = 0;
            /**
             * @brief Get the name of the game
             * @return The name of the game
             */
            virtual std::string getMusic() const = 0;
    };
}
