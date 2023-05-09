/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SFMLAudio
*/

#include "SFMLAudio.hpp"

extern "C" std::unique_ptr<arcade::IAudio> createAudio()
{
    return std::make_unique<arcade::SFMLAudio>();
}

arcade::SFMLAudio::SFMLAudio()
{
}

arcade::SFMLAudio::~SFMLAudio()
{
}

void arcade::SFMLAudio::playMusic(const std::string &path)
{
    if (!this->_music.openFromFile(path)) {
        std::cerr << "Error while loading music" << std::endl;
        return;
    }
    this->_music.setVolume(100);
    this->_music.setLoop(true);
    this->_music.play();
}
