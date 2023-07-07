/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_look
*/

#include "zappy.h"

void look_till(tile_t *tile, client_t *client)
{
    int nb = 0;
    client_t *tmp = tile->player;
    for (; tmp != NULL; tmp = tmp->next_on_tile) {
        if (nb != 0)
            update_wbuffer(client, " player");
        else
            update_wbuffer(client, "player");
        nb++;
    }
    look_till_inventory(tile->item, client, nb);
}

int advance(int x, int limit, int sens)
{
    if (sens < 0) {
        x--;
        if (x < 0)
            x = limit - 1;
    } else {
        x++;
        if (x >= limit)
            x = 0;
    }
    return (x);
}

void commande_look(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    update_wbuffer(client, "[");
    look_till(zap->map[client->player->y][client->player->x], client);
    if (client->player->direction == 0)
        look_right(zap, client);
    if (client->player->direction == 1)
        look_down(zap, client);
    if (client->player->direction == 2)
        look_left(zap, client);
    if (client->player->direction == 3)
        look_up(zap, client);
    update_wbuffer(client, "]\n");
}
