/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** free_map
*/

#include "zappy.h"

void free_item(zone_object_t **item)
{
    for (int i = 0; item[i] != NULL; i++)
        free(item[i]);
    free(item);
}

void free_ressources(ressource_t *r)
{
    free_item(r->food->item);
    free_item(r->linemate->item);
    free_item(r->deraumere->item);
    free_item(r->sibur->item);
    free_item(r->mendiane->item);
    free_item(r->phiras->item);
    free_item(r->thystame->item);
    free(r->food);
    free(r->linemate);
    free(r->deraumere);
    free(r->sibur);
    free(r->mendiane);
    free(r->phiras);
    free(r->thystame);
    free(r);
}

void free_map(tile_t ***map)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != NULL; j++) {
            free(map[i][j]->item);
            free(map[i][j]);
        }
        free(map[i]);
    }
    free(map);
}
