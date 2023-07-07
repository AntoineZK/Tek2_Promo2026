/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** free
*/

#include "zappy.h"

void free_client(client_t *client)
{
    client_t *current = client;
    client_t *next = NULL;

    while (current) {
        next = current->next;
        if (current->teamName)
            free(current->teamName);
        if (current->wBuffer) {
            free(current->wBuffer);
            current->wBuffer = NULL;
        }
        current->cmd != NULL ? free_command(current->cmd) : 0;
        current->player != NULL ? free_player(current->player) : 0;
        free(current);
        current = next;
    }
}

void free_network(network_t *network)
{
    free_client(network->clients);
    free(network);
}

void free_zappy(zappy_t *zappy)
{
    free_egg(zappy->eggs);
    free_ressources(zappy->ressources);
    free_map(zappy->map);
    free_network(zappy->ntw);
    free_argv(zappy->argv);
    free(zappy);
}
