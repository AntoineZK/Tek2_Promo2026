/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

Vector3D::Vector3D()
{
}

Vector3D::Vector3D(double a, double b, double c)
{
    this->x = a;
    this->y = b;
    this->z = c;
}

// Getters

double Vector3D::getX() const
{
    return this->x;
}

double Vector3D::getY() const
{
    return this->y;
}

double Vector3D::getZ() const
{
    return this->z;
}

double Vector3D::getR() const
{
    return this->x;
}

double Vector3D::getG() const
{
    return this->y;
}

double Vector3D::getB() const
{
    return this->z;
}

// Setters

void Vector3D::setX(double x)
{
    this->x = x;
}

void Vector3D::setY(double y)
{
    this->y = y;
}

void Vector3D::setZ(double z)
{
    this->z = z;
}

void Vector3D::setR(double r)
{
    this->x = r;
}

void Vector3D::setG(double g)
{
    this->y = g;
}

void Vector3D::setB(double b)
{
    this->z = b;
}

// Operators

const Vector3D &Vector3D::operator+() const
{
    return *this;
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

double Vector3D::operator[](int i) const
{
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    return z;
}

double &Vector3D::operator[](int i)
{
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    return z;
}

Vector3D &Vector3D::operator+=(const Vector3D &v2)
{
    x += v2.x;
    y += v2.y;
    z += v2.z;
    return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &v2)
{
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
    return *this;
}

Vector3D &Vector3D::operator*=(const Vector3D &v2)
{
    x *= v2.x;
    y *= v2.y;
    z *= v2.z;
    return *this;
}

Vector3D &Vector3D::operator/=(const Vector3D &v2)
{
    x /= v2.x;
    y /= v2.y;
    z /= v2.z;
    return *this;
}

Vector3D &Vector3D::operator*=(const double t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vector3D &Vector3D::operator/=(const double t)
{
    double k = 1.0 / t;
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &v2) const
{
    return Vector3D(x + v2.x, y + v2.y, z + v2.z);
}

Vector3D Vector3D::operator-(const Vector3D &v2) const
{
    return Vector3D(x - v2.x, y - v2.y, z - v2.z);
}

Vector3D Vector3D::operator*(const Vector3D &v2) const
{
    return Vector3D(x * v2.x, y * v2.y, z * v2.z);
}

Vector3D Vector3D::operator/(const Vector3D &v2) const
{
    return Vector3D(x / v2.x, y / v2.y, z / v2.z);
}

Vector3D Vector3D::operator*(double t) const
{
    return Vector3D(x * t, y * t, z * t);
}

Vector3D Vector3D::operator/(double t) const
{
    double k = 1.0 / t;
    return Vector3D(x * k, y * k, z * k);
}

// Methods

void Vector3D::toDouble()
{
    x /= 255;
    y /= 255;
    z /= 255;
}

double Vector3D::length() const
{
    return sqrt(x * x + y * y + z * z);
}

double Vector3D::squared_length() const
{
    return x * x + y * y + z * z;
}

void Vector3D::make_unit_vector()
{
    double k = 1.0 / sqrt(x * x + y * y + z * z);
    x *= k;
    y *= k;
    z *= k;
}

Vector3D Vector3D::random_vector()
{
    return Vector3D(RT::Random::Utils::random_double(), RT::Random::Utils::random_double(), RT::Random::Utils::random_double());
}

Vector3D Vector3D::random_vector(double min, double max)
{
    return Vector3D(RT::Random::Utils::random_double(min, max), RT::Random::Utils::random_double(min, max), RT::Random::Utils::random_double(min, max));
}

double Vector3D::dot(const Vector3D &v1, const Vector3D &v2)
{
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

double Vector3D::dot(const Vector3D &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
                    v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
                    v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

Vector3D Vector3D::unit_vector(Vector3D v)
{
    return v / v.length();
}

Vector3D Vector3D::reflect(const Vector3D &v, const Vector3D &n)
{
    return v - 2 * Vector3D::dot(v, n) * n;
}

Vector3D Vector3D::random_in_unit_sphere(void)
{
    Vector3D p;
    do {
        p = 2.0 * Vector3D(RT::Random::Utils::random_double(), RT::Random::Utils::random_double(), RT::Random::Utils::random_double()) - Vector3D(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return (p);
}

Vector3D Vector3D::refract(const Vector3D& uv, const Vector3D& n, double etai_over_etat) {
    auto cos_theta = fmin(Vector3D::dot(-uv, n), 1.0);
    Vector3D r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vector3D r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squared_length())) * n;
    return r_out_perp + r_out_parallel;
}

double Vector3D::schlick(double cosine, double ref_idx)
{
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Vector3D Vector3D::random_in_unit_disk(void)
{
    Vector3D p;
    do {
        p = 2.0 * Vector3D(RT::Random::Utils::random_double(), RT::Random::Utils::random_double(), 0) - Vector3D(1, 1, 0);
    } while (Vector3D::dot(p, p) >= 1.0);
    return p;
}

// Non-member functions

std::ostream &operator<<(std::ostream &os, const Vector3D &t)
{
    os << t.getX() << " " << t.getY() << " " << t.getZ();
    return os;
}

Vector3D operator*(double t, const Vector3D &v)
{
    return Vector3D(t * v.getX(), t * v.getY(), t * v.getZ());
}

double dot(const Vector3D &v1, const Vector3D &v2)
{
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

Vector3D cross(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
                    v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
                    v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

Vector3D unitVector(Vector3D v)
{
    return v / v.length();
}

Vector3D Vector3D::normalized() const
{
    double l = length();
    return Vector3D(x / l, y / l, z / l);
}