/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** GetLinks
*/

#include "GetLinks.hpp"

nts::GetLinks::GetLinks(std::string comp1, std::string pin1, std::string comp2, std::string pin2)
{
    this->comp1 = comp1;
    this->pin1 = std::stoi(pin1);
    this->comp2 = comp2;
    this->pin2 = std::stoi(pin2);
}

nts::GetLinks::~GetLinks()
{
}
