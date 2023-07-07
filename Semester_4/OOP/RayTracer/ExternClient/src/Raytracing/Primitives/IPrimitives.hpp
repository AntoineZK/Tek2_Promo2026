/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IPrimitives
*/

#pragma once
#include "../AABB.hpp"
#include "../Primitives/HitRecord.hpp"

class IPrimitives {
    public:
        virtual ~IPrimitives() = default;
        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
        virtual bool bounding_box(double t0, double t1, AABB &output_box) const = 0;
};
