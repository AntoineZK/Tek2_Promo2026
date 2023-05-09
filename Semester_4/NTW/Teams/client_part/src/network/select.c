/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** select
*/

#include "client.h"

void setup_select(teams_t *teams)
{
    FD_ZERO(&teams->readfds);
    FD_ZERO(&teams->writefds);
    FD_SET(teams->socket_fd, &teams->readfds);
    if (teams->header != NULL && teams->header->size > 0)
        FD_SET(teams->socket_fd, &teams->writefds);
    FD_SET(STDIN_FILENO, &teams->readfds);
}

int send_message(teams_t *teams)
{
    char buffer[MAX_BODY_LENGTH];

    if (FD_ISSET(STDIN_FILENO, &teams->readfds)) {
        fgets(buffer, MAX_BODY_LENGTH, stdin);
        teams->header = create_header(buffer);
    }
    if (FD_ISSET(teams->socket_fd, &teams->writefds)
    && teams->header != NULL) {
        send(teams->socket_fd, teams->header,
        sizeof(header_t) + teams->header->size, 0);
        free(teams->header);
        teams->header = NULL;
    }
    return 0;
}

int receive_response(teams_t *teams)
{
    char buffer[MAX_BODY_LENGTH + 1];

    if (FD_ISSET(teams->socket_fd, &teams->readfds)) {
        ssize_t recvLen = recv(teams->socket_fd, buffer, MAX_BODY_LENGTH, 0);
        if (recvLen == -1) {
            printf("Error: %s\n", strerror(errno));
            exit(84);
            return -1;
        }
        if (recvLen == 0) {
            free(teams);
            printf("Server disconnected\n");
            exit(0);
            return 0;
        } else {
            buffer[recvLen] = '\0';
            launch_commands(teams, buffer);
        }
    }
    return 0;
}
