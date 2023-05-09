/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** IAudio
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>

namespace arcade {
    class IAudio {
        public:
            virtual ~IAudio() = default;
            /**
             * @brief Play a music in background with the library that have been chosen
             * @param path The path of the music
             */
            virtual void playMusic(const std::string &path) = 0;

        protected:
        private:
    };
}
