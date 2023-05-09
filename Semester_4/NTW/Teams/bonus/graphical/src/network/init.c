/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** init
*/

#include "graphic.h"

static int connect_to_server(const char *ip, int port)
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

header_t *create_header(char *buffer)
{
    header_t *header = malloc(sizeof(header_t) + (strlen(buffer) + 1));

    header->type = TEXT;
    header->size = strlen(buffer);
    strcpy(header->body, buffer);
    return (header);
}

network_t *init_network(char *ip, int port)
{
    network_t *network = malloc(sizeof(network_t));

    network->server_fd = connect_to_server(ip, port);
    network->header = NULL;
    network->timeout.tv_sec = 1;
    network->timeout.tv_usec = 0;
    return network;
}
