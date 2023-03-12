/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** TrueComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
        public:
            TrueComponent(int nbpin = 1);
            ~TrueComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
