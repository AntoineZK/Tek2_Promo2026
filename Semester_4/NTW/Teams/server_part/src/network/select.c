/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** select
*/

#include "server.h"

void setup_select(teams_t *teams)
{
    FD_ZERO(&teams->ntw->readfds);
    FD_ZERO(&teams->ntw->writefds);
    FD_SET(teams->ntw->fd, &teams->ntw->readfds);
    for (sockcli_t *tmp = teams->ntw->cliCon; tmp != NULL; tmp = tmp->next) {
        FD_SET(tmp->fd, &teams->ntw->readfds);
        if (tmp->writeBufferLen > 0)
            FD_SET(tmp->fd, &teams->ntw->writefds);
    }
}

void accept_new_client(teams_t *teams)
{
    int new_client = accept(teams->ntw->fd,
    (struct sockaddr *)&teams->ntw->addr, (socklen_t *)&teams->ntw->addrlen);

    new_client == -1 ? exit(EXIT_FAILURE) : 0;
    teams->ntw->cliCon = add_socket_client(teams->ntw->cliCon, new_client);
}
