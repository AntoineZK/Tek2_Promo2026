/*
** EPITECH PROJECT, 2023
** test
** File description:
** Observer
*/

#pragma once
#include "IObserver.hpp"
#include "../../MainRaytracer/Include/Include.hpp"

class Observer : public IObserver {
    public:
        void miseAJour(std::vector<double> pos, std::vector<double> rot);
        void miseAJour(std::shared_ptr<RT::Parsing::IObjParser> obj);
        std::shared_ptr<RT::Parsing::IObjParser> getValue();
    private:
        std::shared_ptr<RT::Parsing::IObjParser> m_valeur;
};
