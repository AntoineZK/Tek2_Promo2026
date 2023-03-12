/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent(int nbPin) : AComponent(nbPin)
{
}

void nts::ClockComponent::simulate(std::size_t tick)
{
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    return this->_state;
}

void nts::ClockComponent::setState(nts::Tristate state)
{
    this->_state = state;
}

nts::Tristate nts::ClockComponent::getState()
{
    return this->_state;
}