/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Plane
*/

#pragma once

#include "IPrimitives.hpp"

class Plane : public IPrimitives {
    public:
        Plane();
        Plane(Vector3D a, Vector3D b, Vector3D c, std::shared_ptr<IMaterial> mate);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
        bool bounding_box(double t0, double t1, AABB &output_box) const;

        Vector3D getA() const;
        Vector3D getB() const;
        Vector3D getC() const;
        std::shared_ptr<IMaterial> getMaterial() const;
    private:
        Vector3D a;
        Vector3D b;
        Vector3D c;
        std::shared_ptr<IMaterial> mate;
};