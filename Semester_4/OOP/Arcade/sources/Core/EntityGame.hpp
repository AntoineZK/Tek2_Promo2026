/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** EntityGame
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "../Interface/IEntity.hpp"

namespace arcade {
    class EntityGame : public IEntity {
        public:
            EntityGame();
            EntityGame(char character, std::string filename, arcade::IEntity::COLOR colorCharacter, arcade::IEntity::COLOR colorBackground, std::pair<int, int> pos, int animation, int haveChange);
            ~EntityGame();
            char getCharacter() const;
            std::string getFilename() const;
            arcade::IEntity::COLOR getColorCharacter() const;
            arcade::IEntity::COLOR getColorBackground() const;
            std::pair<int, int> getPos() const;
            int getAnimation() const;
            int getHaveChange() const;

            void setCharacter(char character);
            void setHaveChange(int haveChange);
            void setFilename(std::string filename);
            void setAnimation(int animation);
            void setColorCharacter(arcade::IEntity::COLOR color);
            void setColorBackground(arcade::IEntity::COLOR color);
            void setPos(std::pair<int, int> pos);
        private:
            char character;
            std::string filename;
            arcade::IEntity::COLOR colorCharacter;
            arcade::IEntity::COLOR colorBackground;
            std::pair<int, int> pos;
            int animation;
            int haveChange;
    };
}
