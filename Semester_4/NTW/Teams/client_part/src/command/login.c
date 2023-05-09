/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** login
*/

#include "client.h"

void login(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_event_logged_in(buffer[1], buffer[2]);
}
