/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** move_func
*/

#include "zappy.h"

void move_up(zappy_t *zap, client_t *client)
{
    client->player->y--;
    if (client->player->y == -1)
        client->player->y = zap->argv->height - 1;
}

void move_down(zappy_t *zap, client_t *client)
{
    client->player->y++;
    if (client->player->y == zap->argv->height)
        client->player->y = 0;
}

void move_left(zappy_t *zap, client_t *client)
{
    client->player->x--;
    if (client->player->x == -1)
        client->player->x = zap->argv->width - 1;
}

void move_right(zappy_t *zap, client_t *client)
{
    client->player->x++;
    if (client->player->x == zap->argv->width)
        client->player->x = 0;
}
