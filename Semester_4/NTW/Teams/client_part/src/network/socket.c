/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** socket
*/

#include "client.h"

int create_socket(const char *ip, int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int inet = 0;
    int connect_fd = 0;

    if (socket_fd == 0)
        exit(EXIT_FAILURE);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet = inet_pton(AF_INET, ip, &addr.sin_addr);
    if (inet <= 0)
        exit(EXIT_FAILURE);
    connect_fd = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connect_fd < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}
