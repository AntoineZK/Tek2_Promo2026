/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::FalseComponent::FalseComponent(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    return nts::Tristate::False;
}