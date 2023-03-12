/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** comp4081
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4081 : public AGate {
        public:
            comp4081(int nbPin = 14);
            ~comp4081() = default;
            nts::Tristate compute(std::size_t pin);
    };
}