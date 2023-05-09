/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Ghost
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>


namespace arcade {
    class Ghost {
        public:
            Ghost();
            ~Ghost();
            int direction;
            int64_t move_time;
            int64_t stase;
            int64_t time_stock;
            int x;
            int y;
            int stuck;
            char memory;
        private:
    };
}