/*
** EPITECH PROJECT, 2023
** test
** File description:
** Observer
*/

#include "Observer.hpp"

void Observer::miseAJour(std::vector<double> pos, std::vector<double> rot)
{
    m_valeur->add(pos, rot);
}

void Observer::miseAJour(std::shared_ptr<RT::Parsing::IObjParser> obj)
{
    m_valeur = obj;
}

std::shared_ptr<RT::Parsing::IObjParser> Observer::getValue()
{
    return m_valeur;
}