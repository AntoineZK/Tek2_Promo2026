/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** refill_ressouce
*/


#include "zappy.h"

void fill_map(tile_t ***map, zone_object_t *obj, int mat)
{
    int x = obj->item_x;
    int y = obj->item_y;
    if (mat == 0)
        map[y][x]->item->food += 1;
    if (mat == 1)
        map[y][x]->item->linemate += 1;
    if (mat == 2)
        map[y][x]->item->deraumere += 1;
    if (mat == 3)
        map[y][x]->item->sibur += 1;
    if (mat == 4)
        map[y][x]->item->mendiane += 1;
    if (mat == 5)
        map[y][x]->item->phiras += 1;
    if (mat == 6)
        map[y][x]->item->thystame += 1;
}

static void refill(tile_t ***map, zone_object_t **item, int width, int mat)
{
    for (int i = 0; item[i] != NULL; i++) {
        if (item[i]->on == false) {
            fill_random_ressource(item[i], width);
            fill_map(map, item[i], mat);
        }
    }
}

void refile_map_ressources(tile_t ***map, ressource_t *r)
{
    if (r->food->is_changed == true)
        refill(map, r->food->item, r->width, 0);
    if (r->linemate->is_changed == true)
        refill(map, r->linemate->item, r->width, 1);
    if (r->deraumere->is_changed == true)
        refill(map, r->deraumere->item, r->width, 2);
    if (r->sibur->is_changed == true)
        refill(map, r->sibur->item, r->width, 3);
    if (r->mendiane->is_changed == true)
        refill(map, r->mendiane->item, r->width, 4);
    if (r->phiras->is_changed == true)
        refill(map, r->phiras->item, r->width, 5);
    if (r->thystame->is_changed == true)
        refill(map, r->thystame->item, r->width, 6);
}

void up_x(int *x, int *y, int width)
{
    *x += 1;
    if (*x == width) {
        *x = 0;
        *y += 1;
    }
}
