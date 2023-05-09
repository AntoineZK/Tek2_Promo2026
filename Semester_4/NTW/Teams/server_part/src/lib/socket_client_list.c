/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** socket_client_list
*/

#include "server.h"

sockcli_t *add_socket_client(sockcli_t *list, int fd)
{
    sockcli_t *new = malloc(sizeof(sockcli_t));

    new->fd = fd;
    new->terminated = false;
    new->next = NULL;
    new->client = NULL;
    new->writeBuffer = NULL;
    new->rBufferLen = 0;
    new->writeBufferLen = 0;
    new->context = TEAM;
    new->contextArgs = NULL;
    if (list == NULL)
        return new;
    sockcli_t *tmp = list;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return list;
}

sockcli_t *disconnect_sockcli(sockcli_t *list)
{
    sockcli_t *tmp = list;

    if (list == NULL)
        return NULL;
    if (list->terminated == true) {
        list = list->next;
        close(tmp->fd);
        free(tmp);
        return list;
    }
    for (sockcli_t *tmp2 = list; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->next->terminated == true) {
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            close(tmp2->fd);
            free(tmp2);
            return list;
        }
    }
    return list;
}

void print_socket_client(sockcli_t *list)
{
    if (list != NULL)
        printf("Client list: ");
    for (sockcli_t *tmp = list; tmp != NULL; tmp = tmp->next) {
        if (tmp->next == NULL)
            printf("%d\n", tmp->fd);
        else
            printf("%d, ", tmp->fd);
    }
}

void free_socket_client(sockcli_t *list)
{
    sockcli_t *current = list;
    sockcli_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        if (current->contextArgs != NULL)
            free_darray(current->contextArgs);
        if (current->client != NULL)
            free_client(current->client);
        free(current);
        current = next;
    }
}

bool same_sockcli(sockcli_t *cli1, sockcli_t *cli2)
{
    if (cli1->fd == cli2->fd)
        return true;
    return false;
}
