/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Factory
*/

#pragma once
#include "IObjParser.hpp"

namespace RT {
    namespace Parsing {
        class Factory {
            public:
                std::shared_ptr<RT::Parsing::IObjParser> createFactory(std::string name);

            protected:
            private:
        };
    };
};
