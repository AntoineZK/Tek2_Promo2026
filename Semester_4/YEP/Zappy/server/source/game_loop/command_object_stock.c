/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_object_stock
*/

#include "zappy.h"

void set_phiras(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "phiras") == 0) {
        if (client->player->inventory->phiras > 0) {
            zap->map[client->player->y][client->player->x]->item->phiras++;
            client->player->inventory->phiras--;
            ressource_dropping(zap, client, 5);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_thystame(zap, client, cmd);
}

void set_thystame(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "thystame") == 0) {
        if (client->player->inventory->thystame > 0) {
            zap->map[client->player->y][client->player->x]->item->thystame++;
            client->player->inventory->thystame--;
            ressource_dropping(zap, client, 6);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    update_wbuffer(client, "ko\n");
}

void take_phiras(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "phiras") == 0) {
        if (zap->map[client->player->y][client->player->x]->item->phiras > 0) {
            zap->map[client->player->y][client->player->x]->item->phiras--;
            client->player->inventory->phiras++;
            update_ressource(zap->ressources->phiras, client->player->x,
            client->player->y);
            ressource_collecting(zap, client, 5);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_thystame(zap, client, cmd);
}

void take_thystame(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "thystame") == 0) {
        if (z->map[client->player->y][client->player->x]->item->thystame > 0) {
            z->map[client->player->y][client->player->x]->item->thystame--;
            client->player->inventory->thystame++;
            update_ressource(z->ressources->thystame, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 6);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    update_wbuffer(client, "ko\n");
}
