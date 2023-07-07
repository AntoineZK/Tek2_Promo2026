/*
** EPITECH PROJECT, 2023
** RayTracing [WSL: Ubuntu]
** Description:
** AABB (Aligned Axis Bounding Box)
*/

#include "AABB.hpp"

AABB::AABB()
{
    // Constructeur par défaut de la classe AABB
}

AABB::AABB(const Point3D& a, const Point3D& b)
{
    // Constructeur de la classe AABB avec deux points spécifiés
    this->minimum = a;
    this->maximum = b;
}

// Méthodes

bool AABB::hit(const Ray& r, double tmin, double tmax) const
{
    // Vérifie si un rayon touche la boîte englobante
    for (int i = 0; i < 3; i++) {
        auto invD = 1.0f / r.getDirection()[i];
        auto t0 = (this->minimum[i] - r.getOrigin()[i]) * invD;
        auto t1 = (this->maximum[i] - r.getOrigin()[i]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        if (tmax <= tmin)
            return false;
    }
    return true;
}

AABB AABB::surrounding_box(AABB box0, AABB box1)
{
    // Calcule la boîte englobante qui contient deux boîtes spécifiées
    Point3D small(fmin(box0.getMin().getX(), box1.getMin().getX()),
                fmin(box0.getMin().getY(), box1.getMin().getY()),
                fmin(box0.getMin().getZ(), box1.getMin().getZ()));

    Point3D big(fmax(box0.getMax().getX(), box1.getMax().getX()),
                fmax(box0.getMax().getY(), box1.getMax().getY()),
                fmax(box0.getMax().getZ(), box1.getMax().getZ()));

    return AABB(small, big);
}

// Getters

Point3D AABB::getMin() const
{
    // Retourne le coin minimum de la boîte englobante
    return this->minimum;
}

Point3D AABB::getMax() const
{
    // Retourne le coin maximum de la boîte englobante
    return this->maximum;
}
