/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** IData
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>

// Project includes
#include "IEntity.hpp"
#include "../Core/EntityGame.hpp"

namespace arcade {
    /**
     * @brief This class is used to store the data of the game (score, lives, etc...)
     * moreover, it is used to store the map of the game (vector of IEntity) who will be used to display the game
     */
    class IData {
        public:
            virtual ~IData() = default;
            virtual int getScore() const = 0;
            virtual int getLives() const = 0;
            virtual int getLevel() const = 0;
            virtual std::string getUsername() const = 0;
            virtual IEntity& getEntities(int, int) = 0;
            virtual std::pair<int, int> getMapSize() = 0;

            virtual void setScore(int score) = 0;
            virtual void setLives(int lives) = 0;
            virtual void setLevel(int level) = 0;
            virtual void setUsername(std::string username) = 0;
            virtual void setMapSize(std::pair<int, int>) = 0;
            virtual void setEntityAt(std::pair<int, int>, EntityGame &) = 0;
    };
}
