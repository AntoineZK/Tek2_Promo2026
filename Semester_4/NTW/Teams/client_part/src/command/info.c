/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** info
*/

#include "client.h"

void info_data(teams_t *teams, char **args)
{
    (void)(teams);
    if (strcmp(args[1], "TEAM") == 0)
        client_print_team(args[2], args[3], args[4]);
    if (strcmp(args[1], "CHANNEL") == 0)
        client_print_channel(args[2], args[3], args[4]);
    if (strcmp(args[1], "THREAD") == 0) {
        time_t time = str_to_time(args[4]);
        client_print_thread(args[2], args[3], time, args[5], args[6]);
    }
}
