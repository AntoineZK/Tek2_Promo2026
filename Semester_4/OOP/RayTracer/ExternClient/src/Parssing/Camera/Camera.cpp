/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Camera
*/

#include "Camera.hpp"

RT::Parsing::Camera::Camera()
{
    _raypix = 0.0;
    _maxbounds = 0.0;
    _focal = 0.0;
    _aperture = 0.0;
    _fov = 0.0;
    _background = {0.0, 0.0, 0.0};
    _rotation = {0.0, 0.0, 0.0};
    _position = {0.0, 0.0, 0.0};
    _resolution = {0.0, 0.0};
}

RT::Parsing::Camera::~Camera()
{
}

std::string RT::Parsing::Camera::getName() const
{
    return ("Camera");
}

std::vector<double> RT::Parsing::Camera::getResolution() const
{
    return (_resolution);
}

std::vector<double> RT::Parsing::Camera::getPosition() const
{
    return (_position);
}

std::vector<double> RT::Parsing::Camera::getRotation() const
{
    return (_rotation);
}

double RT::Parsing::Camera::getFov() const
{
    return (_fov);
}

double RT::Parsing::Camera::getAperture() const
{
    return (_aperture);
}

double RT::Parsing::Camera::getFocal() const
{
    return (_focal);
}

double RT::Parsing::Camera::getMaxbounds() const
{
    return (_maxbounds);
}

double RT::Parsing::Camera::getRaypix() const
{
    return (_raypix);
}

std::vector<double> RT::Parsing::Camera::getBackground() const
{
    return (_background);
}

void RT::Parsing::Camera::create(libconfig::Setting& cfg)
{
    if (!cfg.exists("fov") || !cfg.exists("resolution") || !cfg.exists("rotation")
        || !cfg.exists("maxbounds") || !cfg.exists("aperture") || !cfg.exists("raypix")
        || !cfg.exists("focal"))
        return;
    cfg.lookupValue("fov", _fov);
    cfg.lookupValue("maxbounds", _maxbounds);
    cfg.lookupValue("raypix", _raypix);
    cfg.lookupValue("focal", _focal);
    cfg.lookupValue("aperture", _aperture);
    if (cfg.exists("resolution")) {
        const libconfig::Setting& resolution = cfg.lookup("resolution");
        
        //Récupération des valeurs
        if (resolution.exists("width"))
            resolution.lookupValue("width", _resolution[0]);
        if (resolution.exists("height"))
            resolution.lookupValue("height", _resolution[1]);
    }
    if (cfg.exists("rotation")) {
        const libconfig::Setting& rotation = cfg.lookup("rotation");
        
        //Récupération des valeurs
        if (rotation.exists("x"))
            rotation.lookupValue("x", _rotation[0]);
        if (rotation.exists("y"))
            rotation.lookupValue("y", _rotation[1]);
        if (rotation.exists("z"))
            rotation.lookupValue("z", _rotation[2]);
    }
    if (cfg.exists("position")) {
        const libconfig::Setting& position = cfg.lookup("position");

        //Récupération des valeurs
        if (position.exists("x"))
            position.lookupValue("x", _position[0]);
        if (position.exists("y"))
            position.lookupValue("y", _position[1]);
        if (position.exists("z"))
            position.lookupValue("z", _position[2]);
    }
    if (cfg.exists("background")) {
        const libconfig::Setting& background = cfg.lookup("background");
        if (background.exists("r"))
            background.lookupValue("r", _background[0]);
        if (background.exists("g"))
            background.lookupValue("g", _background[1]);
        if (background.exists("b"))
            background.lookupValue("b", _background[2]);
    } else {
        _background[0] = 173.0;
        _background[1] = 216.0;
        _background[2] = 230.0;
    }
}
