/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** list
*/

#include "client.h"

void list_all(teams_t *teams, char **args)
{
    (void)(teams);
    if (strcmp(args[1], "TEAM") == 0)
        client_print_teams(args[2], args[3], args[4]);
    if (strcmp(args[1], "CHANNEL") == 0)
        client_team_print_channels(args[2], args[3], args[4]);
    if (strcmp(args[1], "THREAD") == 0) {
        time_t time = str_to_time(args[4]);
        client_channel_print_threads(args[2], args[3], time, args[5], args[6]);
    }
    if (strcmp(args[1], "REPLY") == 0) {
        time_t time = str_to_time(args[4]);
        client_thread_print_replies(args[2], args[3], time, args[5]);
    }
}
