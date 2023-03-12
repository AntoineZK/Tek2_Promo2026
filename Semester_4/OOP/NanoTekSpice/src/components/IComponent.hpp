/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** IComponent
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>

namespace nts {
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };

    class IComponent {
        public :
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t tick) = 0;
            virtual nts::Tristate compute(std::size_t pin) = 0;
            virtual void setLink (std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
            virtual void setLink2 (std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
    };
}