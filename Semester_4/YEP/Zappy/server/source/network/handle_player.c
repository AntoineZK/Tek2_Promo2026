/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** handle_player
*/

#include "zappy.h"

static void check_if_team(zappy_t *zap, client_t *tmp)
{
    if (tmp->teamName == NULL && tmp->cmd != NULL) {
        if (team_has_place(zap, tmp) == true) {
            tmp->isGraphical == true ? resp_to_graphic(zap, tmp) :
            resp_to_ia(zap, tmp);
        } else {
            tmp->terminated = true;
            zap->ntw->nbRemove++;
            printf("No place in team or team doesn't exist\n");
        }
    } else if (tmp->teamName != NULL && tmp->cmd != NULL) {
        tmp->isGraphical == true ? execute_graphic(zap, tmp) :
        execute_ia(zap, tmp);
    }
}

void handle_player(zappy_t *zap)
{
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next)
        check_if_team(zap, tmp);
}
