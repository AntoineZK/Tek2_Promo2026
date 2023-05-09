/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** client_list2
*/

#include "server.h"

bool client_exist(client_t *list, char *uuid)
{
    for (client_t *tmp = list; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->infos->uuid, uuid) == 0)
            return (true);
    }
    return (false);
}

void free_all_client(client_t *list)
{
    client_t *current = list;
    client_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free_client(current);
        current = next;
    }
}
