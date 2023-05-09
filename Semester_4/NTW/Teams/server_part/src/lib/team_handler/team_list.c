/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** team_list
*/

#include "server.h"

team_t *add_team(team_t *team, char *name, char *desc)
{
    team_t *new_team = malloc(sizeof(team_t));
    team_t *tmp = team;

    if (!new_team)
        return NULL;
    new_team->name = strdup(name);
    new_team->description = strdup(desc);
    new_team->uuid = generate_uuid();
    new_team->channels = NULL;
    new_team->members = NULL;
    new_team->next = NULL;
    if (!team)
        return new_team;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_team;
    return team;
}

bool team_exist(team_t *team, char *uuid)
{
    team_t *tmp = team;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return true;
    return false;
}

team_t *get_team(team_t *team, char *uuid)
{
    team_t *tmp = team;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
    return NULL;
}

team_t *get_last_team(team_t *allTeam)
{
    team_t *tmp = allTeam;

    for (; tmp->next; tmp = tmp->next);
    return tmp;
}

void free_team(team_t *team)
{
    team_t *current = team;
    team_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->description);
        free(current->uuid);
        if (current->members)
            free_member(current->members);
        if (current->channels)
            free_channel(current->channels);
        free(current);
        current = next;
    }
}
