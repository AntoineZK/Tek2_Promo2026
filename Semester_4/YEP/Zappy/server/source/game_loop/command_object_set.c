/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_object_set
*/

#include "zappy.h"

void set_food(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "food") == 0) {
        if (client->player->inventory->food > 0) {
            zap->map[client->player->y][client->player->x]->item->food++;
            client->player->inventory->food--;
            ressource_dropping(zap, client, 0);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_linemate(zap, client, cmd);
}

void set_linemate(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "linemate") == 0) {
        if (client->player->inventory->linemate > 0) {
            zap->map[client->player->y][client->player->x]->item->linemate++;
            client->player->inventory->linemate--;
            ressource_dropping(zap, client, 1);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_deraumere(zap, client, cmd);
}

void set_deraumere(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "deraumere") == 0) {
        if (client->player->inventory->deraumere > 0) {
            zap->map[client->player->y][client->player->x]->item->deraumere++;
            client->player->inventory->deraumere--;
            ressource_dropping(zap, client, 2);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_sibur(zap, client, cmd);
}

void set_sibur(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "sibur") == 0) {
        if (client->player->inventory->sibur > 0) {
            zap->map[client->player->y][client->player->x]->item->sibur++;
            client->player->inventory->sibur--;
            ressource_dropping(zap, client, 3);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_mendiane(zap, client, cmd);
}

void set_mendiane(zappy_t *zap, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "mendiane") == 0) {
        if (client->player->inventory->mendiane > 0) {
            zap->map[client->player->y][client->player->x]->item->mendiane++;
            client->player->inventory->mendiane--;
            ressource_dropping(zap, client, 4);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    set_phiras(zap, client, cmd);
}
