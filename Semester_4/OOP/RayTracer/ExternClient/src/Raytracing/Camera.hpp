/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#pragma once
#include "Ray.hpp"

namespace RT {
    class Camera {
        public:
            /**
             * @brief Construit un objet Camera avec les paramètres spécifiés.
             * @param ori Le point d'origine de la caméra.
             * @param rota Le point de rotation de la caméra.
             * @param fov Le champ de vision de la caméra en degrés.
             * @param reso La résolution de la caméra sous la forme d'une paire d'entiers (largeur, hauteur).
             * @param depth La profondeur maximale pour le lancer de rayons.
             * @param raypp Le nombre de rayons par pixel pour l'anti-aliasing.
             * @param aper L'ouverture de l'objectif de la caméra.
             * @param focDist La distance focale de la caméra.
             * @param time0 Le temps de début de l'exposition de la caméra.
             * @param time1 Le temps de fin de l'exposition de la caméra.
             */
            Camera(Point3D ori, Point3D rota, double fov, std::pair<int, int> reso, int depth, int raypp, double aper, double focDist, double time0 = 0.0, double time1 = 0.0);

            /**
             * @brief Renvoie un rayon de la caméra passant par les coordonnées spécifiées (s, t).
             * @param s La coordonnée horizontale normalisée dans la plage [0, 1].
             * @param t La coordonnée verticale normalisée dans la plage [0, 1].
             * @return Un objet Ray représentant le rayon de la caméra.
             */
            Ray get_ray(double s, double t);

            Point3D getLowerLeftCorner() const;
            Vector3D getHorizontal() const;
            Vector3D getVertical() const;
            Vector3D getU() const;
            Vector3D getV() const;
            Vector3D getW() const;
            double getLensRadius() const;
            Point3D getOrigin() const;
            Point3D getRotation() const;
            double getFieldOfView() const;
            std::pair<int, int> getResolution() const;
            int getMaxDepth() const;
            int getRayPerPixel() const;
            double getTime0() const;
            double getTime1() const;

        private:
            Point3D lower_left_corner;
            Vector3D horizontal;
            Vector3D vertical;
            Vector3D u, v, w;
            double lens_radius;
            Point3D origin;
            Point3D rotation;
            double fieldOfView;
            std::pair<int, int> resolution;
            int maxDepth;
            int rayPerPixel;
            double time0, time1;
    };
};