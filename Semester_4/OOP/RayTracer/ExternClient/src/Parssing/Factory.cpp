/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Objects/Sphere/Sphere.hpp"
#include "Objects/Rectangle/Rectangle.hpp"
#include "Objects/Triangle/Triangle.hpp"
#include "Objects/Box/Box.hpp"
#include "Objects/Cylinder/Cylinder.hpp"
#include "Objects/LimitedCylinder/LimitedCylinder.hpp"
#include "Objects/Plane/Plane.hpp"

std::shared_ptr<RT::Parsing::IObjParser> RT::Parsing::Factory::createFactory(std::string name)
{
    std::map<std::string, std::shared_ptr<RT::Parsing::IObjParser>> map_obj = {
        {"sphere", std::make_shared<RT::Parsing::Sphere>()},
        {"rectangle", std::make_shared<RT::Parsing::Rectangle>()},
        {"triangle", std::make_shared<RT::Parsing::Triangle>()},
        {"plane", std::make_shared<RT::Parsing::Plane>()},
        {"box", std::make_shared<RT::Parsing::Box>()},
        {"cylinder", std::make_shared<RT::Parsing::Cylinder>()},
        {"limitedcylinder", std::make_shared<RT::Parsing::LimitedCylinder>()}
    };
    if (map_obj.find(name) == map_obj.end())
        return nullptr;
    map_obj[name]->setGroup(name);
    return map_obj[name];
}
