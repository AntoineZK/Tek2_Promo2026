/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** incantation_graphic
*/

#include "zappy.h"

void start_incantation_player(zappy_t *zap, client_t *client)
{
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true) {
            int maxSize = snprintf(NULL, 0, " %d", client->id);
            char *str = alloca(sizeof(char) * (maxSize + 1));
            snprintf(str, maxSize + 1, " %d", client->id);
            update_wbuffer(allCli, str);
        }
    }
}

void end_incantation(zappy_t *zap, client_t *client, char *cmd)
{
    int maxSize = snprintf(NULL, 0, "pie %d %d %s\n",
    client->player->x, client->player->y, cmd);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pie %d %d %s\n",
    client->player->x, client->player->y, cmd);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
