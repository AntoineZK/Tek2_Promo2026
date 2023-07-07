/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** LimitedCyinlinder
*/

#pragma once
#include "IPrimitives.hpp"

class LimitedCylinder : public IPrimitives {
    public:
        LimitedCylinder();
        LimitedCylinder(Vector3D bottom_center, Vector3D top_center, double r, std::shared_ptr<IMaterial> mate);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
        bool bounding_box(double t0, double t1, AABB &output_box) const;

        Vector3D getA() const;
        Vector3D getB() const;
        double getR() const;
        std::shared_ptr<IMaterial> getMaterial() const;
    private:
        Vector3D top_center;
        Vector3D bottom_center;
        double r;
        std::shared_ptr<IMaterial> mate;
};