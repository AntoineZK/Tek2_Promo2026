/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** map
*/

#include "zappy.h"

tile_t *init_tile(int x, int y)
{
    tile_t *tile = malloc(sizeof(tile_t));
    tile->x = x;
    tile->y = y;
    tile->item = init_invent();
    tile->player = NULL;
    return (tile);
}

tile_t ***init_map(int width, int height)
{
    tile_t ***map = malloc(sizeof(tile_t **) * (height + 1));
    map[height] = NULL;
    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(tile_t *) * (width + 1));
        map[i][width] = NULL;
        for (int j = 0; j < width; j++) {
            map[i][j] = init_tile(j, i);
        }
    }
    return (map);
}

void file_map_ressources(tile_t ***map, ressource_t *r)
{
    for (int i = 0; r->food->item[i] != NULL; i++)
        fill_map(map, r->food->item[i], 0);
    for (int i = 0; r->linemate->item[i] != NULL; i++)
        fill_map(map, r->linemate->item[i], 1);
    for (int i = 0; r->deraumere->item[i] != NULL; i++)
        fill_map(map, r->deraumere->item[i], 2);
    for (int i = 0; r->sibur->item[i] != NULL; i++)
        fill_map(map, r->sibur->item[i], 3);
    for (int i = 0; r->mendiane->item[i] != NULL; i++)
        fill_map(map, r->mendiane->item[i], 4);
    for (int i = 0; r->phiras->item[i] != NULL; i++)
        fill_map(map, r->phiras->item[i], 5);
    for (int i = 0; r->thystame->item[i] != NULL; i++)
        fill_map(map, r->thystame->item[i], 6);
}
