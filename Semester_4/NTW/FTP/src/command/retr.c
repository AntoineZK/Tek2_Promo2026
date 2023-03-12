/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** retr
*/

#include "ftp.h"

int retr_error(ftp_t *ftp)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (1);
    }
    if (ftp->tmp->pasv == false && ftp->tmp->active == false) {
        dprintf(ftp->tmp->client_fd, M_425);
        return (1);
    }
    if (open(ftp->commands[1], O_RDONLY) == -1) {
        dprintf(ftp->tmp->client_fd, M_550);
        return (1);
    }
    return (0);
}

void exec_retr(ftp_t *ftp, char *file)
{
    int new_client = 0;
    char *path = strdup(ftp->tmp->directory);

    if (ftp->tmp->active == true)
        new_client = accept(ftp->tmp->port_fd, (struct sockaddr *)
    &ftp->socket_addr, &ftp->socket_addr_len);
    else if (ftp->tmp->pasv == true)
        new_client = accept(ftp->tmp->pasv_fd, (struct sockaddr *)
    &ftp->socket_addr, &ftp->socket_addr_len);

    if (ftp->tmp->active == true)
        close(ftp->tmp->port_fd);
    else if (ftp->tmp->pasv == true)
        close(ftp->tmp->pasv_fd);
    my_strcat(&path, "/");
    my_strcat(&path, ftp->commands[1]);
    file = stat_file(path);
    free(path);
    dprintf(new_client, "%s", file);
    exit(84);
}

ftp_t *retr(ftp_t *ftp, int j)
{
    pid_t value;
    char *file = NULL;
    int fd = 0;

    if (retr_error(ftp) == 1)
        return (ftp);
    dprintf(ftp->tmp->client_fd, M_150);
    value = fork();
    value == -1 ? exit(84) : 0;
    if (value == 0)
        exec_retr(ftp, file);
    dprintf(ftp->tmp->client_fd, M_226);
    ftp->tmp->pasv == true ? close(ftp->tmp->pasv_fd) : 0;
    ftp->tmp->pasv = false;
    ftp->tmp->pasv_fd = -1;
    ftp->tmp->active == true ? close(ftp->tmp->port_fd) : 0;
    ftp->tmp->active = false;
    ftp->tmp->port_fd = -1;
    return (ftp);
}
