/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** comp4069
*/

#include "comp4069.hpp"
#include "../elementary/NotComponent.hpp"

nts::comp4069::comp4069(int nbPin) : AGate(nbPin)
{
    this->_comps.resize(6);
    for (int i = 0; i < 6; i++) {
        this->_comps[i] = std::make_unique<nts::NotComponent>();
    }
    this->_comps[0]->setLink(1, *this, 1);
    this->_comps[1]->setLink(1, *this, 3);
    this->_comps[2]->setLink(1, *this, 5);
    this->_comps[3]->setLink(1, *this, 9);
    this->_comps[4]->setLink(1, *this, 11);
    this->_comps[5]->setLink(1, *this, 13);
}

nts::Tristate nts::comp4069::compute(std::size_t pin)
{
    if (pin == 2 || pin == 4 || pin == 6 || pin == 8 || pin == 10 || pin == 12)
        return this->_comps[(pin / 2) - 1]->compute(2);
    return this->_pins[pin]->link->compute(this->_pins[pin]->linkPin);
}