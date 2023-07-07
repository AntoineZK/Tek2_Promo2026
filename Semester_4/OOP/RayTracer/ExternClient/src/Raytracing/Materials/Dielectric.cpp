/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Dielectric
*/

#include "Dielectric.hpp"

Dielectric::Dielectric(double ri)
{
    this->ref_idx = ri;
}

// Methods

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.isFrontFace() ? (1.0 / this->ref_idx) : this->ref_idx;

    Vector3D unit_direction = Vector3D::unit_vector(r_in.getDirection());
    double cos_theta = fmin(Vector3D::dot(-unit_direction, rec.getNormal()), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vector3D direction;

    if (cannot_refract || Vector3D::schlick(cos_theta, refraction_ratio) > RT::Random::Utils::random_double())
        direction = Vector3D::reflect(unit_direction, rec.getNormal());
    else
        direction = Vector3D::refract(unit_direction, rec.getNormal(), refraction_ratio);

    scattered = Ray(rec.getP(), direction, r_in.getTime());
    return true;
}

Color Dielectric::emitted(double u, double v, const Point3D &p) const
{
    (void)u;
    (void)v;
    (void)p;
    return (Color(0, 0, 0));
}

// Getters

double Dielectric::getRefIdx() const
{
    return this->ref_idx;
}
