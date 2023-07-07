/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Sphere
*/

#include "Sphere.hpp"

Sphere::Sphere()
{
}

Sphere::Sphere(Point3D center, double radius, std::shared_ptr<IMaterial> mat)
{
    this->center = center;
    this->radius = radius;
    this->mate = mat;
}

// Methods

void Sphere::getSphericalUV(const Vector3D &p, double &u, double &v)
{
    auto theta = acos(-p.getY());
    auto phi = atan2(-p.getZ(), p.getX()) + M_PI;

    u = phi / (2 * M_PI);
    v = theta / M_PI;
}

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    //Pour toutes les primitives c'est le meme principe, pour calculer si si il y a une intersections,
    //on calcule les coefficients de l'équation de la droite (rayon) et de la sphère, et on résout l'équation
    // si le discriminant est négatif, il n'y a pas d'intersection
    // si le discriminant est nul, il y a une intersection (donc pour une sphere on est sur le bord)
    // si le discriminant est positif, il y a deux intersections

    Vector3D oc = r.getOrigin() - this->center;
    auto a = r.getDirection().squared_length();
    auto half_b = Vector3D::dot(oc, r.getDirection());
    auto c = oc.squared_length() - this->radius * this->radius;

    auto discriminant = half_b * half_b - a * c; // b² - 4ac
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }
    // tous les rapports a U et V sont pour la texture
    double u = rec.getU();
    double v = rec.getV();
    rec.setT(root);
    rec.setP(r.point_at_parameter(rec.getT()));
    Vector3D outward_normal = (rec.getP() - this->center) / this->radius;
    rec.set_face_normal(r, outward_normal);
    getSphericalUV(outward_normal, u, v);
    rec.setMatPtr(this->mate);
    return true;
}

bool Sphere::bounding_box(double t0, double t1, AABB &output_box) const
{
    (void)t0;
    (void)t1;
    Point3D min = this->center - Vector3D(this->radius, this->radius, this->radius);
    Point3D max = this->center + Vector3D(this->radius, this->radius, this->radius);
    output_box = AABB(min, max);
    return true;
}

// Getters

Point3D Sphere::getCenter() const
{
    return this->center;
}

double Sphere::getRadius() const
{
    return this->radius;
}

std::shared_ptr<IMaterial> Sphere::getMaterial() const
{
    return this->mate;
}
