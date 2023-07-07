/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** ressource
*/

#include "zappy.h"

void fill_random_ressource(zone_object_t *obj, int width)
{
    int nb = rand() % obj->place;
    int x = obj->x1;
    int y = obj->y1;
    for (int i = 0; i < nb; i++) {
        x++;
        if (x == width) {
            x = 0;
            y++;
        }
    }
    obj->item_x = x;
    obj->item_y = y;
    obj->on = true;
}

static res_type_t *fill_type(int nb)
{
    res_type_t *type = malloc(sizeof(res_type_t));
    type->item = malloc(sizeof(zone_object_t *) * (nb + 1));
    type->item[nb] = NULL;
    type->is_changed = false;
    return (type);
}

float get_nb_ressource(int width, int height, float ratio)
{
    float nb = width * height * ratio;
    if (nb < 1)
        nb = 1;
    return (nb);
}

res_type_t *init_type(int width, int height, float ratio)
{
    float nb = get_nb_ressource(width, height, ratio);
    res_type_t *type = fill_type((int)nb);
    int size = width * height / (int)nb;
    int x = 0;
    int y = 0;
    int g = 0;
    for (int i = (int)nb; i != 0; i--, g++) {
        type->item[g] = malloc(sizeof(zone_object_t));
        type->item[g]->on = false;
        type->item[g]->x1 = x;
        type->item[g]->y1 = y;
        for (int j = 1; j < size; j++)
            up_x(&x, &y, width);
        type->item[g]->x2 = x;
        type->item[g]->y2 = y;
        type->item[g]->place = size;
        fill_random_ressource(type->item[g], width);
        up_x(&x, &y, width);
    }
    return (type);
}

ressource_t *init_ressource(int width, int height)
{
    ressource_t *ressource = malloc(sizeof(ressource_t));
    ressource->food = init_type(width, height, 0.5);
    ressource->linemate = init_type(width, height, 0.3);
    ressource->deraumere = init_type(width, height, 0.15);
    ressource->sibur = init_type(width, height, 0.1);
    ressource->mendiane = init_type(width, height, 0.1);
    ressource->phiras = init_type(width, height, 0.08);
    ressource->thystame = init_type(width, height, 0.05);
    ressource->width = width;
    return (ressource);
}
