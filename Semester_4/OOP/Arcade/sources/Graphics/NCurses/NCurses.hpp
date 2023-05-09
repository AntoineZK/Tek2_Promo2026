/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** NCurses
*/

#pragma once
// Standard includes
#include <ncurses.h>
#include <map>

// Project includes
#include "../../Interface/IGraphical.hpp"

namespace arcade {
    class NCurses : public IGraphical {
        public:
            NCurses();
            ~NCurses();
            std::vector<int> getInputs();
            void display(std::shared_ptr<IData>);
        private:
            std::map<std::pair<IEntity::COLOR, IEntity::COLOR>, int> colorMap;
    };
}
