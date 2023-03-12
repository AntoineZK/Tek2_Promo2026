/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-tekspice-antoine.khalidy
** File description:
** AAdvanced
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class AAdvanced : public AComponent {
        public:
            AAdvanced(int nbPin = 14);
            ~AAdvanced() = default;
    };
}
