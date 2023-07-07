/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

RT::Parsing::Cylinder::Cylinder() : _radius(0), _height(0), _material_reflection(0), _pos(0), _rotate(0), _material(""), _material_color(3), _grp("")
{
}

RT::Parsing::Cylinder::~Cylinder()
{
}

std::string RT::Parsing::Cylinder::getName() const
{
    return ("Cylinder");
}

std::string RT::Parsing::Cylinder::getMaterial() const
{
    return (_material);
}

std::vector<double> RT::Parsing::Cylinder::getMaterialColor() const
{
    return (_material_color);
}

double RT::Parsing::Cylinder::getMaterialReflection() const
{
    return (_material_reflection);
}

double RT::Parsing::Cylinder::getRadius() const
{
    return (_radius);
}

double RT::Parsing::Cylinder::getHeight() const
{
    return (_height);
}

std::string RT::Parsing::Cylinder::getNameRect() const
{
    return ("");
}

double RT::Parsing::Cylinder::getK() const
{
    return (0);
}

void RT::Parsing::Cylinder::create(libconfig::Setting& cylinder)
{
    if (!cylinder.exists("position") || !cylinder.exists("material") || !cylinder.exists("rotation"))
        return;
    if (!cylinder.exists("radius") && !cylinder.exists("height"))
        std::cout << "No radius or no height" << std::endl;
    const libconfig::Setting& position = cylinder.lookup("position");
    const libconfig::Setting& rotation = cylinder.lookup("rotation");
    const libconfig::Setting& material = cylinder.lookup("material");
    if (!material.exists("color"))
        return;
    const libconfig::Setting& color = material.lookup("color");

    //Récupération des valeurs
    if (cylinder.exists("radius"))
        cylinder.lookupValue("radius", _radius);
    if (cylinder.exists("height"))
        cylinder.lookupValue("height", _height);
    for (int j = 0; j < position.getLength(); ++j) {
        if (!position[j].exists("x") && !position[j].exists("y") && !position[j].exists("z"))
            continue;
        if (position[j].exists("x")) {
            double x;
            position[j].lookupValue("x", x);
            _pos.push_back(x);
        } else
            _pos.push_back(0);
        if (position[j].exists("y")) {
            double y;
            position[j].lookupValue("y", y);
            _pos.push_back(y);
        } else
            _pos.push_back(0);
        if (position[j].exists("z")) {
            double z;
            position[j].lookupValue("z", z);
            _pos.push_back(z);
        } else
            _pos.push_back(0);
    }
    for (int k = 0; k < rotation.getLength(); ++k) {
        if (!rotation[k].exists("x") && !rotation[k].exists("y") && !rotation[k].exists("z"))
            continue;
        if (rotation[k].exists("x")) {
            double x;
            rotation[k].lookupValue("x", x);
            _rotate.push_back(x);
        } else
            _rotate.push_back(0);
        if (rotation[k].exists("y")) {
            double y;
            rotation[k].lookupValue("y", y);
            _rotate.push_back(y);
        } else
            _rotate.push_back(0);
        if (rotation[k].exists("z")) {
            double z;
            rotation[k].lookupValue("z", z);
            _rotate.push_back(z);
        } else
            _rotate.push_back(0);
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

void RT::Parsing::Cylinder::set(std::vector<double> pos, std::string material, std::vector<double> material_color, double material_reflection)
{
    (void) pos;
    (void) material;
    (void) material_color;
    (void) material_reflection;
}

void RT::Parsing::Cylinder::add(std::vector<double> pos, std::vector<double> rotate)
{
    if (pos.size() != 3) {
        std::cerr << "Invalid position" << std::endl;
        return;
    }
    if (rotate.size() != 3) {
        std::cerr << "Invalid rotation" << std::endl;
        return;
    }
    for (size_t i = 0; i < _pos.size(); i += 3) {
        _pos[i++] += pos[0];
        _pos[i++] += pos[1];
        _pos[i] += pos[2];
    }
    for (size_t i = 0; i < _rotate.size(); i += 3) {
        _rotate[i++] += rotate[0];
        _rotate[i++] += rotate[1];
        _rotate[i] += rotate[2];
    }
}

void RT::Parsing::Cylinder::add(std::vector<double> pos, std::string name)
{
    if (pos.size() != 3) {
        std::cerr << "Invalid position/rotation" << std::endl;
        return;
    }
    if (name == (std::string)"position") {
        for (size_t i = 0; i < _pos.size(); i += 3) {
            _pos[i++] += pos[0];
            _pos[i++] += pos[1];
            _pos[i] += pos[2];
        }
    }
    if (name == (std::string)"rotation") {
        for (size_t i = 0; i < _rotate.size(); i += 3) {
            _rotate[i++] += pos[0];
            _rotate[i++] += pos[1];
            _rotate[i] += pos[2];
        }
    }
}

std::vector<double> RT::Parsing::Cylinder::getPosRot(std::string name) const
{
    if (name == (std::string)"position")
        return (_pos);
    if (name == (std::string)"rotation")
        return (_rotate);
    return (std::vector<double>());
}

std::string RT::Parsing::Cylinder::getGroup() const
{
    return (_grp);
}

void RT::Parsing::Cylinder::setGroup(std::string grp)
{
    _grp = grp;
}