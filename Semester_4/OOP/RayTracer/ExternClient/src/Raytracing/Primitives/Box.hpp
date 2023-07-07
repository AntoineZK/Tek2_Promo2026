/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** Box
*/

#pragma once
#include "PrimitivesList.hpp"
#include "AxisRect.hpp"

class Box : public IPrimitives {
    public:
        Box();
        Box(const Point3D &p0, const Point3D &p1, std::shared_ptr<IMaterial> material);

        bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const;
        bool bounding_box(double time0, double time1, AABB &output_box) const;

        Point3D getBoxMin() const;
        Point3D getBoxMax() const;
        PrimitivesList getSides() const;
    private:
        Point3D box_min;
        Point3D box_max;
        PrimitivesList sides;
};