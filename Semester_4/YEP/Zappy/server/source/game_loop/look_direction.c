/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** look_direction
*/

#include "zappy.h"

void look_right(zappy_t *zap, client_t *client)
{
    int x = client->player->x;
    int y = client->player->y;
    int z = 0;
    for (int i = 1; i <= client->player->level; i++) {
        y = advance(y, zap->argv->height, -1);
        x = advance(x, zap->argv->width, 1);
        z = y;
        for (int j = 0; j < i * 2 + 1; j++) {
            update_wbuffer(client, ",");
            look_till(zap->map[z][x], client);
            z = advance(z, zap->argv->height, 1);
        }
    }
}

void look_down(zappy_t *zap, client_t *client)
{
    int x = client->player->x;
    int y = client->player->y;
    int z = 0;
    for (int i = 1; i <= client->player->level; i++) {
        y = advance(y, zap->argv->height, 1);
        x = advance(x, zap->argv->width, 1);
        z = x;
        for (int j = 0; j < i * 2 + 1; j++) {
            update_wbuffer(client, ",");
            look_till(zap->map[y][z], client);
            z = advance(z, zap->argv->width, -1);
        }
    }
}

void look_left(zappy_t *zap, client_t *client)
{
    int x = client->player->x;
    int y = client->player->y;
    int z = 0;
    for (int i = 1; i <= client->player->level; i++) {
        y = advance(y, zap->argv->height, 1);
        x = advance(x, zap->argv->width, -1);
        z = y;
        for (int j = 0; j < i * 2 + 1; j++) {
            update_wbuffer(client, ",");
            look_till(zap->map[z][x], client);
            z = advance(z, zap->argv->height, -1);
        }
    }
}

void look_up(zappy_t *zap, client_t *client)
{
    int x = client->player->x;
    int y = client->player->y;
    int z = 0;
    for (int i = 1; i <= client->player->level; i++) {
        y = advance(y, zap->argv->height, -1);
        x = advance(x, zap->argv->width, -1);
        z = x;
        for (int j = 0; j < i * 2 + 1; j++) {
            update_wbuffer(client, ",");
            look_till(zap->map[y][z], client);
            z = advance(z, zap->argv->width, 1);
        }
    }
}
