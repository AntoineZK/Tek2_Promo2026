/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Vector3D
*/

#pragma once
#include "../Include.hpp"

class Vector3D  {
    public:
        Vector3D();
        Vector3D(double a, double b, double c);
        double getX() const;
        double getY() const;
        double getZ() const;
        double getR() const;
        double getG() const;
        double getB() const;

        void setX(double x);
        void setY(double y);
        void setZ(double z);
        void setR(double r);
        void setG(double g);
        void setB(double b);

        const Vector3D& operator+() const;
        Vector3D operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        Vector3D& operator+=(const Vector3D &v2);
        Vector3D& operator-=(const Vector3D &v2);
        Vector3D& operator*=(const Vector3D &v2);
        Vector3D& operator/=(const Vector3D &v2);
        Vector3D& operator*=(const double t);
        Vector3D& operator/=(const double t);
        Vector3D operator+(const Vector3D &v2) const;
        Vector3D operator-(const Vector3D &v2) const;
        Vector3D operator*(const Vector3D &v2) const;
        Vector3D operator/(const Vector3D &v2) const;
        Vector3D operator*(const double t) const;
        Vector3D operator/(const double t) const;

        void toDouble();
        double length() const;
        double squared_length() const;
        void make_unit_vector();
        static double dot(const Vector3D &v1, const Vector3D &v2);
        static Vector3D cross(const Vector3D &v1, const Vector3D &v2);
        static Vector3D unit_vector(Vector3D v);
        static Vector3D reflect(const Vector3D& v, const Vector3D& n);
        static Vector3D random_in_unit_sphere(void);
        static double schlick(double cosine, double ref_idx);
        static Vector3D random_in_unit_disk(void);
        static Vector3D random_vector();
        static Vector3D random_vector(double min, double max);
        static Vector3D refract(const Vector3D& uv, const Vector3D& n, double etai_over_etat);
        double dot(const Vector3D &v2) const;
        Vector3D normalized() const;
    private:
        double x;
        double y;
        double z;
};

using Point3D = Vector3D;
using Color = Vector3D;

std::ostream& operator<<(std::ostream &os, const Vector3D &t);
Vector3D operator*(double t, const Vector3D &v);
double dot(const Vector3D &v1, const Vector3D &v2);
Vector3D cross(const Vector3D &v1, const Vector3D &v2);
Vector3D unitVector(Vector3D v);