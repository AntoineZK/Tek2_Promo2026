/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** AComponent
*/

#include "AComponent.hpp"
// Factory avec lambda
nts::AComponent::AComponent(int nbPin)
{
    this->_nbPins = nbPin;
    this->_pins.resize(this->_nbPins + 1);
    for (int i = 1; i <= this->_nbPins; i++)
        this->_pins[i] = std::make_unique<nts::pin>();
}

nts::AComponent::~AComponent()
{
}

void nts::AComponent::simulate(std::size_t tick)
{
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    this->_pins[pin]->link = &other;
    this->_pins[pin]->linkPin = otherPin;
    other.setLink2(otherPin, *this, pin);
}

void nts::AComponent::setLink2(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    this->_pins[pin]->link = &other;
    this->_pins[pin]->linkPin = otherPin;
}

std::unique_ptr<nts::IComponent> nts::AComponent::getLink(std::size_t pin)
{
    return nullptr;
}

nts::pin::pin()
{
}
