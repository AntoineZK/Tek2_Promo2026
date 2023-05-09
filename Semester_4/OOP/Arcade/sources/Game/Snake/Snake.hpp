/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Snake
*/

#pragma once
// Project includes
#include "../../Interface/IGame.hpp"
#include "../../Core/EntityGame.hpp"

namespace arcade {
    class Snake : public IGame {
        public:
            Snake();
            ~Snake();
            int manage(std::vector<int> inputs, std::shared_ptr<IData>, CURRENT_TIME);
            std::string getMusic() const;
            void create_fruit();
            int move(int input);
            bool game_over(std::shared_ptr<IData> data);

            void update_snake();
        private:
            int score;
            std::vector<std::vector<EntityGame>> map;
            std::tuple<int, int> pos;
            std::tuple<int, int> tmp_snake;
            std::tuple<int, int> prev_snake;
            std::vector<std::tuple<int, int>> snake;
            int64_t move_time;
            int direction;
            int snake_length;
            int life;
            CURRENT_TIME _currentTime;
            int64_t elapsed_time;
            int tmp_speed;
            int palier;

            std::string path_corps;
            std::string path_haut;
            std::string path_bas;
            std::string path_droite;
            std::string path_gauche;

            int speed;
    };
}
