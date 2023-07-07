/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Plane
*/

#include "Plane.hpp"

Plane::Plane()
{
}

Plane::Plane(Vector3D a, Vector3D b, Vector3D c, std::shared_ptr<IMaterial> mate)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->mate = mate;
}

bool Plane::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {

    const Vector3D& p1 = this->a;
    const Vector3D& p2 = this->b;
    const Vector3D& p3 = this->c;

    // Calcule de la normale du plan
    Vector3D normal = cross((p2 - p1), (p3 - p1)).normalized();

    // Calcule de la distance du plan par rapport à l'origine
    double d = -p1.dot(normal);

    // Calcule de la distance entre l'origine du rayon et le plan
    double t = -(r.getOrigin().dot(normal) + d) / (r.getDirection().dot(normal));

    if (t < t_min || t > t_max) {
        return false;
    }

    Vector3D point = r.point_at_parameter(t);

    // Set the hit record
    rec.setT(t);
    rec.setP(point);
    rec.setNormal(normal);
    rec.setMatPtr(mate);

    return true;
}

bool Plane::bounding_box(double t0, double t1, AABB& output_box) const {
    (void)t0;
    (void)t1;
    (void)output_box;
    return false;
}