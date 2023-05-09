/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** launch_command
*/

#include "client.h"

static command_t commands[] = {
    {"LOGIN", &login},
    {"LOGOUT", &logout},
    {"USERS", &users},
    {"USER", &user},
    {"SEND", &send_report},
    {"MESSAGES", &list_message},
    {"SUBSCRIBE", &subscribe},
    {"UNSUBSCRIBE", &unsubscribe},
    {"CREATE", &creating},
    {"LIST", &list_all},
    {"INFO", &info_data},
    {"ERROR1", &error_team},
    {"ERROR2", &error_channel},
    {"ERROR3", &error_thread},
    {"ERROR4", &error_user},
    {"ERROR5", &error_unauthorized},
    {NULL, NULL}
};

void free_darray(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void launch_commands(teams_t *teams, char *buffer)
{
    char **args = split_string(buffer);

    if (args == NULL)
        return;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            commands[i].function(teams, args);
            free_darray(args);
            return;
        }
    }
    printf("%s", buffer);
    free_darray(args);
}
