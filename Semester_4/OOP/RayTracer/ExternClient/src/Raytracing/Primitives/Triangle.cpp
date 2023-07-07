/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Triangle
*/

#include "Triangle.hpp"

Triangle::Triangle()
{
    a = Vector3D(0, 0, 0);
    b = Vector3D(0, 0, 0);
    c = Vector3D(0, 0, 0);
    mate = nullptr;
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c, std::shared_ptr<IMaterial> mate)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->mate = mate;
}

bool Triangle::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Vector3D e1 = b - a;
    Vector3D e2 = c - a;
    Vector3D h = cross(r.getDirection(), e2);
    double j = dot(e1, h);
    if (j > -0.0001 && j < 0.0001)
        return false;
    double f = 1 / j;
    Vector3D s = r.getOrigin() - a;
    double u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;
    Vector3D q = cross(s, e1);
    double v = f * dot(r.getDirection(), q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    double t = f * dot(e2, q);
    if (t < t_min || t > t_max)
        return false;
    rec.setT(t);
    rec.setP(r.point_at_parameter(t));
    rec.setNormal(unitVector(cross(e1, e2)));
    rec.setMatPtr(mate);
    return true;
}

bool Triangle::bounding_box(double t0, double t1, AABB &output_box) const
{
    (void)t0;
    (void)t1;
    Vector3D min = Vector3D(std::min(a.getX(), std::min(b.getX(), c.getX())),
                            std::min(a.getY(), std::min(b.getY(), c.getY())),
                            std::min(a.getZ(), std::min(b.getZ(), c.getZ())));
    Vector3D max = Vector3D(std::max(a.getX(), std::max(b.getX(), c.getX())),
                            std::max(a.getY(), std::max(b.getY(), c.getY())),
                            std::max(a.getZ(), std::max(b.getZ(), c.getZ())));
    output_box = AABB(min, max);
    return true;
}

Vector3D Triangle::getA() const
{
    return a;
}

Vector3D Triangle::getB() const
{
    return b;
}

Vector3D Triangle::getC() const
{
    return c;
}

std::shared_ptr<IMaterial> Triangle::getMaterial() const
{
    return mate;
}