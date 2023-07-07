/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Dieletric
*/

#pragma once
#include "IMaterial.hpp"

class Dielectric : public IMaterial {
    public:
        Dielectric(double ri);

        bool scatter(const Ray& r_in, const HitRecord& rec, Vector3D& attenuation, Ray& scattered) const;
        Color emitted(double u, double v, const Point3D& p) const;

        double getRefIdx() const;
    private:
        double ref_idx;
};
