/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** ressource
*/

#pragma once

typedef struct zone_object_s {
    bool on;
    int x1;
    int x2;
    int y1;
    int y2;
    int item_x;
    int item_y;
    int place;
} zone_object_t;

typedef struct res_type_s {
    zone_object_t **item;
    bool is_changed;
} res_type_t;

typedef struct ressource_s {
    res_type_t *food;
    res_type_t *linemate;
    res_type_t *deraumere;
    res_type_t *sibur;
    res_type_t *mendiane;
    res_type_t *phiras;
    res_type_t *thystame;
    int width;
} ressource_t;

ressource_t *init_ressource(int width, int height);
