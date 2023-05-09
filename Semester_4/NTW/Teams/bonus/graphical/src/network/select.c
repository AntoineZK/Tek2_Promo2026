/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** select
*/

#include "graphic.h"

void setup_select(network_t *net)
{
    FD_ZERO(&net->readfds);
    FD_ZERO(&net->writefds);
    FD_SET(net->server_fd, &net->readfds);
    if (net->header != NULL && net->header->size > 0)
        FD_SET(net->server_fd, &net->writefds);
    FD_SET(STDIN_FILENO, &net->readfds);
}

void send_to_server(network_t *net)
{
    if (net->header != NULL && FD_ISSET(net->server_fd, &net->writefds)) {
        send(net->server_fd, net->header,
        sizeof(header_t) + net->header->size, 0);
        free(net->header);
        net->header = NULL;
    }
}

void read_from_server(network_t *net)
{
    ssize_t size = 0;
    char buffer[MAX_BODY_LENGTH + 1] = {0};

    if (FD_ISSET(net->server_fd, &net->readfds)) {
        size = recv(net->server_fd, buffer, MAX_BODY_LENGTH, 0);
        size == -1 ? exit(84) : 0;
        if (size == 0) {
            printf("Server disconnected\n");
            exit(0);
        } else {
            buffer[size] = '\0';
            printf("%s\n", buffer);
        }
    }
}

void handle_network(network_t *net)
{
    setup_select(net);
    select(net->server_fd + 1, &net->readfds, &net->writefds,
    NULL, &net->timeout);
    read_from_server(net);
    send_to_server(net);
}
