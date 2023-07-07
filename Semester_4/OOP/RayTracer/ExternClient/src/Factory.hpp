/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Factory
*/

#pragma once
#include "Parssing/IObjParser.hpp"
#include "Raytracing/Primitives/IPrimitives.hpp"
#include "Raytracing/Primitives/PrimitivesList.hpp"

namespace RT {
    class Factory {
        public:
            Factory();
            std::shared_ptr<IMaterial> createMaterial(std::string name, std::vector<double> color, double reflectivity);
            PrimitivesList create(std::vector<std::shared_ptr<RT::Parsing::IObjParser>> obj_parser);
            ~Factory();

        protected:
        private:
    };
};