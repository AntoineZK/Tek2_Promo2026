/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** socket
*/

#include "zappy.h"

int create_server(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int opt = 1;
    int optName = SO_REUSEADDR | SO_REUSEPORT;

    if (server_fd == 0)
        return -1;
    if (setsockopt(server_fd, SOL_SOCKET, optName, &opt, sizeof(opt)))
        return -1;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    if (listen(server_fd, 10000) < 0)
        return -1;
    return (server_fd);
}
