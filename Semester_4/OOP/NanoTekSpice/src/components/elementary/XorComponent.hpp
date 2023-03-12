/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** XorComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class XorComponent : public AComponent {
        public:
            XorComponent(int nbPin = 3);
            ~XorComponent() = default;
            nts::Tristate compute(std::size_t pin);
    };
}
