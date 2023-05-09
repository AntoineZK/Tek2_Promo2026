/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** member_list
*/

#include "server.h"

member_t *add_member(member_t *member, char *name, char *uuid)
{
    member_t *new_member = malloc(sizeof(member_t));
    member_t *tmp = member;

    if (!new_member)
        return NULL;
    new_member->name = strdup(name);
    new_member->uuid = strdup(uuid);
    new_member->next = NULL;
    if (!member)
        return new_member;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_member;
    return member;
}

void remove_member(member_t **head, char *name, char *uuid)
{
    member_t *prev = NULL;
    member_t *curr = *head;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0 && strcmp(curr->uuid, uuid) == 0) {
            prev == NULL ? *head = curr->next : (prev->next = curr->next);
            free(curr->name);
            free(curr->uuid);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool ismember(team_t *team, char *uuid)
{
    member_t *tmp = team->members;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return true;
    return false;
}

void free_member(member_t *member)
{
    member_t *current = member;
    member_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->uuid);
        free(current);
        current = next;
    }
}
