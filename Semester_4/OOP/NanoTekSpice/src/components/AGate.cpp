/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AGate
*/

#include "AGate.hpp"

nts::AGate::AGate(int nbPin) : AComponent(nbPin)
{
}

nts::Tristate nts::AGate::opposite(nts::Tristate state)
{
    if (state == nts::Tristate::True)
        return nts::Tristate::False;
    if (state == nts::Tristate::False)
        return nts::Tristate::True;
    return nts::Tristate::Undefined;
}