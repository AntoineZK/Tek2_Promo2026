/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** NotComponent
*/

#include "NotComponent.hpp"

nts::NotComponent::NotComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{
    Tristate a = this->_pins[1]->link->compute(this->_pins[1]->linkPin);
    if (pin == 1)
        return a;

    if (a == Tristate::True)
        return Tristate::False;
    if (a == Tristate::False)
        return Tristate::True;
    return Tristate::Undefined;
}