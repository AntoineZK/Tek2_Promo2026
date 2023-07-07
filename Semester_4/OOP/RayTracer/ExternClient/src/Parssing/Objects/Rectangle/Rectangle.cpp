/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

RT::Parsing::Rectangle::Rectangle() : _pos(0), _material(""), _material_color(3), _material_reflection(0), _k(0), _grp(""), _name("")
{
}

RT::Parsing::Rectangle::~Rectangle()
{
}

std::string RT::Parsing::Rectangle::getName() const
{
    return ("Rectangle");
}

std::string RT::Parsing::Rectangle::getMaterial() const
{
    return (_material);
}

std::vector<double> RT::Parsing::Rectangle::getMaterialColor() const
{
    return (_material_color);
}

double RT::Parsing::Rectangle::getMaterialReflection() const
{
    return (_material_reflection);
}

double RT::Parsing::Rectangle::getRadius() const
{
    return (0);
}

double RT::Parsing::Rectangle::getHeight() const
{
    return (0);
}

double RT::Parsing::Rectangle::getK() const
{
    return (_k);
}

std::string RT::Parsing::Rectangle::getNameRect() const
{
    return (_name);
}

void RT::Parsing::Rectangle::create(libconfig::Setting& Rectangle)
{
    if (!Rectangle.exists("position") || !Rectangle.exists("material") || !Rectangle.exists("k") || !Rectangle.exists("name"))
        return;
    const libconfig::Setting& position = Rectangle.lookup("position");
    const libconfig::Setting& material = Rectangle.lookup("material");
    if (!material.exists("color"))
        return;
    const libconfig::Setting& color = material.lookup("color");

    //Récupération des valeurs
    if (Rectangle.exists("k"))
        Rectangle.lookupValue("k", _k);
    if (Rectangle.exists("name"))
        Rectangle.lookupValue("name", _name);
    for (int j = 0; j < position.getLength(); ++j) {
        if (!position[j].exists("coord1") && !position[j].exists("coord2"))
            continue;
        if (position[j].exists("coord1")) {
            double x;
            position[j].lookupValue("coord1", x);
            _pos.push_back(x);
        } else
            _pos.push_back(0);
        if (position[j].exists("coord2")) {
            double y;
            position[j].lookupValue("coord2", y);
            _pos.push_back(y);
        } else
            _pos.push_back(0);
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

void RT::Parsing::Rectangle::set(std::vector<double> pos, std::string material, std::vector<double> material_color, double material_reflection)
{
    _pos = pos;
    _material = material;
    _material_color = material_color;
    _material_reflection = material_reflection;
}

void RT::Parsing::Rectangle::add(std::vector<double> pos, std::vector<double> rotate)
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

void RT::Parsing::Rectangle::add(std::vector<double> pos, std::string name)
{
    if (pos.size() != 3) {
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

std::vector<double> RT::Parsing::Rectangle::getPosRot(std::string name) const
{
    if (name == (std::string)"position")
        return (_pos);
    return (std::vector<double>());
}

std::string RT::Parsing::Rectangle::getGroup() const
{
    return (_grp);
}

void RT::Parsing::Rectangle::setGroup(std::string grp)
{
    _grp = grp;
}