/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** users
*/

#include "client.h"

static int len_darray(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return (i);
}

void users(teams_t *teams, char **buffer)
{
    (void)(teams);
    int len = len_darray(buffer);
    for (int i = 0; i < len / 4; i++) {
        client_print_users(buffer[i * 4 + 1], buffer[i * 4 + 2],
        atoi(buffer[i * 4 + 3]));
    }

}
