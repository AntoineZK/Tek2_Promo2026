/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** FalseComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent {
        public:
            FalseComponent(int nbPin = 1);
            ~FalseComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
