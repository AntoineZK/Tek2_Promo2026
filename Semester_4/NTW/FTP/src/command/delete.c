/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** delete
*/

#include "ftp.h"

ftp_t *dele(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    struct stat sb;
    int returnvalue = stat(ftp->commands[1], &sb);
    char *path = strdup(ftp->tmp->directory);
    my_strcat(&path, "/");
    my_strcat(&path, ftp->commands[1]);
    if (returnvalue == 0) {
        if (remove(path) == 0) {
            dprintf(ftp->clients->client_fd, M_250);
            return (ftp);
        }
    } else {
        dprintf(ftp->clients->client_fd, M_550);
        return (ftp);
    }
    return (ftp);
}
