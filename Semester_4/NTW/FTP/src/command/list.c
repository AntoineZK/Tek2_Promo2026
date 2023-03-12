/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** list
*/

#include "ftp.h"

bool list_error(ftp_t *ftp)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (true);
    }
    if (ftp->tmp->pasv == false && ftp->tmp->active == false) {
        dprintf(ftp->tmp->client_fd, M_425);
        return (true);
    }
    return (false);
}

void exec_list(ftp_t *ftp, char *dir)
{
    int new_client = 0;
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
    dup2(new_client, 1);
    char *directory[] = {"ls", "-l", dir, NULL};
    execv("/usr/bin/ls", directory);
    exit(84);
}

ftp_t *list(ftp_t *ftp, int i)
{
    char *list = strdup(ftp->tmp->directory);
    my_strcat(&list, "/");
    my_strcat(&list, ftp->commands[1]);

    if (list_error(ftp) == true)
        return (ftp);
    char *dir = (i == 1) ? list : ftp->tmp->directory;
    dprintf(ftp->tmp->client_fd, M_150);
    pid_t value = fork();
    value == -1 ? exit(84) : 0;
    if (value == 0)
        exec_list(ftp, dir);
    dprintf(ftp->tmp->client_fd, M_226);
    ftp->tmp->pasv == true ? close(ftp->tmp->pasv_fd) : 0;
    ftp->tmp->pasv = false;
    ftp->tmp->pasv_fd = -1;
    ftp->tmp->active == true ? close(ftp->tmp->port_fd) : 0;
    ftp->tmp->active = false;
    ftp->tmp->port_fd = -1;
    return (ftp);
}
