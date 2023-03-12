/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** AComponent
*/

#pragma once
#include "IComponent.hpp"
#include <iostream>
#include <memory>

namespace nts {
    class pin {
        public:
            pin();
            ~pin() = default;
            IComponent *link = nullptr;
            std::size_t linkPin = 0;
    };

    class AComponent : public IComponent {
        public:
            AComponent(int nbPin = 0);
            ~AComponent();
            void simulate(std::size_t tick);
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
            void setLink2(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
            std::unique_ptr<IComponent> getLink(std::size_t pin);
            std::vector<std::unique_ptr<pin>> _pins;
            int _nbPins;
        private:
    };
}

