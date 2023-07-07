/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Translation
*/

#include "Translation.hpp"

Translation::Translation(std::shared_ptr<IPrimitives> actPri, const Vector3D& mvVector)
{
    this->actPri = actPri;
    this->offset = mvVector;
}

bool Translation::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Ray moved_r(r.getOrigin() - offset, r.getDirection(), r.getTime());
    if (!this->actPri->hit(moved_r, t_min, t_max, rec))
        return false;
    rec.setP(rec.getP() + offset);
    rec.set_face_normal(moved_r, rec.getNormal());
    return true;
}

bool Translation::bounding_box(double time0, double time1, AABB& output_box) const
{
    if (!this->actPri->bounding_box(time0, time1, output_box))
        return false;
    output_box = AABB(output_box.getMin() + offset, output_box.getMax() + offset);
    return true;
}
