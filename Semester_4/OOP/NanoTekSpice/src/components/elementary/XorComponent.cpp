/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** XorComponent
*/

#include "XorComponent.hpp"

nts::XorComponent::XorComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::XorComponent::compute(std::size_t pin)
{
    Tristate a = this->_pins[1]->link->compute(this->_pins[1]->linkPin);
    if (pin == 1)
        return a;
    Tristate b = this->_pins[2]->link->compute(this->_pins[2]->linkPin);
    if (pin == 2)
        return b;

    if (a == Tristate::True && b == Tristate::True)
        return Tristate::False;
    if (a == Tristate::False && b == Tristate::False)
        return Tristate::False;
    if (a == Tristate::False && b == Tristate::True)
        return Tristate::True;
    if (a == Tristate::True && b == Tristate::False)
        return Tristate::True;
    return Tristate::Undefined;
}