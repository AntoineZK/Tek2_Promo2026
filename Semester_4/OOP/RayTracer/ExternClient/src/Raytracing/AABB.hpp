/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** AABB
*/

#pragma once
#include "Ray.hpp"

/**
 * @brief La classe AABB représente une boîte englobante alignée sur les axes ce qui nous permet de vérifier si un rayon touche la boîte englobante.
 * Et donc d'eviter de calculer l'intersection avec tous les objets de la scène si le rayon ne touche pas la boîte englobante qui contient l'objet.
 */
class AABB {
    public:
        /**
         * @brief Constructeur par défaut de la classe AABB.
         */
        AABB();

        /**
         * @brief Constructeur de la classe AABB avec deux points spécifiés.
         * @param a Le premier coin de la boîte.
         * @param b Le deuxième coin de la boîte.
         */
        AABB(const Point3D& a, const Point3D& b);

        /**
         * @brief Vérifie si un rayon touche la boîte englobante.
         * @param r Le rayon à vérifier.
         * @param t_min La valeur minimale du paramètre de temps t.
         * @param t_max La valeur maximale du paramètre de temps t.
         * @return true si le rayon touche la boîte englobante, false sinon.
         */
        bool hit(const Ray& r, double t_min, double t_max) const;

        /**
         * @brief Calcule la boîte englobante qui contient deux boîtes spécifiées.
         * @param box0 La première boîte.
         * @param box1 La deuxième boîte.
         * @return La boîte englobante résultante.
         */
        static AABB surrounding_box(AABB box0, AABB box1);

        /**
         * @brief Retourne le coin minimum de la boîte englobante.
         * @return Le coin minimum de la boîte.
         */
        Point3D getMin() const;

        /**
         * @brief Retourne le coin maximum de la boîte englobante.
         * @return Le coin maximum de la boîte.
         */
        Point3D getMax() const;

    private:
        Point3D minimum; /**< Le coin minimum de la boîte englobante. */
        Point3D maximum; /**< Le coin maximum de la boîte englobante. */
};
