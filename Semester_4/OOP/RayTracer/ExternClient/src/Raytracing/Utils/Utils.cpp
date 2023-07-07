/*
** EPITECH PROJECT, 2023
** RayTracing
** File description:
** Utils
*/

#include "Utils.hpp"
#include "../Materials/IMaterial.hpp"

namespace RT {
    namespace Calcul {
        namespace Utils {

            void writeColor(std::ostream &out, Color pixelColor)
            {
                // On écrit les composantes RGB de la couleur du pixel en version 255 255 255 (pour pouvoir l'afficher avec un visualisateur d'image)
                pixelColor = RT::Calcul::Utils::toRGB(pixelColor);
                int r = static_cast<int>(pixelColor.getR());
                int g = static_cast<int>(pixelColor.getG());
                int b = static_cast<int>(pixelColor.getB());
                out << r << ' ' << g << ' ' << b << '\n';
            }

            Color applyGamma(Color actColor, double gamma, int rayPerPixel)
            {
                // On applique la correction gamma : on prend la racine carrée de la couleur et on multiplie par le nombre de rayons par pixel

                double scale = gamma / rayPerPixel;
                double r = sqrt(scale * actColor.getR());
                double g = sqrt(scale * actColor.getG());
                double b = sqrt(scale * actColor.getB());
                return Color(r, g, b);
            }

            Color rayColor(const Ray &r, const Color& background, const IPrimitives &world, int depth)
            {
                HitRecord rec;
                // Si on dépasse le nombre maximum de rebond on retourne du noir.
                if (depth <= 0)
                    return Color(0, 0, 0);

                // Si on ne touche rien on retourne la couleur de fond.
                if (!world.hit(r, 0.001, infinity, rec))
                    return background;

                Ray scattered;
                Color attenuation;
                // On récupère la couleur émise par le matériau (Rouge, mirroir etc...)
                Color emitted = rec.getMatPtr()->emitted(rec.getU(), rec.getV(), rec.getP());

                // Si on ne peut pas diffuser la lumière on retourne la couleur émise.
                if (!rec.getMatPtr()->scatter(r, rec, attenuation, scattered))
                    return emitted;

                // On retourne la couleur émise + la couleur diffusée, on diminue la profondeur de 1 pour chaque rebond jusqu'à atteindre 0.
                // Si on atteint 0 on retourne du noir sinon on continue de calculer la couleur.

                return emitted + attenuation * rayColor(scattered, background, world, depth - 1);
            }

            double clamp(double x, double min, double max)
            {
                if (x < min)
                    return min;
                if (x > max)
                    return max;
                return x;
            }

            Color toRGB(Color actColor)
            {
                int r = static_cast<int>(256 * Utils::clamp(actColor.getR(), 0.0, 0.999));
                int g = static_cast<int>(256 * Utils::clamp(actColor.getG(), 0.0, 0.999));
                int b = static_cast<int>(256 * Utils::clamp(actColor.getB(), 0.0, 0.999));
                return Color(r, g, b);
            }
        }
    }
}