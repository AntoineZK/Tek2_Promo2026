/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** ParserObj
*/

#include "ParserObj.hpp"

static std::vector<long long> getVertex(std::string line, int nb_v)
{
    std::vector<long long> vertex;
    long long vIndex1 = 0, vIndex2 = 0, vIndex3 = 0, vIndex4 = 0, vIndex5 = 0
    , vIndex6 = 0, vIndex7 = 0, vIndex8 = 0, vIndex9 = 0, vIndex10 = 0
    , vIndex11 = 0, vIndex12 = 0;
    int nb = 0;

    if (nb_v == 2) {
        nb = std::sscanf(line.c_str(), "f %lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6, &vIndex7, &vIndex8, &vIndex9, &vIndex10, &vIndex11, &vIndex12);
        if (nb == 12) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            vertex.push_back(vIndex7);
            vertex.push_back(vIndex8);
            vertex.push_back(vIndex9);
            vertex.push_back(vIndex10);
            vertex.push_back(vIndex11);
            vertex.push_back(vIndex12);
            return (vertex);
        }
        nb = std::sscanf(line.c_str(), "f %lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6, &vIndex7, &vIndex8, &vIndex9);
        if (nb == 9) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            vertex.push_back(vIndex7);
            vertex.push_back(vIndex8);
            vertex.push_back(vIndex9);
            return (vertex);
        }
    } else if (nb_v == 1) {
        nb = std::sscanf(line.c_str(), "f %lld/%lld %lld/%lld %lld/%lld %lld/%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6, &vIndex7, &vIndex8);
        if (nb == 8) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            vertex.push_back(vIndex7);
            vertex.push_back(vIndex8);
            return (vertex);
        }
        nb = std::sscanf(line.c_str(), "f %lld//%lld %lld//%lld %lld//%lld %lld//%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6, &vIndex7, &vIndex8);
        if (nb == 8) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            vertex.push_back(vIndex7);
            vertex.push_back(vIndex8);
            return (vertex);
        }
        nb = std::sscanf(line.c_str(), "f %lld/%lld %lld/%lld %lld/%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6);
        if (nb == 6) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            return (vertex);
        }
        nb = std::sscanf(line.c_str(), "f %lld//%lld %lld//%lld %lld//%lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4, &vIndex5, &vIndex6);
        if (nb == 6) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            vertex.push_back(vIndex5);
            vertex.push_back(vIndex6);
            return (vertex);
        }
    } else {
        nb = std::sscanf(line.c_str(), "f %lld %lld %lld %lld", 
                    &vIndex1, &vIndex2, &vIndex3, &vIndex4);
        if (nb == 4) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            vertex.push_back(vIndex4);
            return (vertex);
        }
        nb = std::sscanf(line.c_str(), "f %lld %lld %lld", 
                    &vIndex1, &vIndex2, &vIndex3);
        if (nb == 3) {
            vertex.push_back(vIndex1);
            vertex.push_back(vIndex2);
            vertex.push_back(vIndex3);
            return (vertex);
        }
    }
    return (vertex);
}

RT::ParserObj::ParserObj()
{
    has_normals = false;
    has_textures = false;
}

void RT::ParserObj::create(std::string filepath)
{
    std::ifstream file(filepath);
    std::string line;

    //Variables for parsing
    std::vector<std::vector<long long>> faces;
    std::map<long long, std::string> smooths;
    std::map<long long, std::string> materials;
    std::vector<bool> textures_bool;
    std::vector<bool> normals_bool;
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        if (line[0] == 'v' && line[1] == ' ') {
            double x = 0, y = 0, z = 0;
            std::vector<double> tmp;
            std::sscanf(line.c_str(), "v %lf %lf %lf", &x, &y, &z);
            tmp.push_back(x);
            tmp.push_back(y);
            tmp.push_back(z);
            stock_vertices.push_back(tmp);

        } else if (line[0] == 'v' && line[1] == 'n') {
            double x = 0, y = 0, z = 0;
            std::vector<double> tmp;
            std::sscanf(line.c_str(), "vn %lf %lf %lf", &x, &y, &z);
            tmp.push_back(x);
            tmp.push_back(y);
            tmp.push_back(z);
            stock_vertices_normals.push_back(tmp);
            has_normals = 1;
        
        } else if (line[0] == 'v' && line[1] == 't') {
            double u = 0, v = 0;
            std::vector<double> tmp;
            std::sscanf(line.c_str(), "vt %lf %lf", &u, &v);
            tmp.push_back(u);
            tmp.push_back(v);
            stock_vertices_textures.push_back(tmp);
            has_textures = 1;

        } else if (line[0] == 'f')
            faces.push_back(getVertex(line, has_normals + has_textures));

        else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
            std::string tmp;
            std::sscanf(line.c_str(), "usemtl %s", tmp.data());

            //handle error
            tmp = "light";
            if (faces.size() > 0)
                materials.insert(std::make_pair(faces.back()[0], tmp.c_str()));
            else
                materials.insert(std::make_pair(0, tmp.c_str()));

        } else if (line[0] == 's') {
            std::string tmp;
            std::sscanf(line.c_str(), "s %s", tmp.data());

            //handle error
            if (tmp == "1")
                tmp = "on";
            if (faces.size() > 0)
                smooths.insert(std::make_pair(faces.back()[0], tmp.c_str()));
            else
                smooths.insert(std::make_pair(0, tmp.c_str()));

        } else if (line[0] == 'o') {
            stock_faces.push_back(faces);
            stock_smooths.push_back(smooths);
            stock_materials.push_back(materials);
            textures_bool.push_back(has_textures);
            normals_bool.push_back(has_normals);
            faces.clear();
            smooths.clear();
            materials.clear();
        }
    }
    //Adding the last object
    stock_faces.push_back(faces);
    stock_smooths.push_back(smooths);
    stock_materials.push_back(materials);
    textures_bool.push_back(has_textures);
    normals_bool.push_back(has_normals);

    file.close();

    //Assigning values to the index
    for (size_t i = 0; i < textures_bool.size() && i < normals_bool.size(); i++) {
        if (textures_bool[i] == 1 && normals_bool[i] == 1)
            index.push_back(3);
        else if (textures_bool[i] == 1 || normals_bool[i] == 1)
            index.push_back(2);
        else
            index.push_back(1);
    }
}

