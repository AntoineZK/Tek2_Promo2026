/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SDL2Audio
*/

#pragma once
#include "../../Interface/IAudio.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace arcade {
    class SDL2Audio : public IAudio {
        public:
            SDL2Audio();
            ~SDL2Audio();
            void playMusic(const std::string &path);
        private:
            Mix_Music *_music;
    };
}