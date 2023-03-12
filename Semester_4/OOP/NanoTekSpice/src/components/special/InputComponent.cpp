/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    return this->_state;
}

void nts::InputComponent::setState(nts::Tristate value)
{
    this->_state = value;
}

nts::Tristate nts::InputComponent::getState()
{
    return this->_state;
}