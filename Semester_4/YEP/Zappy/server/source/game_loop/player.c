/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** player
*/

#include "zappy.h"

player_t *init_player(int x, int y, int direction)
{
    player_t *player = malloc(sizeof(player_t));
    player->x = x;
    player->y = y;
    player->level = 1;
    player->nbCycle = 0;
    player->canAct = true;
    player->inventory = init_invent();
    player->inventory->food = 10;
    player->direction = direction;
    player->time_food = 126;
    player->isEvolve = false;
    return (player);
}

void place_player(tile_t ***map, client_t *client)
{
    tile_t *tile = map[client->player->y][client->player->x];
    client_t *tmp = tile->player;
    if (tmp == NULL) {
        tile->player = client;
        return;
    }
    while (tmp->next_on_tile != NULL)
        tmp = tmp->next_on_tile;
    tmp->next_on_tile = client;
}

void free_player(player_t *player)
{
    free(player->inventory);
    free(player);
}
