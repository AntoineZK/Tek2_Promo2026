/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** server_to_graphic
*/

#include "zappy.h"

bool serv_to_graph(zappy_t *zap, char **cmd)
{
    message_from_serv(zap, cmd[1]);
    int maxSize = snprintf(NULL, 0, "Server send \"%s\" to graphicals", cmd[1]);
    char *str = alloca(sizeof(char) * (maxSize + 1));
    snprintf(str, maxSize + 1, "Server send \"%s\" to graphicals", cmd[1]);
    zap->argv->isNcurses ? zap->ncurses->serverResponse =
    add_command(zap->ncurses->serverResponse, str, 0) : 0;
    return (true);
}
