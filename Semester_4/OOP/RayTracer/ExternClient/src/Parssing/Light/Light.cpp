/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Light
*/

#include "Light.hpp"

RT::Parsing::Light::Light() : _point_pos(3), _point_color(3), _direct_direct(3), _direct_color(3)
{
}

RT::Parsing::Light::~Light()
{
}

std::string RT::Parsing::Light::getName() const
{
    return ("Light");
}

void RT::Parsing::Light::create(libconfig::Setting& cfg)
{
    //Affichage des points
    if (cfg.exists("point")) {
        const libconfig::Setting& points = cfg.lookup("point");
        for (int i = 0; i < points.getLength(); ++i) {
            const libconfig::Setting& point = points[i];
            if (!point.exists("position") || !point.exists("color"))
                continue;
            const libconfig::Setting& position = point.lookup("position");
            const libconfig::Setting& color = point.lookup("color");

            //Récupération des valeurs
            if (position.exists("x"))
                position.lookupValue("x", _point_pos[0]);
            if (position.exists("y"))
                position.lookupValue("y", _point_pos[1]);
            if (position.exists("z"))
                position.lookupValue("z", _point_pos[2]);
            if (color.exists("r"))
                color.lookupValue("r", _point_color[0]);
            if (color.exists("g"))
                color.lookupValue("g", _point_color[1]);
            if (color.exists("b"))
                color.lookupValue("b", _point_color[2]);

            //Vérification des valeurs
            if (_point_color[0] > 255 || _point_color[0] < 0) {
                std::cout << "Invalid color value for r" << std::endl;
                _point_color[0] = 0;
            }
            if (_point_color[1] > 255 || _point_color[1] < 0) {
                std::cout << "Invalid color value for g" << std::endl;
                _point_color[1] = 0;
            }
            if (_point_color[2] > 255 || _point_color[2] < 0) {
                std::cout << "Invalid color value for b" << std::endl;
                _point_color[2] = 0;
            }
        }
    }

    //Affichage des directionals
    if (cfg.exists("directional")) {
        const libconfig::Setting& directionals = cfg.lookup("directional");
        for (int i = 0; i < directionals.getLength(); ++i) {
            const libconfig::Setting& directional = directionals[i];
            if (!directional.exists("direction") || !directional.exists("color"))
                continue;
            const libconfig::Setting& direction = directional.lookup("direction");
            const libconfig::Setting& color = directional.lookup("color");

            //Récupération des valeurs
            if (direction.exists("x"))
                direction.lookupValue("x", _direct_direct[0]);
            if (direction.exists("y"))
                direction.lookupValue("y", _direct_direct[1]);
            if (direction.exists("z"))
                direction.lookupValue("z", _direct_direct[2]);
            if (color.exists("r"))
                color.lookupValue("r", _direct_color[0]);
            if (color.exists("g"))
                color.lookupValue("g", _direct_color[1]);
            if (color.exists("b"))
                color.lookupValue("b", _direct_color[2]);

            //Vérification des valeurs
            if (_direct_color[0] > 255 || _direct_color[0] < 0) {
                std::cout << "Invalid color value for r" << std::endl;
                _direct_color[0] = 0;
            }
            if (_direct_color[1] > 255 || _direct_color[1] < 0) {
                std::cout << "Invalid color value for g" << std::endl;
                _direct_color[1] = 0;
            }
            if (_direct_color[2] > 255 || _direct_color[2] < 0) {
                std::cout << "Invalid color value for b" << std::endl;
                _direct_color[2] = 0;
            }
        }
    }
}
