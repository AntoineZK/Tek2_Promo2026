/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** LimitedCylinder
*/

#include "LimitedCylinder.hpp"

LimitedCylinder::LimitedCylinder()
{
}

LimitedCylinder::LimitedCylinder(Vector3D bottom_center, Vector3D top_center, double r, std::shared_ptr<IMaterial> mate) {
    this->top_center = top_center;
    this->bottom_center = bottom_center;
    this->r = r;
    this->mate = mate;
}

bool LimitedCylinder::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    const double radius = this->r;
    const Vector3D& top_center = this->top_center;
    const Vector3D& bottom_center = this->bottom_center;
    const Vector3D& V = (top_center - bottom_center).normalized();

    const Vector3D& O = r.getOrigin();
    const Vector3D& D = r.getDirection();

    // Compute coefficients of the quadratic equation
    const Vector3D& CO = O - bottom_center;
    const double a = D.dot(D) - pow(D.dot(V), 2);
    const double b = 2 * (CO.dot(D) - (CO.dot(V) * D.dot(V)));
    const double c = CO.dot(CO) - pow(CO.dot(V), 2) - pow(radius, 2);

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
    Vector3D point, normal;
    if (t1 > t_min && t1 < t_max) {
        point = r.point_at_parameter(t1);
        if (point.getY() < bottom_center.getY() || point.getY() > top_center.getY()) {
            return false;
        }
        t = t1;
        normal = (point - bottom_center - V * (point - bottom_center).dot(V)).normalized();
    } else if (t2 > t_min && t2 < t_max) {
        point = r.point_at_parameter(t2);
        if (point.getY() < bottom_center.getY() || point.getY() > top_center.getY()) {
            return false;
        }
        t = t2;
        normal = (point - bottom_center - V * (point - bottom_center).dot(V)).normalized();
    } else {
        return false;
    }

    // Set hit record
    rec.setT(t);
    rec.setP(point);
    if (normal.dot(D) > 0) {
        normal = -normal;
    }
    rec.setNormal(normal);
    rec.setMatPtr(mate);

    return true;
}

bool LimitedCylinder::bounding_box(double t0, double t1, AABB& output_box) const {
    (void)t0;
    (void)t1;
    const double radius = this->r;
    const Vector3D& top_center = this->top_center;
    const Vector3D& bottom_center = this->bottom_center;

    const Vector3D& min = Vector3D(
        fmin(top_center.getX(), bottom_center.getX()) - radius,
        fmin(top_center.getY(), bottom_center.getY()),
        fmin(top_center.getZ(), bottom_center.getZ()) - radius
    );
    const Vector3D& max = Vector3D(
        fmax(top_center.getX(), bottom_center.getX()) + radius,
        fmax(top_center.getY(), bottom_center.getY()),
        fmax(top_center.getZ(), bottom_center.getZ()) + radius
    );

    output_box = AABB(min, max);

    return true;
}