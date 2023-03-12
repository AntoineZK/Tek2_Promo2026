/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** OrComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class OrComponent : public AComponent {
        public:
            OrComponent(int nbPin = 3);
            ~OrComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
