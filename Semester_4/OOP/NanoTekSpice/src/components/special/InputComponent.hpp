/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** InputComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent {
        public:
            InputComponent(int nbPin = 1);
            ~InputComponent() = default;
            nts::Tristate compute(std::size_t pin);
            void setState(nts::Tristate state);
            nts::Tristate getState();
        private:
            nts::Tristate _state = nts::Tristate::Undefined;
    };
}
