/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AGate
*/

#pragma once
#include "AComponent.hpp"
#include <iostream>
#include <memory>
namespace nts {
    class AGate : public AComponent {
        public:
            AGate(int nbPin = 14);
            ~AGate() = default;
            nts::Tristate opposite(nts::Tristate state);
            std::vector<std::unique_ptr<IComponent>> _comps;
    };
}
