/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Raylib
*/

#pragma once
// Standard includes
#include <raylib.h>
#include <map>
#include <vector>
#include <memory>

// Project includes
#include "../../Interface/IGraphical.hpp"

namespace arcade {
    class Raylib : public IGraphical {
        public:
            Raylib();
            ~Raylib();
            std::vector<int> getInputs();
            void display(std::shared_ptr<IData>);
        private:
            std::map<arcade::IEntity::COLOR, Color> colorMap = {
                {arcade::IEntity::COLOR::ARCADE_BLACK, BLACK},
                {arcade::IEntity::COLOR::ARCADE_WHITE, WHITE},
                {arcade::IEntity::COLOR::ARCADE_RED, RED},
                {arcade::IEntity::COLOR::ARCADE_GREEN, GREEN},
                {arcade::IEntity::COLOR::ARCADE_BLUE, BLUE},
                {arcade::IEntity::COLOR::ARCADE_YELLOW, YELLOW},
                {arcade::IEntity::COLOR::ARCADE_MAGENTA, MAGENTA},
                {arcade::IEntity::COLOR::ARCADE_CYAN, ORANGE}
            };
            Camera3D camera;
    };
}
