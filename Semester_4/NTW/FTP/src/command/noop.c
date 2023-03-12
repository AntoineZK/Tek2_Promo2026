/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** noop
*/

#include "ftp.h"

ftp_t *noop(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    dprintf(ftp->tmp->client_fd, M_200);
    return (ftp);
}
