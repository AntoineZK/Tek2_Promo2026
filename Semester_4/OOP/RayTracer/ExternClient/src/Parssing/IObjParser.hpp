/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** IObjParser
*/

#pragma once
#include <libconfig.h++>
#include "../../../MainRaytracer/Include/Include.hpp"

namespace RT {
    namespace Parsing {
        class IObjParser {
            public:
                virtual void create(libconfig::Setting& cfg) = 0;
                virtual ~IObjParser() = default;
                virtual std::string getName() const = 0;
                virtual std::string getMaterial() const = 0;
                virtual std::string getNameRect() const = 0;
                virtual std::vector<double> getMaterialColor() const = 0;
                virtual std::vector<double> getPosRot(std::string name) const = 0;
                virtual double getMaterialReflection() const = 0;
                virtual double getRadius() const = 0;
                virtual double getHeight() const = 0;
                virtual double getK() const = 0;
                virtual void set(std::vector<double> pos, std::string material, std::vector<double> material_color, double material_reflection) = 0;
                virtual void add(std::vector<double> pos, std::vector<double> rotate) = 0;
                virtual void add(std::vector<double> tab, std::string name) = 0;
                virtual std::string getGroup() const = 0;
                virtual void setGroup(std::string group) = 0;


            protected:
            private:
        };
    };
};
