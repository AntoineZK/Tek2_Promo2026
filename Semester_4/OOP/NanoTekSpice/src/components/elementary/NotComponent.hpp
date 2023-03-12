/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** NotComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent(int nbPin = 2);
            ~NotComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
