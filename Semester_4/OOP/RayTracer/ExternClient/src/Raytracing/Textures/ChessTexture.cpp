/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** ChessTexture
*/

#include "ChessTexture.hpp"

ChessTexture::ChessTexture()
{
}

ChessTexture::ChessTexture(std::shared_ptr<ITextures> even, std::shared_ptr<ITextures> odd)
{
    this->even = even;
    this->odd = odd;
}

ChessTexture::ChessTexture(const Color &even, const Color &odd)
{
    this->even = std::make_shared<ColorTexture>(even);
    this->odd = std::make_shared<ColorTexture>(odd);
}

Color ChessTexture::value(double u, double v, const Point3D &p) const
{
    // On utilise la fonction sin pour créer un motif de damier, car le resultat de sin oscille entre -1 et 1
    auto sines = sin(10 * p.getX()) * sin(10 * p.getY()) * sin(10 * p.getZ());
    if (sines < 0)
        return this->odd->value(u, v, p);
    else
        return this->even->value(u, v, p);
}
