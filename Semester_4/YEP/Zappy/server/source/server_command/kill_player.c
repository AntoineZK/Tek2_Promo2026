/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy [WSL : Ubuntu]
** File description:
** kill_player
*/

#include "zappy.h"

bool kill_by_id(zappy_t *zap, char **cmd)
{
    int id = atoi(cmd[1]);

    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next) {
        if (tmp->id == id && tmp->player != NULL) {
            update_wbuffer(tmp, "dead\n");
            send_player_death(zap, tmp);
            break;
        }
    }
    zap->argv->isNcurses ? zap->ncurses->serverResponse =
    add_command(zap->ncurses->serverResponse, "A Player has been killed", 0) :
    0;
    return true;
}
