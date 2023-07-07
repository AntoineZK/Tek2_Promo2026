/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Camera
*/

#pragma once
#include "../IObjParser.hpp"

namespace RT {
    namespace Parsing {
        class Camera {
            public:
                Camera();
                void create(libconfig::Setting& cfg);
                std::string getName() const;
                std::vector<double> getResolution() const;
                std::vector<double> getPosition() const;
                std::vector<double> getRotation() const;
                std::vector<double> getBackground() const;
                double getFov() const;
                double getAperture() const;
                double getFocal() const;
                double getMaxbounds() const;
                double getRaypix() const;
                ~Camera();

            protected:
            private:
                std::vector<double> _resolution;
                std::vector<double> _position;
                std::vector<double> _rotation;
                std::vector<double> _background;
                double _fov;
                double _aperture;
                double _focal;
                double _maxbounds;
                double _raypix;

        };
    };
};
