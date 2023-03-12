/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** ClockComponent
*/

#pragma once
#include "../AComponent.hpp"

namespace nts {
    class ClockComponent : public AComponent {
        public:
            ClockComponent(int nbPin = 1);
            ~ClockComponent() = default;
            void simulate(std::size_t tick);
            nts::Tristate compute(std::size_t pin);
            void setState(nts::Tristate state);
            nts::Tristate getState();
        private:
            nts::Tristate _state = nts::Tristate::Undefined;

    };
}
