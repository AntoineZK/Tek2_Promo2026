/*
** EPITECH PROJECT, 2023
** test
** File description:
** Manager
*/

#pragma once
#include "../../MainRaytracer/Include/Include.hpp"
#include "IObserver.hpp"

class Manager {
    public:
        void join(std::shared_ptr<IObserver> observateur);
        void join(std::vector<std::shared_ptr<IObserver>> observateurs);
        void detach(std::shared_ptr<IObserver> observateur);
        void detach(std::vector<std::shared_ptr<IObserver>> observateurs);
        void setValue(std::vector<double> pos, std::vector<double> rot);
        void setValue(std::shared_ptr<RT::Parsing::IObjParser> obj);
    private:
        std::vector<std::shared_ptr<IObserver>> m_Observer;

};
