/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** subscribe
*/

#include "client.h"

void subscribe(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_print_subscribed(buffer[1], buffer[2]);
}

void unsubscribe(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_print_unsubscribed(buffer[1], buffer[2]);
}
