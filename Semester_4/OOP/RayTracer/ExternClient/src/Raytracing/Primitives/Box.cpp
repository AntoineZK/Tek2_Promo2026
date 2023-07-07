/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** Box
*/

#include "Box.hpp"

Box::Box()
{
}

Box::Box(const Point3D &p0, const Point3D &p1, std::shared_ptr<IMaterial> material)
{
    box_min = p0;
    box_max = p1;

    sides.add(std::make_shared<XYRect>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p1.getZ(), material));
    sides.add(std::make_shared<XYRect>(p0.getX(), p1.getX(), p0.getY(), p1.getY(), p0.getZ(), material));

    sides.add(std::make_shared<XZRect>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p1.getY(), material));
    sides.add(std::make_shared<XZRect>(p0.getX(), p1.getX(), p0.getZ(), p1.getZ(), p0.getY(), material));

    sides.add(std::make_shared<YZRect>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p1.getX(), material));
    sides.add(std::make_shared<YZRect>(p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p0.getX(), material));
}

// Methods

bool Box::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
{
    return sides.hit(ray, t_min, t_max, rec);
}

bool Box::bounding_box(double time0, double time1, AABB &output_box) const
{
    (void)time0;
    (void)time1;
    output_box = AABB(this->box_min, this->box_max);
    return true;
}

// Getters

Point3D Box::getBoxMin() const
{
    return this->box_min;
}

Point3D Box::getBoxMax() const
{
    return this->box_max;
}

PrimitivesList Box::getSides() const
{
    return this->sides;
}
