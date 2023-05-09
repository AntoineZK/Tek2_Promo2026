/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Pacman
*/

#pragma once
// Project includes
#include "../../Interface/IGame.hpp"
#include "../../Core/DataGame.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "Ghost.hpp"

namespace arcade {

    class Pacman : public IGame {
        public:
            Pacman();
            ~Pacman();
            std::vector<std::string> get_map(std::string path);
            int manage(std::vector<int> inputs, std::shared_ptr<IData>, CURRENT_TIME);
            std::string getMusic() const;
            void move(int input, arcade::Pacman &pac);
            EntityGame add_color(char c, int i, int j);
            void back_ghosts(int i, int64_t time);
            void gcollision(int i, int64_t time);
            void reset();
            std::vector<std::string> map;
            int score;
            int direction;
            int powerup;
            int nb_gums;
            int64_t move_time;
            std::vector<Ghost> ghosts;
            int life = 3;
            int clock_pac_sprite;
        private:
            int pacx;
            int pacy;
            int level = 1;
            CURRENT_TIME _currentTime;
            int64_t elapsed_time;
    };
}
