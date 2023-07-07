/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Ray
*/

#include "Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(const Point3D &a, const Vector3D &b, double time)
{
    this->ori = a;
    this->direc = b;
    this->time = time;
}

// Methods

Point3D Ray::point_at_parameter(double t) const
{
    // On calcule la position du point en fonction d'un paramètre t qui controle la position le long du rayon.
    return this->ori + t * this->direc;
}

// Getters

Vector3D Ray::getOrigin() const
{
    return this->ori;
}

Vector3D Ray::getDirection() const
{
    return this->direc;
}

double Ray::getTime() const
{
    return this->time;
}
