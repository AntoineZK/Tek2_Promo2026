/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** Lights
*/

#include "Lights.hpp"

Lights::Lights(std::shared_ptr<ITextures> texture)
{
    this->emit = texture;
}

Lights::Lights(Color color)
{
    this->emit = std::make_shared<ColorTexture>(color);
}

// Methods

bool Lights::scatter(const Ray &r_in, const HitRecord &rec, Vector3D &attenuation, Ray &scattered) const
{
    (void)r_in;
    (void)rec;
    (void)attenuation;
    (void)scattered;
    return (false);
}

Color Lights::emitted(double u, double v, const Point3D &p) const
{
    // Les lumières émettent de la lumière donc on retourne la couleur de la texture
    return (this->emit->value(u, v, p));
}

// Getters

std::shared_ptr<ITextures> Lights::getEmit() const
{
    return this->emit;
}
