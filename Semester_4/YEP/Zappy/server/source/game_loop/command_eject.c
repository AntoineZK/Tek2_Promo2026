/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_eject
*/

#include "zappy.h"

static void eject(zappy_t *zap, client_t *client, client_t *pusher)
{
    int x = client->player->x;
    int y = client->player->y;
    if (pusher->player->direction == 0)
        move_right(zap, client);
    if (pusher->player->direction == 1)
        move_down(zap, client);
    if (pusher->player->direction == 2)
        move_left(zap, client);
    if (pusher->player->direction == 3)
        move_up(zap, client);
    move_to_tile(zap->map[y][x],
    zap->map[client->player->y][client->player->x], client);
}

void commande_eject(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    client_t *tmp = zap->map[client->player->y][client->player->x]->player;
    client_t *tmp2 = NULL;
    if (tmp->next_on_tile == NULL) {
        update_wbuffer(client, "ko\n");
        return;
    }
    for (; tmp != NULL;) {
        if (tmp == client) {
            tmp = tmp->next_on_tile;
            continue;
        }
        tmp2 = tmp->next_on_tile;
        eject(zap, tmp, client);
        tmp = tmp2;
    }
    send_player_expulsion(zap, client);
    update_wbuffer(client, "ok\n");
}
