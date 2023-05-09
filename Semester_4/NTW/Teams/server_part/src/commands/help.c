/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** help
*/

#include "server.h"

void help(teams_t *server, sockcli_t *actCli, char **args)
{
    (void)server;
    (void)args;
    update_wbuffer(actCli, "HELP\n");
}
