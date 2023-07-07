/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** test_deserialiser
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <type_traits>
#include <algorithm>


int main(void)
{
    std::string data = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15";

    std::vector<int> tmp;
    std::stringstream ss(data);
    std::string tmpStr;

    while(std::getline(ss, tmpStr, ',')) {
        tmp.push_back(std::stoi(tmpStr));
    }

    for (int i = 0; i < (int) tmp.size(); i++) {
        std::cout << tmp[i] << std::endl;
    }

    return 0;
}