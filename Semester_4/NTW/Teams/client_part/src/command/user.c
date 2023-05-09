/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** user
*/

#include "client.h"

void user(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_print_user(buffer[1], buffer[2], atoi(buffer[3]));
}
