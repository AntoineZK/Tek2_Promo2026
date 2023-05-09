/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** messages
*/

#include "client.h"

static int len_darray(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return (i);
}

void list_message(teams_t *teams, char **buffer)
{
    (void)(teams);
    int len = len_darray(buffer);
    for (int i = 0; i < len / 4; i++) {
        client_private_message_print_messages(buffer[1 + i * 4],
        str_to_time(buffer[2 + i * 4]), buffer[3 + i * 4]);
    }
}
