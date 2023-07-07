/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** client
*/

#include "zappy.h"

client_t *add_client(client_t *client, int sock)
{
    client_t *new = malloc(sizeof(client_t));

    new->id = get_last_id(client) + 1;
    new->cliFD = sock;
    new->terminated = false;
    new->next = NULL;
    new->wBuffer = NULL;
    new->rBuffLen = 0;
    new->wBuffLen = 0;
    new->teamName = NULL;
    new->isGraphical = false;
    new->cmd = NULL;
    new->next_on_tile = NULL;
    new->player = NULL;
    if (client == NULL)
        return new;
    client_t *tmp = client;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return client;
}

static void free_client_node(client_t *client)
{
    close(client->cliFD);
    client->teamName != NULL ? free(client->teamName) : 0;
    client->wBuffer != NULL ? free(client->wBuffer) : 0;
    client->cmd != NULL ? free_command(client->cmd) : 0;
    client->player != NULL ? free_player(client->player) : 0;
    free(client);
}

client_t *remove_cli(client_t *list)
{
    client_t *tmp = list;

    if (list == NULL)
        return NULL;
    if (list->terminated == true) {
        list = list->next;
        free_client_node(tmp);
        return list;
    }
    for (client_t *tmp2 = list; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->next->terminated == true) {
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free_client_node(tmp2);
            return list;
        }
    }
    return list;
}

client_t *get_last_client(client_t *list)
{
    client_t *tmp = list;

    if (list == NULL)
        return NULL;
    for (; tmp->next != NULL; tmp = tmp->next);
    return tmp;
}

int get_last_id(client_t *list)
{
    client_t *tmp = list;
    int id = 0;

    if (list == NULL)
        return 0;
    for (; tmp->next != NULL; tmp = tmp->next);
    id = tmp->id;
    return id;
}
