/*
** EPITECH PROJECT, 2023
** test
** File description:
** Observer
*/

#pragma once
#include "Parssing/IObjParser.hpp"

class IObserver {
    public:
        virtual void miseAJour(std::vector<double> pos, std::vector<double> rot) = 0;
        virtual void miseAJour(std::shared_ptr<RT::Parsing::IObjParser>) = 0;
        virtual std::shared_ptr<RT::Parsing::IObjParser> getValue() = 0;
};
