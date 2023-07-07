/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** zappy_criterion
*/

#pragma once
// Criterion includes
#include <criterion/criterion.h>

// Project includes
#include "../../../server/include/zappy.h"

client_t *decal_wbuffer(client_t *cli);
tile_t ***generate_test_map(tile_t ***map, int x, int y);
client_t *create_client_test(client_t *cli, int id, int x, int y);
