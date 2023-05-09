/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** exit_server
*/

#include "server.h"

void stop_server(teams_t *teams, sockcli_t *tmp, char **args)
{
    (void)args;
    (void)tmp;
    teams->shouldStop = true;
}

void exit_server(teams_t *teams, sockcli_t *tmp, char **args)
{
    (void)args;
    teams->ntw->nbRemove++;
    tmp->terminated = true;
}
