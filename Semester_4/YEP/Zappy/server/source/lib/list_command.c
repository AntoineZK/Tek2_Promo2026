/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** list_command
*/

#include "zappy.h"

command_t *add_command(command_t *list, char *cmd, int id)
{
    command_t *new = malloc(sizeof(command_t));
    command_t *tmp = list;

    new->cmd = strdup(cmd);
    new->id = id;
    new->next = NULL;
    if (list == NULL)
        return new;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return list;
}

command_t *remove_command(command_t *list)
{
    command_t *tmp = list;

    if (list == NULL)
        return NULL;
    list = list->next;
    free(tmp->cmd);
    free(tmp);
    return list;
}

int nb_command(command_t *list)
{
    int i = 0;

    for (; list != NULL; list = list->next, i++);
    return i;
}

void free_command(command_t *list)
{
    command_t *current = list;
    command_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->cmd);
        free(current);
        current = next;
    }
}
