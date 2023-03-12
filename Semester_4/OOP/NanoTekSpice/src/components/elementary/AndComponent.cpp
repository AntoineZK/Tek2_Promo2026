/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** AndComponent
*/

#include "AndComponent.hpp"

nts::AndComponent::AndComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::AndComponent::compute(std::size_t pin)
{
    Tristate a = this->_pins[1]->link->compute(this->_pins[1]->linkPin);
    if (pin == 1)
        return a;
    Tristate b = this->_pins[2]->link->compute(this->_pins[2]->linkPin);
    if (pin == 2)
        return b;

    if (a == Tristate::True && b == Tristate::True)
        return Tristate::True;
    if (a == Tristate::Undefined && b == Tristate::True)
        return Tristate::Undefined;
    if (a == Tristate::True && b == Tristate::Undefined)
        return Tristate::Undefined;
    if (a == Tristate::Undefined && b == Tristate::Undefined)
        return Tristate::Undefined;
    return Tristate::False;
}
