/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** SFMLAudio
*/

#pragma once
#include "../../Interface/IAudio.hpp"
#include <SFML/Audio.hpp>

namespace arcade {
    class SFMLAudio : public IAudio {
        public:
            SFMLAudio();
            ~SFMLAudio();
            void playMusic(const std::string &path);
        private:
            sf::Music _music;
    };
}
