/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Utils
*/

#include "Utils.hpp"

RT::Utils::Utils()
{
}

RT::Utils::~Utils()
{
}

std::vector<std::string> RT::Utils::split(const std::string &str, char delim)
{
    std::vector<std::string> result;
    std::string tmp;
    std::stringstream ss(str);
    while (std::getline(ss, tmp, delim)) {
        result.push_back(tmp);
    }
    return result;
}

int RT::Utils::findInList(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &list, std::pair<int, int> &pos)
{
    int index = 0;
    for (auto &it : list) {
        if ((it.first.first <= pos.first && it.first.second >= pos.first) && (it.second.first <= pos.second && it.second.second >= pos.second)) {
            return index;
        }
        index++;
    }
    return -1;
}
