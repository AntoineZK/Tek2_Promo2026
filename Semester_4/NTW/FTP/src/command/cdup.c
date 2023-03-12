/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** cdup
*/

#include "ftp.h"

ftp_t *cdup(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false ||
    strcmp(ftp->tmp->directory, ftp->path) == 0) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    dprintf(ftp->tmp->client_fd, M_200);
    ftp->tmp->directory = remove_last_directory(ftp->tmp->directory);
    return (ftp);
}
