/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** end_graphic
*/

#include "zappy.h"

void end_game(zappy_t *zap, char *team)
{
    int maxSize = snprintf(NULL, 0, "seg %s\n", team);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "seg %s\n", team);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

void message_from_serv(zappy_t *zap,  char *cmd)
{
    int maxSize = snprintf(NULL, 0, "smg %s\n", cmd);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "smg %s\n", cmd);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
