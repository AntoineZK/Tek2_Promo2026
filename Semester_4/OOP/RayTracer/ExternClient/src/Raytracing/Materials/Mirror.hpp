/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Mirror
*/

#pragma once
#include "IMaterial.hpp"

class Mirror : public IMaterial {
    public:
        Mirror(const Vector3D& a, double f);

        bool scatter(const Ray& r_in, const HitRecord& rec, Vector3D& attenuation, Ray& scattered) const;
        Color emitted(double u, double v, const Point3D& p) const;

        Vector3D getAlbedo() const;
        double getFuzz() const;
    private:
        Vector3D albedo;
        double fuzz;
};
