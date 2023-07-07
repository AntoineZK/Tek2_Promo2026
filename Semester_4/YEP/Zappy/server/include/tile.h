/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** tile
*/

#pragma once
#include "inventory.h"

typedef struct client_s client_t;

typedef struct tile_s {
    int x;
    int y;
    invent_t *item;
    client_t *player;
} tile_t;
