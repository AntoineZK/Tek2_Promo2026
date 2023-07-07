/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** AxisRect
*/

#include "AxisRect.hpp"

// XYRect

XYRect::XYRect()
{
}

XYRect::XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<IMaterial> mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->k = k;
    this->mat_ptr = mat;
}

bool XYRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.getOrigin().getZ()) / r.getDirection().getZ();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.getOrigin().getX() + t * r.getDirection().getX();
    auto y = r.getOrigin().getY() + t * r.getDirection().getY();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.setU((x - x0) / (x1 - x0));
    rec.setV((y - y0) / (y1 - y0));
    rec.setT(t);
    auto outward_normal = Vector3D(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.setMatPtr(mat_ptr);
    rec.setP(r.point_at_parameter(t));
    return true;
}

bool XYRect::bounding_box(double time0, double time1, AABB &output_box) const
{
    (void)(time0);
    (void)(time1);
    output_box = AABB(Vector3D(x0, y0, k - 0.0001), Vector3D(x1, y1, k + 0.0001));
    return true;
}

std::shared_ptr<IMaterial> XYRect::getMaterial() const
{
    return this->mat_ptr;
}

double XYRect::getX0() const
{
    return this->x0;
}

double XYRect::getX1() const
{
    return this->x1;
}

double XYRect::getY0() const
{
    return this->y0;
}

double XYRect::getY1() const
{
    return this->y1;
}

double XYRect::getK() const
{
    return this->k;
}

// XZRect

XZRect::XZRect()
{
}

XZRect::XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<IMaterial> mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mat_ptr = mat;
}

bool XZRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.getOrigin().getY()) / r.getDirection().getY();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.getOrigin().getX() + t * r.getDirection().getX();
    auto z = r.getOrigin().getZ() + t * r.getDirection().getZ();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.setU((x - x0) / (x1 - x0));
    rec.setV((z - z0) / (z1 - z0));
    rec.setT(t);
    auto outward_normal = Vector3D(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.setMatPtr(mat_ptr);
    rec.setP(r.point_at_parameter(t));
    return true;
}

bool XZRect::bounding_box(double time0, double time1, AABB &output_box) const
{
    (void)(time0);
    (void)(time1);
    output_box = AABB(Vector3D(x0, k - 0.0001, z0), Vector3D(x1, k + 0.0001, z1));
    return true;
}

std::shared_ptr<IMaterial> XZRect::getMaterial() const
{
    return this->mat_ptr;
}

double XZRect::getX0() const
{
    return this->x0;
}

double XZRect::getX1() const
{
    return this->x1;
}

double XZRect::getZ0() const
{
    return this->z0;
}

double XZRect::getZ1() const
{
    return this->z1;
}

double XZRect::getK() const
{
    return this->k;
}

// YZRect

YZRect::YZRect()
{
}

YZRect::YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<IMaterial> mat)
{
    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mat_ptr = mat;
}

bool YZRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.getOrigin().getX()) / r.getDirection().getX();
    if (t < t_min || t > t_max)
        return false;
    auto y = r.getOrigin().getY() + t * r.getDirection().getY();
    auto z = r.getOrigin().getZ() + t * r.getDirection().getZ();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.setU((y - y0) / (y1 - y0));
    rec.setV((z - z0) / (z1 - z0));
    rec.setT(t);
    auto outward_normal = Vector3D(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.setMatPtr(mat_ptr);
    rec.setP(r.point_at_parameter(t));
    return true;
}

bool YZRect::bounding_box(double time0, double time1, AABB &output_box) const
{
    (void)(time0);
    (void)(time1);
    output_box = AABB(Vector3D(k - 0.0001, y0, z0), Vector3D(k + 0.0001, y1, z1));
    return true;
}

std::shared_ptr<IMaterial> YZRect::getMaterial() const
{
    return this->mat_ptr;
}

double YZRect::getY0() const
{
    return this->y0;
}

double YZRect::getY1() const
{
    return this->y1;
}

double YZRect::getZ0() const
{
    return this->z0;
}

double YZRect::getZ1() const
{
    return this->z1;
}

double YZRect::getK() const
{
    return this->k;
}
