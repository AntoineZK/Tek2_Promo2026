/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** HitRecord
*/

#pragma once
#include "../Ray.hpp"

class IMaterial;

class HitRecord {
    public:
        HitRecord();

        void set_face_normal(const Ray &r, const Vector3D &outward_normal);

        Vector3D getP() const;
        Vector3D getNormal() const;
        std::shared_ptr<IMaterial> getMatPtr() const;
        double getT() const;
        bool isFrontFace() const;
        double getU() const;
        double getV() const;

        void setP(const Vector3D &p);
        void setNormal(const Vector3D &normal);
        void setMatPtr(const std::shared_ptr<IMaterial> &matPtr);
        void setT(double t);
        void setFrontFace(bool frontFace);
        void setU(double u);
        void setV(double v);

    private:
        Vector3D p;
        Vector3D normal;
        std::shared_ptr<IMaterial> mat_ptr;
        double t;
        bool front_face;
        double u;
        double v;
};
