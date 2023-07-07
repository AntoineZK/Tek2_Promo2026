/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** ColorTexture
*/

#include "ColorTexture.hpp"

ColorTexture::ColorTexture()
{
}

ColorTexture::ColorTexture(const Color &c)
{
    this->color = c;
    // this->color.toDouble();
}

ColorTexture::ColorTexture(double red, double green, double blue)
{
    this->color = Color(red, green, blue);
    // this->color.toDouble();
}

Color ColorTexture::value(double u, double v, const Point3D &p) const
{
    (void)u;
    (void)v;
    (void)p;
    return this->color;
}

Color ColorTexture::getColor() const
{
    return this->color;
}
