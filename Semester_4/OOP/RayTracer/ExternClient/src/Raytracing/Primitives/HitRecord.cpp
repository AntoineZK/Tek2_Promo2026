/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** HitRecord
*/

#include "HitRecord.hpp"

HitRecord::HitRecord()
{
    this->p = Vector3D(0, 0, 0);
    this->normal = Vector3D(0, 0, 0);
    this->mat_ptr = nullptr;
    this->t = 0;
    this->front_face = false;
}

void HitRecord::set_face_normal(const Ray &r, const Vector3D &outward_normal)
{
    this->front_face = Vector3D::dot(r.getDirection(), outward_normal) < 0;
    this->normal = this->front_face ? outward_normal : -outward_normal;
}

// Getters

Vector3D HitRecord::getP() const
{
    return this->p;
}

Vector3D HitRecord::getNormal() const
{
    return this->normal;
}

std::shared_ptr<IMaterial> HitRecord::getMatPtr() const
{
    return this->mat_ptr;
}

double HitRecord::getT() const
{
    return this->t;
}

bool HitRecord::isFrontFace() const
{
    return this->front_face;
}

double HitRecord::getU() const
{
    return this->u;
}

double HitRecord::getV() const
{
    return this->v;
}

// Setters

void HitRecord::setP(const Vector3D &p)
{
    this->p = p;
}

void HitRecord::setNormal(const Vector3D &normal)
{
    this->normal = normal;
}

void HitRecord::setMatPtr(const std::shared_ptr<IMaterial> &matPtr)
{
    this->mat_ptr = matPtr;
}

void HitRecord::setT(double t)
{
    this->t = t;
}

void HitRecord::setFrontFace(bool frontFace)
{
    this->front_face = frontFace;
}

void HitRecord::setU(double u)
{
    this->u = u;
}

void HitRecord::setV(double v)
{
    this->v = v;
}
