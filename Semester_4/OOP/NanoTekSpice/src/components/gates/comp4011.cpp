/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** comp4011
*/

#include "comp4011.hpp"
#include "../elementary/AndComponent.hpp"

nts::comp4011::comp4011(int nbPin) : AGate(nbPin)
{
    this->_comps.resize(4);
    for (int i = 0; i < 4; i++) {
        this->_comps[i] = std::make_unique<nts::AndComponent>();
    }
    this->_comps[0]->setLink(1, *this, 1);
    this->_comps[0]->setLink(2, *this, 2);
    this->_comps[1]->setLink(1, *this, 5);
    this->_comps[1]->setLink(2, *this, 6);
    this->_comps[2]->setLink(1, *this, 8);
    this->_comps[2]->setLink(2, *this, 9);
    this->_comps[3]->setLink(1, *this, 12);
    this->_comps[3]->setLink(2, *this, 13);
}

nts::Tristate nts::comp4011::compute(std::size_t pin)
{
    if (pin == 3 || pin == 4)
        return opposite(this->_comps[pin - 3]->compute(3));
    if (pin == 10 || pin == 11)
        return opposite(this->_comps[pin - 8]->compute(3));
    return this->_pins[pin]->link->compute(this->_pins[pin]->linkPin);
}