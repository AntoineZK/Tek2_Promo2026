/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** handle_buffer
*/

#include "zappy.h"

static void update_rbuffer(client_t *cli, int len)
{
    memcpy(cli->rBuffer, cli->rBuffer + len, cli->rBuffLen - len);
    cli->rBuffLen -= len;
    cli->rBuffer[cli->rBuffLen] = '\0';
}

void handle_buffer(zappy_t *zap, client_t *tmp, int recvLen)
{
    tmp->rBuffLen += recvLen;
    tmp->rBuffer[tmp->rBuffLen] = '\0';

    for (char *delPos = strchr(tmp->rBuffer, '\n'); delPos != NULL;
    delPos = strchr(tmp->rBuffer, '\n')) {
        *delPos = '\0';
        char *subString = strdup(tmp->rBuffer);
        zap->argv->isNcurses ? zap->ncurses->receivingCommand =
        add_command(zap->ncurses->receivingCommand, subString, tmp->id) : 0;
        update_rbuffer(tmp, strlen(subString) + 1);
        if (nb_command(tmp->cmd) == 10) {
            free(subString);
            continue;
        }
        tmp->cmd = add_command(tmp->cmd, subString, tmp->id);
        free(subString);
    }
}
