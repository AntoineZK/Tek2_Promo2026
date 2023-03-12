/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** comp4071
*/

#pragma once
#include "../AGate.hpp"

namespace nts {
    class comp4071 : public AGate {
        public:
            comp4071(int nbPin = 14);
            ~comp4071() = default;
            nts::Tristate compute(std::size_t pin);
    };
}