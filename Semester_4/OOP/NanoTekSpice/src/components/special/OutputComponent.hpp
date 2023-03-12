/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** OutputComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class OutputComponent : public AComponent {
        public:
            OutputComponent(int nbPin = 1);
            ~OutputComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
