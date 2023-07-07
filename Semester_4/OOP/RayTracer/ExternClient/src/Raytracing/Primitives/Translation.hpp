/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Translation
*/

#pragma once
#include "PrimitivesList.hpp"

class Translation : public IPrimitives {
    public:
        Translation(std::shared_ptr<IPrimitives> p, const Vector3D& displacement);

        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

        bool bounding_box(double time0, double time1, AABB& output_box) const;

    private:
        std::shared_ptr<IPrimitives> actPri;
        Vector3D offset;
};
