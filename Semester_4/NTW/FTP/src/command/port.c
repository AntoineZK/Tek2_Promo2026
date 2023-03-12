/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** port
*/

#include "ftp.h"

int connect_to_socket(ftp_t *ftp, int j)
{
    int connect_result = 0;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(ftp->tmp->port);
    addr.sin_addr.s_addr = inet_addr(ftp->tmp->ip);
    printf("Trying to connect to %s:%d.\n", ftp->tmp->ip, ftp->tmp->port);
    connect_result = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (connect_result == -1) {
        dprintf(ftp->tmp->client_fd, M_425);
        return (-1);
    }
    return (fd);
}

ftp_t *port(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    char **ip = my_stwa(ftp->commands[1], ",");
    if (len_darray(ip) != 6) {
        dprintf(ftp->clients[j].client_fd, M_501);
        return (ftp);
    }
    ftp->tmp->port = atoi(ip[4]) * 256 + atoi(ip[5]);
    ftp->tmp->ip = strdup(ip[0]);
    for (int i = 1; i < 4; i++) {
        my_strcat(&ftp->tmp->ip, ".");
        my_strcat(&ftp->tmp->ip, ip[i]);
    }
    dprintf(ftp->tmp->client_fd, M_200);
    printf("PORT : %i\r\n", ftp->tmp->port);
    ftp->tmp->port_fd = connect_to_socket(ftp, j);
    ftp->tmp->active = true;
    return (ftp);
}
