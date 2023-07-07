/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** format_message_ncurses
*/

#include "zappy.h"

int calculate_size(boxes_t *box, char *cmd)
{
    int sizeCmd = strlen(cmd);
    int width = box->size[0];
    int fullLines = sizeCmd / width + 1;

    return fullLines;
}

bool is_higher_than_box(boxes_t *box, command_t *cmd)
{
    int size = 2;
    for (command_t *tmp = cmd; tmp != NULL; tmp = tmp->next)
        size += calculate_size(box, tmp->cmd);
    if (size >= box->size[1])
        return true;
    return false;
}
