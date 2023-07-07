/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Lambertian
*/

#include "Lambertian.hpp"

Lambertian::Lambertian(const Vector3D &a)
{
    this->albedo = std::make_shared<ColorTexture>(a);
}

Lambertian::Lambertian(std::shared_ptr<ITextures> a)
{
    this->albedo = a;
}

// Methods

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Vector3D &attenuation, Ray &scattered) const
{
    // Calcule du point cible du rayon diffusé
    Vector3D target = rec.getP() + rec.getNormal() + Vector3D::random_in_unit_sphere();

    // On calcule le rayon diffusé en fonction du point d'intersection et du point cible
    scattered = Ray(rec.getP(), target - rec.getP(), r_in.getTime());

    // On applique l'albedo du matériau (couleur) pour le rayon diffusé
    attenuation = this->albedo->value(rec.getU(), rec.getV(), rec.getP());

    // Vu que un materiaux Lambertian (Mate) diffuse la lumière dans toutes les directions on retourne true
    return (true);
}

Color Lambertian::emitted(double u, double v, const Point3D &p) const
{
    (void)u;
    (void)v;
    (void)p;
    // Le lambertian ne diffuse pas de lumière donc on retourne du noir
    return (Color(0, 0, 0));
}

// Getters

std::shared_ptr<ITextures> Lambertian::getAlbedo() const
{
    return this->albedo;
}
