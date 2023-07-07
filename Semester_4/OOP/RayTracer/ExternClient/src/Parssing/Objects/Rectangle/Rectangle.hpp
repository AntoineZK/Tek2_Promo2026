/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Rectangle
*/

#pragma once
#include "../../IObjParser.hpp"

namespace RT {
    namespace Parsing {
        class Rectangle : public IObjParser {
            public:
                Rectangle();
                void create(libconfig::Setting& cfg);
                void set(std::vector<double> pos, std::string material, std::vector<double> material_color, double material_reflection);
                void add(std::vector<double> pos, std::vector<double> rotate);
                void add(std::vector<double> tab, std::string name);
                std::vector<double> getPosRot(std::string name) const;
                std::string getName() const;
                std::string getMaterial() const;
                std::string getNameRect() const;
                std::vector<double> getMaterialColor() const;
                double getMaterialReflection() const;
                double getRadius() const;
                double getHeight() const;
                double getK() const;
                std::string getGroup() const;
                void setGroup(std::string group);
                ~Rectangle();

            protected:
            private:
                std::vector<double> _pos;
                std::string _material;
                std::vector<double> _material_color;
                double _material_reflection;
                double _k;
                std::string _grp;
                std::string _name;
        };
    }
}

