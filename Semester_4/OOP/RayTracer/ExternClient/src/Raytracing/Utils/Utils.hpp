/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Utils
*/

#pragma once
#include "../Include.hpp"
#include "../Math/Vector3D.hpp"
#include "../Ray.hpp"
#include "../Primitives/IPrimitives.hpp"

namespace RT {
    namespace Calcul {
        namespace Utils {
            void writeColor(std::ostream &out, Color pixelColor);
            Color applyGamma(Color actColor, double gamma, int rayPerPixel);
            Color rayColor(const Ray &r, const Color& background, const IPrimitives &world, int depth);
            double clamp(double x, double min, double max);
            Color toRGB(Color actColor);
        }
    }
}