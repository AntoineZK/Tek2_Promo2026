/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Box
*/

#include "Box.hpp"

RT::Parsing::Box::Box() : _pos(0), _material(""), _material_color(3), _material_reflection(0), _grp("")
{
}

RT::Parsing::Box::~Box()
{
}

std::string RT::Parsing::Box::getName() const
{
    return ("Box");
}

std::string RT::Parsing::Box::getMaterial() const
{
    return (_material);
}

std::vector<double> RT::Parsing::Box::getMaterialColor() const
{
    return (_material_color);
}

double RT::Parsing::Box::getMaterialReflection() const
{
    return (_material_reflection);
}

double RT::Parsing::Box::getRadius() const
{
    return (0);
}

double RT::Parsing::Box::getHeight() const
{
    return (0);
}

double RT::Parsing::Box::getK() const
{
    return (0);
}

std::string RT::Parsing::Box::getNameRect() const
{
    return ("");
}

void RT::Parsing::Box::create(libconfig::Setting& box)
{
    if (!box.exists("position") || !box.exists("material"))
        return;
    const libconfig::Setting& position = box.lookup("position");
    const libconfig::Setting& material = box.lookup("material");
    if (!material.exists("color"))
        return;
    const libconfig::Setting& color = material.lookup("color");

    //Récupération des valeurs
    for (int j = 0; j < position.getLength(); ++j) {
        if (!position[j].exists("x") && !position[j].exists("y") && !position[j].exists("z"))
            continue;
        if (position[j].exists("x")) {
            double x = 0.0;
            position[j].lookupValue("x", x);
            _pos.push_back(x);
        } else
            _pos.push_back(0);
        if (position[j].exists("y")) {
            double y = 0.0;
            position[j].lookupValue("y", y);
            _pos.push_back(y);
        } else
            _pos.push_back(0);
        if (position[j].exists("z")) {
            double z = 0.0;
            position[j].lookupValue("z", z);
            _pos.push_back(z);
        } else
            _pos.push_back(0);
    }
    //Material
    if (material.exists("type"))
        material.lookupValue("type", _material);
    if (material.exists("reflectivity"))
        material.lookupValue("reflectivity", _material_reflection);
    if (color.exists("r"))
        color.lookupValue("r", _material_color[0]);
    if (color.exists("g"))
        color.lookupValue("g", _material_color[1]);
    if (color.exists("b"))
        color.lookupValue("b", _material_color[2]);

    //Vérification des valeurs
    if (_material_color[0] > 255 || _material_color[0] < 0) {
        std::cout << "Invalid color value for r" << std::endl;
        _material_color[0] = 0;
    }
    if (_material_color[1] > 255 || _material_color[1] < 0) {
        std::cout << "Invalid color value for g" << std::endl;
        _material_color[1] = 0;
    }
    if (_material_color[2] > 255 || _material_color[2] < 0) {
        std::cout << "Invalid color value for b" << std::endl;
        _material_color[2] = 0;
    }
    if (_material == "") {
        std::cout << "Invalid material type" << std::endl;
        _material = "lambertian";
    }
}

void RT::Parsing::Box::set(std::vector<double> pos, std::string material, std::vector<double> material_color, double material_reflection)
{
    (void) pos;
    (void) material;
    (void) material_color;
    (void) material_reflection;
}

void RT::Parsing::Box::add(std::vector<double> pos, std::vector<double> rotate)
{
    (void) rotate;
    if (pos.size() != 3) {
        std::cerr << "Invalid position" << std::endl;
        return;
    }
    for (size_t i = 0; i < _pos.size(); i += 3) {
        _pos[i++] += pos[0];
        _pos[i++] += pos[1];
        _pos[i] += pos[2];
    }
}

void RT::Parsing::Box::add(std::vector<double> pos, std::string name)
{
    if (pos.size() != 3) {
        std::cerr << "Invalid position" << std::endl;
        return;
    }
    if (name == (std::string)"position") {
        for (size_t i = 0; i < _pos.size(); i += 3) {
            _pos[i++] += pos[0];
            _pos[i++] += pos[1];
            _pos[i] += pos[2];
        }
    }
}

std::vector<double> RT::Parsing::Box::getPosRot(std::string name) const
{
    if (name == (std::string)"position")
        return (_pos);
    return (std::vector<double>());
}

std::string RT::Parsing::Box::getGroup() const
{
    return (_grp);
}

void RT::Parsing::Box::setGroup(std::string grp)
{
    _grp = grp;
}