/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** set_init
*/

#include "ftp.h"

void init_ftp(ftp_t *ftp, char **av)
{
    ftp->port = atoi(av[1]);
    ftp->path = strdup(av[2]);
    ftp->server_fd = create_socket(ftp->port);
    ftp->socket_addr_len = sizeof(ftp->socket_addr);
    ftp->clients = NULL;
    ftp->tmp = NULL;
    ftp->commands = NULL;
    ftp->helper = stat_file("helper.txt");
    set_fd(ftp);
}

void set_fd(ftp_t *ftp)
{
    FD_ZERO(&ftp->readfds);
    FD_SET(ftp->server_fd, &ftp->readfds);
    lk_list *tmp = ftp->clients;
    for (; tmp; tmp = tmp->next) {
        FD_SET(tmp->client_fd, &ftp->readfds);
        if (tmp->pasv_fd != -1)
            FD_SET(tmp->pasv_fd, &ftp->readfds);
    }
}
