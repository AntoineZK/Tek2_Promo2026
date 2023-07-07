/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray
*/

#pragma once
#include "Include.hpp"
#include "Math/Vector3D.hpp"

class Ray {
    public:
        Ray();
        Ray(const Point3D& a, const Vector3D& b, double time = 0.0);

        Point3D point_at_parameter(double t) const;

        Vector3D getOrigin() const;
        Vector3D getDirection() const;
        double getTime() const;
    private:
        Point3D ori;
        Vector3D direc;
        double time;
};
