/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4040
*/

#include "comp4040.hpp"

nts::comp4040::comp4040(int nbPin) : AAdvanced(nbPin)
{
}

void nts::comp4040::simulate(std::size_t tick)
{
    this->_tick++;
}

nts::Tristate nts::comp4040::compute(std::size_t pin)
{
    if (pin == 10 || pin == 11)
        return this->_pins[pin]->link->compute(this->_pins[pin]->linkPin);
    if (this->_pins[11]->link->compute(this->_pins[11]->linkPin) == Tristate::True)
        this->_tick = 0;
    if (this->_pins[10]->link->compute(this->_pins[10]->linkPin) == Tristate::Undefined)
        return Tristate::Undefined;
    int table[16] = {11,
                    5,
                    4,
                    6,
                    3,
                    2,
                    1,
                    -1,
                    0,
                    -1,
                    -1,
                    8,
                    7,
                    9,
                    10,
                    -1};
    int i = (this->_tick >> table[pin -1]) & 1;
    return (i == 1) ? Tristate::True : Tristate::False;
}
