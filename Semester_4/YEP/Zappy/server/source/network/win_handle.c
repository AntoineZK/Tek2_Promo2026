/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy [WSL : Ubuntu]
** File description:
** handle_win
*/

#include "zappy.h"

static void handle_win_two(zappy_t *zap, char *winningTeam)
{
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next) {
        if (tmp->player != NULL && strcmp(tmp->teamName, winningTeam) == 0)
            update_wbuffer(tmp, "victory\n");
        if (tmp->player != NULL && strcmp(tmp->teamName, winningTeam) != 0)
            update_wbuffer(tmp, "defeat\n");
        if (tmp->isGraphical == false && tmp->teamName == NULL) {
            tmp->terminated = true;
            zap->ntw->nbRemove++;
        }
    }
}

bool handle_win(zappy_t *zap)
{
    char *winningTeam = NULL;
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next) {
        if (tmp->player != NULL && tmp->player->level == 8) {
            winningTeam = tmp->teamName;
            break;
        }
    }
    if (winningTeam == NULL)
        return false;
    handle_win_two(zap, winningTeam);
    end_game(zap, winningTeam);
    return true;
}
