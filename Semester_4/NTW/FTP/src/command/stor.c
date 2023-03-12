/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** stor
*/

#include "ftp.h"

bool stor_error(ftp_t *ftp)
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

void exec_stor(ftp_t *ftp, char *buffer, size_t size)
{
    int new_client = 0;
    char *list = strdup(ftp->tmp->directory);
    my_strcat(&list, "/");
    my_strcat(&list, ftp->commands[1]);
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
    FILE *file = fopen(list, "w");
    FILE *pasv = fdopen(new_client, "r");
    while (getline(&buffer, &size, pasv) != -1)
        fprintf(file, "%s", buffer);
    fclose(file);
    exit(84);
}

ftp_t *stor(ftp_t *ftp, int j)
{
    size_t size = 0;
    char *buffer = NULL;
    pid_t value;

    if (stor_error(ftp))
        return (ftp);
    dprintf(ftp->tmp->client_fd, M_150);
    value = fork();
    value == -1 ? exit(84) : 0;
    if (value == 0)
        exec_stor(ftp, buffer, size);
    dprintf(ftp->tmp->client_fd, M_226);
    ftp->tmp->pasv == true ? close(ftp->tmp->pasv_fd) : 0;
    ftp->tmp->pasv = false;
    ftp->tmp->pasv_fd = -1;
    ftp->tmp->active == true ? close(ftp->tmp->port_fd) : 0;
    ftp->tmp->active = false;
    ftp->tmp->port_fd = -1;
    return (ftp);
}
