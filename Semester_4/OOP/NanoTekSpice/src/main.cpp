/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** main
*/

#include <iostream>
#include <memory>
#include "components/elementary/AndComponent.hpp"
#include "components/elementary/NotComponent.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/special/TrueComponent.hpp"
#include "parser/Parser.hpp"
#include "Circuit.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (nts::Circuit::helper(84));
    if (av[1] == std::string("-h"))
        return (nts::Circuit::helper(0));
    nts::Parser parser(av[1]);
    nts::Circuit circuit(parser);
    nts::Circuit::ntsLoop(parser, circuit);
    return (0);
}
