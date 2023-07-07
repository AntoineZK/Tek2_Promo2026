/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** IMaterial
*/

#pragma once
#include "../Primitives/HitRecord.hpp"

/**
 * @brief Interface pour les matériaux utilisés dans le raytracer.
 */
class IMaterial {
public:
    /**
     * @brief Fonction virtuelle pure pour calculer la diffusion d'un rayon sur un matériau.
     * @param r_in Le rayon incident.
     * @param rec Les informations sur le point d'intersection avec la surface.
     * @param attenuation La couleur d'atténuation du matériau.
     * @param scattered Le rayon diffusé (réfléchi ou réfracté).
     * @return True si le rayon est diffusé, false sinon.
     */
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;

    /**
     * @brief Fonction virtuelle pure pour calculer la couleur émise par le matériau.
     * @param u La coordonnée u de la texture.
     * @param v La coordonnée v de la texture.
     * @param p Le point sur la surface du matériau.
     * @return La couleur émise par le matériau.
     */
    virtual Color emitted(double u, double v, const Point3D& p) const = 0;
};
