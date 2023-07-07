/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** Utils
*/

#pragma once
    #include "../../Include/Include.hpp"

namespace RT {
    class Utils {
        public:
            Utils();
            ~Utils();
            std::vector<std::string> split(const std::string &str, char delim);
            int findInList(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &list, std::pair<int, int> &pos);

        protected:
        private:
    };
}