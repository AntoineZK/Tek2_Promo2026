/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** egg
*/

#include "zappy.h"

void free_egg(eggs_t *list)
{
    eggs_t *current = list;
    eggs_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->team_name);
        free(current);
        current = next;
    }
}

eggs_t *get_egg_by_team_name(eggs_t *list, char *team_name)
{
    eggs_t *tmp = list;

    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->team_name, team_name) == 0)
            return tmp;
    }
    return NULL;
}

eggs_t *remove_egg(eggs_t *list, eggs_t *toRemove)
{
    eggs_t *tmp = list;
    eggs_t *prev = NULL;

    if (tmp != NULL && tmp == toRemove) {
        list = tmp->next;
        free(tmp->team_name);
        free(tmp);
        return list;
    }
    for (; tmp != NULL && tmp != toRemove; tmp = tmp->next)
        prev = tmp;
    if (tmp == NULL)
        return list;
    prev->next = tmp->next;
    free(tmp->team_name);
    free(tmp);
    return list;
}
