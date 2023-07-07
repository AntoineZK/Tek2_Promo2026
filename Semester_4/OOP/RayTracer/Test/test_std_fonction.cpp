/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** test_std_fonction
*/

#include <iostream>
#include <functional>

class A {
public:
    A() {
        // Assigner l'une des fonctions à la std::function dans le constructeur
        m_function = std::bind(&A::printB, this);
    }

    void printB() {
        std::cout << "Fonction printB appelée" << std::endl;
    }

    void printC() {
        std::cout << "Fonction printC appelée" << std::endl;
    }

    void getWichFonctionIsSelect() {
        // Vérifier si la std::function contient la fonction printB
        if (m_function.target<std::function<void()>>() == &std::function<void()>(std::bind(&A::printB, this))) {
            std::cout << "La fonction printB est actuellement liée à la std::function" << std::endl;
        }
        // Vérifier si la std::function contient la fonction printC
        else if (m_function.target<std::function<void()>>() == &std::function<void()>(std::bind(&A::printC, this))) {
            std::cout << "La fonction printC est actuellement liée à la std::function" << std::endl;
        }
        else {
            std::cout << "Aucune fonction n'est actuellement liée à la std::function" << std::endl;
        }
    }

private:
    std::function<void()> m_function;
};

int main() {
    A a;
    a.getWichFonctionIsSelect(); // affiche "La fonction printB est actuellement liée à la std::function"
    a.printC();
    // a.m_function = std::bind(&A::printC, &a);
    a.getWichFonctionIsSelect(); // affiche "La fonction printC est actuellement liée à la std::function"
    a.printC();
    return 0;
}
