/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** client_list
*/

#include "server.h"

client_t *load_all_cli(teams_t *teams)
{
    (void)(teams);
    client_t *lst_cli = NULL;
    char name[4][10] = {"Antoine", "Alex", "Romain", "Toto Rac"};

    for (int i = 0; i <= 3; i++) {
        char *uuid_str = generate_uuid();
        lst_cli = add_client(lst_cli, name[i], uuid_str);
        server_event_user_loaded(uuid_str, name[i]);
        free(uuid_str);
    }
    return lst_cli;
}

client_t *add_client(client_t *client, char *name, char *uuid)
{
    client_t *new = malloc(sizeof(client_t));

    new->is_connected = false;
    new->infos = malloc(sizeof(infos_t));
    new->infos->username = strdup(name);
    new->infos->uuid = strdup(uuid);
    new->next = NULL;
    if (client == NULL)
        return new;
    client_t *tmp = client;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return client;
}

client_t *duplicate_client(client_t *src)
{
    client_t *new = malloc(sizeof(client_t));

    new->is_connected = true;
    new->infos = malloc(sizeof(infos_t));
    new->infos->username = strdup(src->infos->username);
    new->infos->uuid = strdup(src->infos->uuid);
    new->next = NULL;
    return new;
}

client_t *get_last_client(client_t *allCli)
{
    client_t *tmp = allCli;

    for (; tmp->next != NULL; tmp = tmp->next);
    return tmp;
}

client_t *free_client(client_t *client)
{
    free(client->infos->username);
    free(client->infos->uuid);
    free(client->infos);
    free(client);
    return NULL;
}
