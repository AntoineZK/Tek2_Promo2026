/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Mirror
*/

#include "Mirror.hpp"

Mirror::Mirror(const Vector3D &a, double f)
{
    this->albedo = a;
    if (f < 1)
        this->fuzz = f;
    else
        this->fuzz = 1;
}

// Methods

bool Mirror::scatter(const Ray &r_in, const HitRecord &rec, Vector3D &attenuation, Ray &scattered) const
{
    // Calcule la direction réfléchie du rayon incident
    Vector3D reflected = Vector3D::reflect(Vector3D::unit_vector(r_in.getDirection()), rec.getNormal());

    // On applique un flou au rayon réfléchi
    scattered = Ray(rec.getP(), reflected + this->fuzz * Vector3D::random_in_unit_sphere(), r_in.getTime());

    // On applique l'albedo du matériau (couleur)
    attenuation = this->albedo;

    // On check si le rayon diffusé est dans la même direction que la normale si oui on le diffuse sinon non
    return (Vector3D::dot(scattered.getDirection(), rec.getNormal()) > 0);
}

Color Mirror::emitted(double u, double v, const Point3D &p) const
{
    (void)u;
    (void)v;
    (void)p;
    // Le mirroir ne diffuse pas de lumière donc on retourne du noir
    return (Color(0, 0, 0));
}

// Getters

Vector3D Mirror::getAlbedo() const
{
    return this->albedo;
}

double Mirror::getFuzz() const
{
    return this->fuzz;
}
