/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ParserObj
*/

#pragma once
#include "../../../MainRaytracer/Include/Include.hpp"

namespace RT {
    class ParserObj {
        public:
            ParserObj();
            void create(std::string filepath);
            ~ParserObj();
            std::vector<std::map<long long, std::string>> getSmooths() const;
            std::vector<std::map<long long, std::string>> getMaterials() const;
            std::vector<std::vector<std::vector<double>>> getVerticesOfFaces(size_t pos) const;
            std::vector<std::vector<std::vector<double>>> getVerticesNormalsOfFaces(size_t pos) const;
            std::vector<std::vector<std::vector<double>>> getVerticesTexturesOfFaces(size_t pos) const;

            size_t getNbFaces() const;

        protected:
        private:
            std::vector<std::vector<double>> stock_vertices;
            std::vector<std::vector<double>> stock_vertices_normals;
            std::vector<std::vector<double>> stock_vertices_textures;
            std::vector<std::vector<std::vector<long long>>> stock_faces;
            std::vector<std::map<long long, std::string>> stock_smooths;
            std::vector<std::map<long long, std::string>> stock_materials;

            //Variables to know if the file has normals or textures
            std::vector<int> index;
            bool has_normals;
            bool has_textures;
    };
};
