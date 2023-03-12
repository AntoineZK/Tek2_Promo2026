/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** comp4069
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4069 : public AGate {
        public:
            comp4069(int nbPin = 14);
            ~comp4069() = default;
            nts::Tristate compute(std::size_t pin);
    };
}