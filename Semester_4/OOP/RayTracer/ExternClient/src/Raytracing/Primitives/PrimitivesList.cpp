/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** PrimitivesList
*/

#include "PrimitivesList.hpp"

PrimitivesList::PrimitivesList()
{
}

PrimitivesList::PrimitivesList(std::shared_ptr<IPrimitives> object)
{
    this->add(object);
}

// Methods

void PrimitivesList::clear()
{
    this->objects.clear();
}

void PrimitivesList::add(std::shared_ptr<IPrimitives> object)
{
    this->objects.push_back(object);
}

bool PrimitivesList::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    // Test si le rayon intersect avec toutes les primitives de la scène
    // Si oui, on récupère la primitive la plus proche de la caméra, et les informations de l'intersection,
    // et on retourne true
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object : this->objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.getT();
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool PrimitivesList::bounding_box(double t0, double t1, AABB &output_box) const
{
    if (this->objects.empty())
        return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto &object : this->objects) {
        if (!object->bounding_box(t0, t1, temp_box))
            return false;
        output_box = first_box ? temp_box : AABB::surrounding_box(output_box, temp_box);
        first_box = false;
    }
    return true;
}

// Getters

std::vector<std::shared_ptr<IPrimitives>> PrimitivesList::getObjects() const
{
    return this->objects;
}

void PrimitivesList::print()
{
    
}