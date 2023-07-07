/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** ChessTexture
*/

#pragma once
#include "ColorTexture.hpp"
/**
 * @brief La classe ChessTexture représente une texture de damier.
*/

class ChessTexture : public ITextures {
    public:
        /**
         * @brief Constructeur par défaut de la classe ChessTexture.
         */
        ChessTexture();
        /**
         * @brief Constructeur de la classe ChessTexture avec deux textures spécifiées.
         * @param even La première texture (Case pair)
         * @param odd La deuxième texture (Case impair)
         */
        ChessTexture(std::shared_ptr<ITextures> even, std::shared_ptr<ITextures> odd);

        /**
         * @brief Constructeur de la classe ChessTexture avec deux couleurs spécifiées.
         * @param even La première couleur (Case pair)
         * @param odd La deuxième couleur (Case impair)
         */
        ChessTexture(const Color &even, const Color &odd);

        /**
         * @brief Retourne la couleur de la texture en fonction des coordonnées UV et du point p.
         * @param u La coordonnée u.
         * @param v La coordonnée v.
         * @param p Le point p.
         * @return La couleur de la texture.
         */
        Color value(double u, double v, const Point3D &p) const;

        std::shared_ptr<ITextures> getOdd() const;
        std::shared_ptr<ITextures> getEven() const;
    private:
        std::shared_ptr<ITextures> odd;
        std::shared_ptr<ITextures> even;
};
