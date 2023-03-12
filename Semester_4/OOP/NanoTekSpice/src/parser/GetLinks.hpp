/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** GetLinks
*/

#pragma once
#include <iostream>

namespace nts {
    class GetLinks {
        public:
            GetLinks(std::string comp1, std::string pin1, std::string comp2, std::string pin2);
            ~GetLinks();
            std::string getComp1(void) { return this->comp1; };
            size_t getPin1(void) { return this->pin1; };
            std::string getComp2(void) { return this->comp2; };
            size_t getPin2(void) { return this->pin2; };

        protected:
        private:
            std::string comp1;
            size_t pin1;
            std::string comp2;
            size_t pin2;
    };
}
