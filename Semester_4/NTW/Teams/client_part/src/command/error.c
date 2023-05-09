/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** error
*/

#include "client.h"

void error_team(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_error_unknown_team(buffer[1]);
}

void error_channel(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_error_unknown_channel(buffer[1]);
}

void error_thread(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_error_unknown_thread(buffer[1]);
}

void error_user(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_error_unknown_user(buffer[1]);
}

void error_unauthorized(teams_t *teams, char **buffer)
{
    (void)(teams);
    (void)(buffer);
    client_error_unauthorized();
}
