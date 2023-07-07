/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Factory
*/

#include "Factory.hpp"

#include "Raytracing/Primitives/Sphere.hpp"
#include "Raytracing/Primitives/Box.hpp"
#include "Raytracing/Primitives/Triangle.hpp"
#include "Raytracing/Primitives/Cylinder.hpp"
#include "Raytracing/Primitives/LimitedCylinder.hpp"
#include "Raytracing/Primitives/Plane.hpp"

#include "Raytracing/Materials/Lambertian.hpp"
#include "Raytracing/Materials/Mirror.hpp"
#include "Raytracing/Materials/Dielectric.hpp"
#include "Raytracing/Materials/Lights.hpp"

RT::Factory::Factory()
{
}

RT::Factory::~Factory()
{
}

std::shared_ptr<IMaterial> RT::Factory::createMaterial(std::string name, std::vector<double> color, double reflectivity)
{
    std::map<std::string, std::shared_ptr<IMaterial>> _mat_tab = {
        {"lambertian", nullptr},
        {"mirror", nullptr},
        {"dielectric", nullptr},
        {"light", nullptr}
    };
    if (_mat_tab.find(name) != _mat_tab.end()) {

        //Parametres de fonction
        double r = 0.0;
        double g = 0.0;
        double b = 0.0;
        if (color.size() > 0)
            r = color[0];
        if (color.size() > 1)
            g = color[1];
        if (color.size() > 2)
            b = color[2];
        Color col = Color(r, g, b);
        col.toDouble();
        double _refl = reflectivity;

        auto lambertian = std::make_shared<Lambertian>(col);
        auto mirror = std::make_shared<Mirror>(col, _refl);
        auto dielectric = std::make_shared<Dielectric>(_refl);
        auto lights = std::make_shared<Lights>(col);

        std::map<std::string, std::shared_ptr<IMaterial>> _mat = {
            {"lambertian", lambertian},
            {"mirror", mirror},
            {"dielectric", dielectric},
            {"light", lights}
        };
        return _mat[name];
    }
    return nullptr;
}

PrimitivesList RT::Factory::create(std::vector<std::shared_ptr<RT::Parsing::IObjParser>> obj_parser)
{
    PrimitivesList list;

    //Ajout des objets dans la liste
    std::map<std::string, std::shared_ptr<IPrimitives>> _obj_tab = {
        {"Sphere", nullptr},
        {"Rectangle", nullptr},
        {"Triangle", nullptr},
        {"Box", nullptr},
        {"Cone", nullptr},
        {"Cylinder", nullptr},
        {"LimitedCylinder", nullptr},
        {"Plane", nullptr},
        {"LimitedCone", nullptr}
    };
    for (size_t i = 0; i < obj_parser.size(); i++) {
        if (_obj_tab.find(obj_parser[i]->getName()) != _obj_tab.end()) {

            //Parametres de fonction
            int index = 1;
            Vector3D point1 = Vector3D(0, 0, 0);
            Vector3D point2 = Vector3D(0, 0, 0);
            Vector3D point3 = Vector3D(0, 0, 0);
            Vector3D point4 = Vector3D(0, 0, 0);
            Vector3D director;
            double coord01 = 0.0;
            double coord02 = 0.0;
            double coord03 = 0.0;
            double coord04 = 0.0;

            for (size_t j = 0; j < obj_parser[i]->getPosRot("rotation").size(); j += 3) {
                double a = 0.0;
                double b = 0.0;
                double c = 0.0;
                if (j < obj_parser[i]->getPosRot("rotation").size())
                    a = obj_parser[i]->getPosRot("rotation")[j];
                if (j + 1 < obj_parser[i]->getPosRot("rotation").size())
                    b = obj_parser[i]->getPosRot("rotation")[j + 1];
                if (j + 2 < obj_parser[i]->getPosRot("rotation").size())
                    c = obj_parser[i]->getPosRot("rotation")[j + 2];
                director = Vector3D(a, b, c);
            }

            for (size_t j = 0; j < obj_parser[i]->getPosRot("position").size(); j += 3, index++) {
                double a = 0.0;
                double b = 0.0;
                double c = 0.0;
                if (j < obj_parser[i]->getPosRot("position").size())
                    a = obj_parser[i]->getPosRot("position")[j];
                if (j + 1 < obj_parser[i]->getPosRot("position").size())
                    b = obj_parser[i]->getPosRot("position")[j + 1];
                if (j + 2 < obj_parser[i]->getPosRot("position").size())
                    c = obj_parser[i]->getPosRot("position")[j + 2];
                if (index == 1) {
                    point1 = Vector3D(a, b, c);
                    coord01 = a;
                    coord02 = b;
                }
                if (index == 2) {
                    point2 = Vector3D(a, b, c);
                    coord03 = a;
                    coord04 = b;
                }
                if (index == 3)
                    point3 = Vector3D(a, b, c);
                if (index == 4)
                    point4 = Vector3D(a, b, c);
            }

            std::shared_ptr<IMaterial> _mat = createMaterial(obj_parser[i]->getMaterial(), obj_parser[i]->getMaterialColor(), obj_parser[i]->getMaterialReflection());

            double _radius = obj_parser[i]->getRadius();
            double height = obj_parser[i]->getHeight();
            double k = obj_parser[i]->getK();
            std::string name_bis = obj_parser[i]->getNameRect();

            //Construction des objets
            auto sphere = std::make_shared<Sphere>(point1, _radius, _mat);
            auto box = std::make_shared<Box>(point1, point2, _mat);
            auto triangle = std::make_shared<Triangle>(point1, point2, point3, _mat);
            auto plane = std::make_shared<Plane>(point1, point2, point3, _mat);
            auto cylinder = std::make_shared<Cylinder>(point1, director, _radius, _mat);
            auto limitedCylinder = std::make_shared<LimitedCylinder>(point1, director, _radius, _mat);
            auto rectangleXY = std::make_shared<XYRect>(coord01, coord02, coord03, coord04, k, _mat);
            auto rectangleXZ = std::make_shared<XZRect>(coord01, coord02, coord03, coord04, k, _mat);
            auto rectangleYZ = std::make_shared<YZRect>(coord01, coord02, coord03, coord04, k, _mat);

            //Ajout des objets dans la liste
            std::map<std::string, std::shared_ptr<IPrimitives>> _obj_final = {
                {"Sphere", sphere},
                {"Triangle", triangle},
                {"Plane", plane},
                {"Box", box},
                {"Cylinder", cylinder},
                {"LimitedCylinder", limitedCylinder},
                {"XY", rectangleXY},
                {"XZ", rectangleXZ},
                {"YZ", rectangleYZ}
            };

            if (_obj_final[obj_parser[i]->getName()] != nullptr) {
                list.add(_obj_final[obj_parser[i]->getName()]);
            } else if (_obj_final[obj_parser[i]->getNameRect()] != nullptr) {
                list.add(_obj_final[obj_parser[i]->getNameRect()]);
            }
        }
    }
    return (list);
}