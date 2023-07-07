/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_object_take
*/

#include "zappy.h"

void take_food(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "food") == 0) {
        if (z->map[client->player->y][client->player->x]->item->food > 0) {
            z->map[client->player->y][client->player->x]->item->food--;
            client->player->inventory->food++;
            update_ressource(z->ressources->food, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 0);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_linemate(z, client, cmd);
}

void take_linemate(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "linemate") == 0) {
        if (z->map[client->player->y][client->player->x]->item->linemate > 0) {
            z->map[client->player->y][client->player->x]->item->linemate--;
            client->player->inventory->linemate++;
            update_ressource(z->ressources->linemate, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 1);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_deraumere(z, client, cmd);
}

void take_deraumere(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "deraumere") == 0) {
        if (z->map[client->player->y][client->player->x]->item->deraumere > 0) {
            z->map[client->player->y][client->player->x]->item->deraumere--;
            client->player->inventory->deraumere++;
            update_ressource(z->ressources->deraumere, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 2);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_sibur(z, client, cmd);
}

void take_sibur(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "sibur") == 0) {
        if (z->map[client->player->y][client->player->x]->item->sibur > 0) {
            z->map[client->player->y][client->player->x]->item->sibur--;
            client->player->inventory->sibur++;
            update_ressource(z->ressources->sibur, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 3);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_mendiane(z, client, cmd);
}

void take_mendiane(zappy_t *z, client_t *client, char **cmd)
{
    if (strcasecmp(cmd[1], "mendiane") == 0) {
        if (z->map[client->player->y][client->player->x]->item->mendiane > 0) {
            z->map[client->player->y][client->player->x]->item->mendiane--;
            client->player->inventory->mendiane++;
            update_ressource(z->ressources->mendiane, client->player->x,
            client->player->y);
            ressource_collecting(z, client, 4);
            update_wbuffer(client, "ok\n");
        } else
            update_wbuffer(client, "ko\n");
        return;
    }
    take_phiras(z, client, cmd);
}
