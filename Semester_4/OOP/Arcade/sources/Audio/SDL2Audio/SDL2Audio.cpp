/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SDL2Audio
*/

#include "SDL2Audio.hpp"

extern "C" std::unique_ptr<arcade::IAudio> createAudio()
{
    return std::make_unique<arcade::SDL2Audio>();
}

arcade::SDL2Audio::SDL2Audio()
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error initializing SDL audio: " << SDL_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
    }
}

arcade::SDL2Audio::~SDL2Audio()
{
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void arcade::SDL2Audio::playMusic(const std::string &path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(music, -1);
}
