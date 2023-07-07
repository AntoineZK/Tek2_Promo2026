/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Parser
*/

#pragma once

#include "../../../MainRaytracer/Include/Include.hpp"
#include "ParserObj.hpp"
#include "Factory.hpp"
#include "Camera/Camera.hpp"
#include "Light/Light.hpp"
#include "../Observer.hpp"
#include "../IObserver.hpp"
#include "../Manager.hpp"

namespace RT {
    class Parser {
        public:
            Parser();
            Parser(std::string filepath);
            ~Parser();
            void init(std::string filepath);
            std::vector<std::shared_ptr<RT::Parsing::IObjParser>> getInfo();
            RT::Parsing::Camera getInfoCam();
            RT::Parsing::Light getInfoLight();
            void fillObj(std::string str, std::map<std::string, RT::ParserObj>::iterator it, std::string name);
            void getClassObj(size_t begin, RT::ParserObj obj, std::string name);
            void getObj(libconfig::Setting& cfg, std::string name);
            void readFile(std::string filepath);
            void checkObj(libconfig::Setting& cfg, std::shared_ptr<RT::Parsing::IObjParser> &obj, std::string name);

        protected:
        private:
            libconfig::Config _cfg;
            std::vector<std::shared_ptr<RT::Parsing::IObjParser>> _obj;
            RT::Parsing::Camera _camera;
            RT::Parsing::Light _light;
            std::map<std::string, std::vector<std::shared_ptr<RT::Parsing::IObjParser>>> _obj_map;
            std::map<std::string, RT::ParserObj> _filepath;
    };
};
