/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** GetChipsets
*/

#pragma once
#include <iostream>

namespace nts {
    class GetChipsets {
        public:
            GetChipsets(std::string comp, std::string name);
            ~GetChipsets();
            std::string getComp(void) { return this->comp; };
            std::string getName(void) { return this->name; };

        protected:
            std::string comp;
            std::string name;
        private:
    };
}
