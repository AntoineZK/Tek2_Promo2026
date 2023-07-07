/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#pragma once
#include "IPrimitives.hpp"

class Sphere : public IPrimitives {
    public:
        Sphere();
        Sphere(Vector3D center, double radius, std::shared_ptr<IMaterial> mate);

        static void getSphericalUV(const Vector3D &p, double &u, double &v);
        bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
        bool bounding_box(double t0, double t1, AABB &output_box) const;

        Vector3D getCenter() const;
        double getRadius() const;
        std::shared_ptr<IMaterial> getMaterial() const;
    private:
        Vector3D center;
        double radius;
        std::shared_ptr<IMaterial> mate;
};