RT::ParserObj::~ParserObj()
{
}

std::vector<std::vector<std::vector<double>>> RT::ParserObj::getVerticesOfFaces(size_t pos) const
{
    std::vector<std::vector<std::vector<double>>> vertices_of_faces;
    std::vector<std::vector<double>> vertices;

    for (size_t nb_face = 0; nb_face < stock_faces[pos].size(); nb_face++) {

        for (size_t nb_point = 0; nb_point < stock_faces[pos][nb_face].size(); nb_point += index[pos]) {
            if (((size_t)stock_faces[pos][nb_face][nb_point] - 1) < stock_vertices.size()) {
                vertices.push_back(stock_vertices[stock_faces[pos][nb_face][nb_point] - 1]);
            }
        }
        vertices_of_faces.push_back(vertices);
        vertices.clear();
    }
    return (vertices_of_faces);
}

std::vector<std::vector<std::vector<double>>> RT::ParserObj::getVerticesNormalsOfFaces(size_t pos) const
{
    if (has_normals == 1)
        return (std::vector<std::vector<std::vector<double>>>());
    std::vector<std::vector<std::vector<double>>> vertices_normals_of_faces;
    std::vector<std::vector<double>> vertices_normals;

    for (size_t nb_face = 0; nb_face < stock_faces[pos].size(); nb_face++) {

        for (size_t nb_point = 0; nb_point < stock_faces[pos][nb_face].size(); nb_point += index[pos]) {
            if (((size_t)stock_faces[pos][nb_face][nb_point] - 1) < stock_vertices_normals.size()) {
                vertices_normals.push_back(stock_vertices_normals[stock_faces[pos][nb_face][nb_point] - 1]);
            }
        }
        vertices_normals_of_faces.push_back(vertices_normals);
        vertices_normals.clear();
    }
    return (vertices_normals_of_faces);
}

std::vector<std::vector<std::vector<double>>> RT::ParserObj::getVerticesTexturesOfFaces(size_t pos) const
{
    if (has_textures == 1)
        return (std::vector<std::vector<std::vector<double>>>());
    std::vector<std::vector<std::vector<double>>> vertices_textures_of_faces;
    std::vector<std::vector<double>> vertices_textures;

    for (size_t nb_face = 0; nb_face < stock_faces[pos].size(); nb_face++) {

        for (size_t nb_point = 0; nb_point < stock_faces[pos][nb_face].size(); nb_point += index[pos]) {
            if (((size_t)stock_faces[pos][nb_face][nb_point] - 1) < stock_vertices_textures.size()) {
                vertices_textures.push_back(stock_vertices_textures[stock_faces[pos][nb_face][nb_point] - 1]);
            }
        }
        vertices_textures_of_faces.push_back(vertices_textures);
        vertices_textures.clear();
    }
    return (vertices_textures_of_faces);
}

std::vector<std::map<long long, std::string>> RT::ParserObj::getSmooths() const
{
    return (stock_smooths);
}

std::vector<std::map<long long, std::string>> RT::ParserObj::getMaterials() const
{
    return (stock_materials);
}

size_t RT::ParserObj::getNbFaces() const
{
    return (this->stock_faces.size());
};
