/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** PrimitivesList
*/

#pragma once
#include "IPrimitives.hpp"

class PrimitivesList : public IPrimitives {
    public:
        PrimitivesList();
        PrimitivesList(std::shared_ptr<IPrimitives> object);
        void print();

        void clear();
        void add(std::shared_ptr<IPrimitives> object);
        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        bool bounding_box(double t0, double t1, AABB& output_box) const;

        std::vector<std::shared_ptr<IPrimitives>> getObjects() const;
    private:
        std::vector<std::shared_ptr<IPrimitives>> objects;
};
