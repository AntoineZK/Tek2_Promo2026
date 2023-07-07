/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Cylinder
*/

#pragma once
#include "IPrimitives.hpp"

class Cylinder : public IPrimitives {
    public:
        Cylinder();
        Cylinder(Vector3D point_on_axis, Vector3D vecteur_direction, double r, std::shared_ptr<IMaterial> mate);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const;
        bool bounding_box(double t0, double t1, AABB &output_box) const;

        Vector3D getA() const;
        Vector3D getB() const;
        double getR() const;
        std::shared_ptr<IMaterial> getMaterial() const;
    private:
        Vector3D vecteur_direction;
        Vector3D point_on_axis;
        double r;
        std::shared_ptr<IMaterial> mate;
};
