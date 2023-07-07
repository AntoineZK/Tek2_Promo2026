/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Packet
*/

#include "INetwork.hpp"

Packet::Packet()
{
}

Packet::~Packet()
{
}

void Packet::addToBody(std::string &body)
{
    int x = 0;
    for (; _body[x] != '\0'; x++);
    for (int i = 0; body[i] != '\0'; i++, x++) {
        _body[x] = body[i];
    }
    _body[x] = '\0';
}

std::string Packet::getBody() const
{
    return _body;
}

//! TODO: Add a function to serialize the sphere/cube/.. class

std::vector<std::string> Packet::deserialize()
{
    // printf("Packet::deserialize()\n");
    std::vector<std::string> result;
    std::string tmp;
    std::stringstream ss(_body);
    // printf("separator = %c\n", _separator);
    while (std::getline(ss, tmp, _separator)) {
        // printf("tmp = %s\n", tmp.c_str());
        result.push_back(tmp);
    }
    // printf("result.size() = %d\n", (int) result.size());
    // _size = 0;
    // std::memset(_body, 0, sizeof(_body));
    // printf("Packet::deserialize() end\n");
    return result;
}

void Packet::clearBody()
{
    _body[0] = '\0';
}

int Packet::getSize() const
{
    return _size;
}

void Packet::addLetterToBody(char c, int index)
{
    if (index <= 0 && index > (int) sizeof(_body))
        throw std::runtime_error("Index out of range");
    _body[index] = c;
}