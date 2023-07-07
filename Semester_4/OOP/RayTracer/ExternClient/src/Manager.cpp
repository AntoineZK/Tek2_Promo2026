/*
** EPITECH PROJECT, 2023
** test
** File description:
** Manager
*/

#include "Manager.hpp"

void Manager::join(std::shared_ptr<IObserver> observer)
{
    m_Observer.push_back(observer);
}

void Manager::join(std::vector<std::shared_ptr<IObserver>> observers)
{
    m_Observer.insert(m_Observer.end(), observers.begin(), observers.end());
}

void Manager::detach(std::shared_ptr<IObserver> observer)
{
    for (auto it = m_Observer.begin(); it != m_Observer.end(); ++it) {
        if (*it == observer) {
            m_Observer.erase(it);
            return;
        }
    }
}

void Manager::detach(std::vector<std::shared_ptr<IObserver>> observers)
{
    for (auto observer : observers) {
        detach(observer);
    }
}

void Manager::setValue(std::vector<double> pos, std::vector<double> rot)
{
    for (auto observer : m_Observer) {
        observer->miseAJour(pos, rot);
    }
}

void Manager::setValue(std::shared_ptr<RT::Parsing::IObjParser> obj)
{
    for (auto observer : m_Observer) {
        observer->miseAJour(obj);
    }
}