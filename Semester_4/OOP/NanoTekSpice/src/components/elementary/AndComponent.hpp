/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** AndComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent(int nbPin = 3);
            ~AndComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
