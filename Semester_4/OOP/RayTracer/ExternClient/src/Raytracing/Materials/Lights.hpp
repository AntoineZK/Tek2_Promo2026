/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** Lights
*/

#pragma once
#include "IMaterial.hpp"
#include "../Textures/ColorTexture.hpp"

class Lights : public IMaterial {
    public:
        Lights(std::shared_ptr<ITextures> texture);
        Lights(Color color);

        bool scatter(const Ray& r_in, const HitRecord& rec, Vector3D& attenuation, Ray& scattered) const;
        Color emitted(double u, double v, const Point3D& p) const;
        std::shared_ptr<ITextures> getEmit() const;
    private:
        std::shared_ptr<ITextures> emit;
};
