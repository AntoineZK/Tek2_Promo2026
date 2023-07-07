/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** ColorTexture
*/

#pragma once
#include "ITextures.hpp"

class ColorTexture : public ITextures {
    public:
        ColorTexture();
        ColorTexture(const Color &c);
        ColorTexture(double red, double green, double blue);

        Color value(double u, double v, const Point3D &p) const;

        Color getColor() const;
    private:
        Color color;
};
