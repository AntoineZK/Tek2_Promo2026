/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** command_move
*/

#include "zappy.h"

void turn_player_left(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    (void)zap;
    client->player->direction--;
    if (client->player->direction == -1)
        client->player->direction = 3;
    update_wbuffer(client, "ok\n");
    char *str = send_player_position2(client);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
    free(str);
}

void turn_player_right(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    (void)zap;
    client->player->direction++;
    if (client->player->direction == 4)
        client->player->direction = 0;
    update_wbuffer(client, "ok\n");
    char *str = send_player_position2(client);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
    free(str);
}

void move_to_tile(tile_t *start, tile_t *arrive, client_t *client)
{
    client_t *tmp = start->player;
    client_t *tmp2 = arrive->player;
    if (tmp == client)
        start->player = client->next_on_tile;
    for (; tmp != NULL; tmp = tmp->next_on_tile) {
        if (tmp->next_on_tile == client)
            tmp->next_on_tile = client->next_on_tile;
    }
    client->next_on_tile = NULL;
    if (tmp2 == NULL) {
        arrive->player = client;
        return;
    }
    for (; tmp2->next_on_tile != NULL; tmp2 = tmp2->next_on_tile);
    tmp2->next_on_tile = client;
}

void move_player_forward(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int x = client->player->x;
    int y = client->player->y;
    if (client->player->direction == 0)
        move_right(zap, client);
    if (client->player->direction == 1)
        move_down(zap, client);
    if (client->player->direction == 2)
        move_left(zap, client);
    if (client->player->direction == 3)
        move_up(zap, client);
    move_to_tile(zap->map[y][x],
    zap->map[client->player->y][client->player->x], client);
    update_wbuffer(client, "ok\n");
    char *str = send_player_position2(client);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
    free(str);
}
