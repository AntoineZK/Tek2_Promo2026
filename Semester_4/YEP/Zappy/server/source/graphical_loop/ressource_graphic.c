/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** ressource_graphic
*/

#include "zappy.h"

void ressource_dropping(zappy_t *zap, client_t *sender, int ressrc)
{
    int maxSize = snprintf(NULL, 0, "pdr %d %d\n", sender->id, ressrc);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pdr %d %d\n", sender->id, ressrc);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

void ressource_collecting(zappy_t *zap, client_t *sender, int ressrc)
{
    int maxSize = snprintf(NULL, 0, "pgt %d %d\n", sender->id, ressrc);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pgt %d %d\n", sender->id, ressrc);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
