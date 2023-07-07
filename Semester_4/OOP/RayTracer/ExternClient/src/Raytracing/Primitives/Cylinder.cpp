/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(Vector3D point_on_axis, Vector3D vecteur_direction, double r, std::shared_ptr<IMaterial> mate)
{
    this->point_on_axis = point_on_axis;
    this->vecteur_direction = vecteur_direction;
    this->r = r;
    this->mate = mate;
}

bool Cylinder::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    const Vector3D& A = point_on_axis;
    const Vector3D& V = vecteur_direction;
    const double& radius = this->r;

    const Vector3D& O = r.getOrigin();
    const Vector3D& D = r.getDirection();

    // Compute coefficients of the quadratic equation
    const double a = D.dot(D) - pow(D.dot(V), 2);
    const double b = 2 * (D.dot(O - A) - D.dot(V) * (O - A).dot(V));
    const double c = (O - A).dot(O - A) - pow((O - A).dot(V), 2) - pow(radius, 2);

    // Compute discriminant of the quadratic equation
    const double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    // Compute the two roots of the quadratic equation
    const double sqrt_discriminant = sqrt(discriminant);
    const double t1 = (-b - sqrt_discriminant) / (2 * a);
    const double t2 = (-b + sqrt_discriminant) / (2 * a);

    // Choose the smallest positive root within the given range
    double t;
    if (t1 > t_min && t1 < t_max) {
        t = t1;
    } else if (t2 > t_min && t2 < t_max) {
        t = t2;
    } else {
        return false;
    }

    // Compute intersection point and normal vector
    Vector3D point = r.point_at_parameter(t);
    Vector3D normal = (point - A - V * (point - A).dot(V)).normalized();
    if (normal.dot(D) > 0) {
        normal = -normal;
    }

    // Set hit record
    rec.setT(t);
    rec.setP(point);
    rec.setNormal(normal);
    rec.setMatPtr(mate);

    return true;
}

bool Cylinder::bounding_box(double t0, double t1, AABB &output_box) const
{
    (void)t0;
    (void)t1;
    Vector3D min = point_on_axis - Vector3D(r, r, r);
    Vector3D max = point_on_axis + Vector3D(r, r, r);
    output_box = AABB(min, max);
    return true;
}