/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** DataGame
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Project includes
#include "../Interface/IData.hpp"
#include "EntityGame.hpp"

namespace arcade {
    class DataGame : public IData {
        public:
            DataGame();
            ~DataGame();
            int getScore() const;
            int getLives() const;
            int getLevel() const;
            std::string getUsername() const;
            IEntity& getEntities(int x, int y);
            std::pair<int, int> getMapSize();

            void setScore(int score);
            void setLives(int lives);
            void setLevel(int level);
            void setUsername(std::string username);
            void setMapSize(std::pair<int, int> size);
            void setEntityAt(std::pair<int, int>, EntityGame &);
        private:
            int score;
            int lives;
            int level;
            std::string username;
            std::vector<std::vector<EntityGame>> entities;
    };
}
