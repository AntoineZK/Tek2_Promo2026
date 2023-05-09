/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** exec_commands
*/

#include "server.h"

static command_t commands[] = {
    {"/help", &help},
    {"/login", &login},
    {"/logout", &logout},
    {"/users", &users},
    {"/user", &user},
    {"/send", &send_message},
    {"/messages", &list_message},
    {"/subscribe", &subscribe},
    {"/subscribed", &subscribed},
    {"/unsubscribe", &unsubscribe},
    {"/use", &use_team},
    {"/create", &create},
    {"/list", &list_team_channel_thread},
    {"/info", &info},
    {"exit", &exit_server},
    {"stop", &stop_server},
    {NULL, NULL}
};

void execute_command(teams_t *teams, sockcli_t *tmp)
{
    char **array = split_string(teams->header->body);
    int size = len_darray(array);

    if (size == 0)
        return;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(array[0], commands[i].name) == 0)
            commands[i].function(teams, tmp, array);
    }
    free_darray(array);
}
