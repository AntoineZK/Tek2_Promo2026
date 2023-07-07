/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** select
*/

#include "zappy.h"

void setup_select(zappy_t *zappy)
{
    FD_ZERO(&zappy->ntw->rfds);
    FD_ZERO(&zappy->ntw->wfds);
    FD_SET(zappy->ntw->sock, &zappy->ntw->rfds);
    FD_SET(STDIN_FILENO, &zappy->ntw->rfds);
    for (client_t *tmp = zappy->ntw->clients; tmp != NULL; tmp = tmp->next) {
        FD_SET(tmp->cliFD, &zappy->ntw->rfds);
        if (tmp->wBuffLen > 0)
            FD_SET(tmp->cliFD, &zappy->ntw->wfds);
    }
}

void accept_client(zappy_t *zappy)
{
    if (FD_ISSET(zappy->ntw->sock, &zappy->ntw->rfds)) {
        int newCli = accept(zappy->ntw->maxFD,
        (struct sockaddr *)&zappy->ntw->addr,
        (socklen_t *)&zappy->ntw->addrlen);

        if (newCli <= 0)
            return;
        zappy->ntw->clients = add_client(zappy->ntw->clients, newCli);
        client_t *last = get_last_client(zappy->ntw->clients);
        update_wbuffer(last, "WELCOME\n");
        printf("New client: %d\n", newCli);
    }
}

int max_fd(zappy_t *zappy)
{
    int max = zappy->ntw->sock;

    for (client_t *tmp = zappy->ntw->clients; tmp != NULL; tmp = tmp->next) {
        if (tmp->cliFD > max)
            max = tmp->cliFD;
    }
    return (max + 1);
}
