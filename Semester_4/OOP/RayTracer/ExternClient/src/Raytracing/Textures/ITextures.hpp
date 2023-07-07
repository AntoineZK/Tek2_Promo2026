/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** ITextures
*/

#pragma once
#include "../Math/Vector3D.hpp"

class ITextures {
    public:
        virtual ~ITextures() = default;
        virtual Color value(double u, double v, const Point3D &p) const = 0;
};
