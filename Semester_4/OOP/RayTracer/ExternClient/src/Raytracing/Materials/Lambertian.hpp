/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Lambertian
*/

#pragma once
#include "IMaterial.hpp"
#include "../Textures/ColorTexture.hpp"

class Lambertian : public IMaterial {
    public:
        Lambertian(const Vector3D& a);
        Lambertian(std::shared_ptr<ITextures> a);

        bool scatter(const Ray& r_in, const HitRecord& rec, Vector3D& attenuation, Ray& scattered) const;
        Color emitted(double u, double v, const Point3D& p) const;

        std::shared_ptr<ITextures> getAlbedo() const;
    private:
        std::shared_ptr<ITextures> albedo;
};
