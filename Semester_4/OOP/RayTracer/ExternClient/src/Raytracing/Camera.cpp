/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Camera
*/

#include "Camera.hpp"

RT::Camera::Camera(Point3D ori, Point3D rota, double fov, std::pair<int, int> reso, int depth, int raypp, double aper, double focDist, double time0, double time1)
{
    // Utiliser les paramètres spécifiés pour initialiser les attributs de la caméra.
    this->origin = ori;
    this->rotation = rota;
    this->fieldOfView = fov;
    this->resolution = reso;
    this->maxDepth = depth;
    this->rayPerPixel = raypp;
    this->time0 = time0;
    this->time1 = time1;

    // Calculer le rayon de l'objectif comme pour une lentille pour pouvoir calculer le flou de l'objectif.
    this->lens_radius = aper / 2;

    // Calculer les demi-angles pour pouvoir calculer le FOV
    double theta = Random::Utils::degrees_to_radians(this->fieldOfView);
    double aspect = (double)this->resolution.first / (double)this->resolution.second;
    double half_height = tan(theta / 2);
    double half_width = aspect * half_height;

    // Calculer les vecteurs de base pour la caméra
    w = Vector3D::unit_vector(this->origin - this->rotation);
    u = Vector3D::unit_vector(Vector3D::cross(Vector3D(0, 1, 0), w));
    v = Vector3D::cross(w, u);

    // Calculer le coin inférieur gauche du rectangle de vue pour la caméra car cela permet de calculer les autres coins.
    this->lower_left_corner = this->origin - half_width * focDist * u - half_height * focDist * v - focDist * w;

    // Calculer les dimensions horizontales et verticales du rectangle de vue.
    this->horizontal = 2 * half_width * focDist * u;
    this->vertical = 2 * half_height * focDist * v;
}

// Methods

Ray RT::Camera::get_ray(double s, double t)
{
    // On genere des valeurs aléatoires pour pouvoir generer un effet de profondeur de champ.
    Vector3D rd = this->lens_radius * Vector3D::random_in_unit_disk();
    Vector3D offset = this->u * rd.getX() + this->v * rd.getY();

    // On calcule la direction du rayon en fonction de la position du pixel et de la position de la caméra pour pouvoir le générer.
    Vector3D direction = this->lower_left_corner + s * this->horizontal + t * this->vertical - this->origin - offset;

    // Générer un temps aléatoire dans la durée d'exposition (Utile dans le cas d'un mouvement.)
    double randomTime = Random::Utils::random_double(this->time0, this->time1);

    // Créer et retourner le rayon de la caméra.
    return Ray(this->origin + offset, direction, randomTime);
}

// Getters

Point3D RT::Camera::getLowerLeftCorner() const
{
    return this->lower_left_corner;
}

Vector3D RT::Camera::getHorizontal() const
{
    return this->horizontal;
}

Vector3D RT::Camera::getVertical() const
{
    return this->vertical;
}

Vector3D RT::Camera::getU() const
{
    return this->u;
}

Vector3D RT::Camera::getV() const
{
    return this->v;
}

Vector3D RT::Camera::getW() const
{
    return this->w;
}

double RT::Camera::getLensRadius() const
{
    return this->lens_radius;
}

Point3D RT::Camera::getOrigin() const
{
    return this->origin;
}

Point3D RT::Camera::getRotation() const
{
    return this->rotation;
}

double RT::Camera::getFieldOfView() const
{
    return this->fieldOfView;
}

std::pair<int, int> RT::Camera::getResolution() const
{
    return this->resolution;
}

int RT::Camera::getMaxDepth() const
{
    return this->maxDepth;
}

int RT::Camera::getRayPerPixel() const
{
    return this->rayPerPixel;
}

double RT::Camera::getTime0() const
{
    return this->time0;
}

double RT::Camera::getTime1() const
{
    return this->time1;
}
