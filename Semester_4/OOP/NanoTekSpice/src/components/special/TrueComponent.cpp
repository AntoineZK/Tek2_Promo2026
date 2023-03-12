/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

nts::TrueComponent::TrueComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    return nts::Tristate::True;
}
