/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

nts::OutputComponent::OutputComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    return this->_pins[1]->link->compute(this->_pins[1]->linkPin);
}
