/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** create
*/

#include "client.h"

static void creating_thread_reply(char **args)
{
    if (strcmp(args[1], "THREAD") == 0) {
        time_t time = str_to_time(args[4]);
        if (atoi(args[7]) == 1)
            client_print_thread_created(args[2], args[3], time, args[5],
            args[6]);
        client_event_thread_created(args[2], args[3], time, args[5], args[6]);
    }
    if (strcmp(args[1], "REPLY") == 0) {
        time_t time = str_to_time(args[6]);
        if (atoi(args[7]) == 1)
            client_print_reply_created(args[3], args[4], time, args[5]);
        client_event_thread_reply_received(args[2], args[3], args[4], args[5]);
    }
}

void creating(teams_t *teams, char **args)
{
    (void)(teams);
    if (strcmp(args[1], "TEAM") == 0) {
        if (atoi(args[5]) == 1)
            client_print_team_created(args[2], args[3], args[4]);
        client_event_team_created(args[2], args[3], args[4]);
    }
    if (strcmp(args[1], "CHANNEL") == 0) {
        if (atoi(args[5]) == 1)
            client_print_channel_created(args[2], args[3], args[4]);
        client_event_channel_created(args[2], args[3], args[4]);
    }
    creating_thread_reply(args);
}
