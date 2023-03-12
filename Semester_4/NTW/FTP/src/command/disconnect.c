/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** disconnect
*/

#include "ftp.h"

ftp_t *disconnect(ftp_t *ftp, int i)
{
    printf("Client %d disconnected.\n", ftp->tmp->client_fd);
    dprintf(ftp->tmp->client_fd, M_221);
    shutdown(ftp->tmp->client_fd, SHUT_RDWR);
    ftp->num_remove++;
    ftp->clients = update_lklist(ftp->clients, i);
    return ftp;
}
