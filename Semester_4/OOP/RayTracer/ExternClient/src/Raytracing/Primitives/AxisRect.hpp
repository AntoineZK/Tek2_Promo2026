/*
** EPITECH PROJECT, 2023
** RayTracing [WSL : Ubuntu]
** File description:
** AxisRect
*/

#pragma once
#include "IPrimitives.hpp"

class XYRect : public IPrimitives {
    public:
        XYRect();
        XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<IMaterial> mat);

        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        bool bounding_box(double time0, double time1, AABB& output_box) const;

        std::shared_ptr<IMaterial> getMaterial() const;
        double getX0() const;
        double getX1() const;
        double getY0() const;
        double getY1() const;
        double getK() const;
    private:
        std::shared_ptr<IMaterial> mat_ptr;
        double x0;
        double x1;
        double y0;
        double y1;
        double k;
};

class XZRect : public IPrimitives {
    public:
        XZRect();
        XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<IMaterial> mat);

        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        bool bounding_box(double time0, double time1, AABB& output_box) const;

        std::shared_ptr<IMaterial> getMaterial() const;
        double getX0() const;
        double getX1() const;
        double getZ0() const;
        double getZ1() const;
        double getK() const;
    private:
        std::shared_ptr<IMaterial> mat_ptr;
        double x0;
        double x1;
        double z0;
        double z1;
        double k;
};

class YZRect : public IPrimitives {
    public:
        YZRect();
        YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<IMaterial> mat);

        bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        bool bounding_box(double time0, double time1, AABB& output_box) const;

        std::shared_ptr<IMaterial> getMaterial() const;
        double getY0() const;
        double getY1() const;
        double getZ0() const;
        double getZ1() const;
        double getK() const;
    private:
        std::shared_ptr<IMaterial> mat_ptr;
        double y0;
        double y1;
        double z0;
        double z1;
        double k;
};
