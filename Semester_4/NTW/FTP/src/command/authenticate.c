/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** authenticate
*/

#include "ftp.h"

int error_pass(ftp_t *ftp)
{
    if (ftp->tmp->username == NULL) {
        dprintf(ftp->tmp->client_fd, M_503);
        return 1;
    }
    if (ftp->tmp->logged == true) {
        dprintf(ftp->tmp->client_fd, M_230);
        return 1;
    }
    return 0;
}

ftp_t *user(ftp_t *ftp, int j)
{
    dprintf(ftp->tmp->client_fd, M_331);
    ftp->tmp->username = strdup(ftp->commands[1]);
    return ftp;
}

ftp_t *pass(ftp_t *ftp, int j)
{
    if (error_pass(ftp) == 1)
        return ftp;
    if (j == 0 && strcmp(ftp->tmp->username, "Anonymous") == 0) {
        ftp->tmp->logged = true;
        dprintf(ftp->tmp->client_fd, M_230);
    } else if (j == 1 && strcmp(ftp->tmp->username, "AZK") == 0 &&
    strcmp(ftp->commands[1], "toor") == 0) {
        ftp->tmp->logged = true;
        dprintf(ftp->tmp->client_fd, M_230);
    } else {
        dprintf(ftp->tmp->client_fd, M_530);
        ftp->tmp->logged = false;
    }
    free(ftp->tmp->username);
    return ftp;
}
