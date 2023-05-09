/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** IGraphical
*/

#pragma once
// Standard includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Project includes
#include "IData.hpp"

namespace arcade {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;
            /**
             * @brief Get the Inputs from the user
             * @return A vector of int that represent the inputs
             */
            virtual std::vector<int> getInputs() = 0;
            /**
             * @brief Display the game
             * @param data The data to display (Should print a map using a vector of IEntity)
             */
            virtual void display(std::shared_ptr<IData>) = 0;

    };
}
