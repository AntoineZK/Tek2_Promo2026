/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** egg_graphic
*/

#include "zappy.h"

void egg_laying(zappy_t *zap, client_t *client)
{
    int maxSize = snprintf(NULL, 0, "pfk %d\n", client->id);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pfk %d\n", client->id);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

void egg_laid(zappy_t *zap, client_t *client)
{
    eggs_t *tmp = zap->eggs;
    for (; tmp; tmp = tmp->next) {
        if (client->player->x == tmp->x && client->player->y == tmp->y)
            break;
    }
    int maxSize = snprintf(NULL, 0, "enw %d %d %d %d\n",
    tmp->id, client->id, tmp->x, tmp->y);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "enw %d %d %d %d\n",
    tmp->id, client->id, tmp->x, tmp->y);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

void egg_hatching(zappy_t *zap, client_t *client)
{
    eggs_t *tmp = zap->eggs;
    for (; tmp; tmp = tmp->next) {
        if (client->player->x == tmp->x && client->player->y == tmp->y)
            break;
    }
    int maxSize = snprintf(NULL, 0, "ebo %d\n", tmp->id);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "ebo %d\n", tmp->id);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

void egg_death(zappy_t *zap, client_t *client)
{
    eggs_t *tmp = zap->eggs;
    for (; tmp; tmp = tmp->next) {
        if (client->player->x == tmp->x && client->player->y == tmp->y)
            break;
    }
    int maxSize = snprintf(NULL, 0, "edi %d\n", tmp->id);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "edi %d\n", tmp->id);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
