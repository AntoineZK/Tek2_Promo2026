/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** use
*/

#include "server.h"

char **get_context_args(char **args)
{
    char **contextArgs = malloc(sizeof(char *) * len_darray(args));

    for (int i = 1; args[i]; i++)
        contextArgs[i - 1] = strdup(args[i]);
    contextArgs[len_darray(args) - 1] = NULL;
    return contextArgs;
}

void use_team3(channel_t *channel, sockcli_t *actCli, char **args)
{
    thread_t *thread = get_thread(channel->threads, args[3]);
    if (!thread) {
        char *response = gen_resp("ERROR3", 1, args[3]);
        update_wbuffer(actCli, response);
        free(response);
        return;
    }
    free_darray(actCli->contextArgs);
    actCli->contextArgs = get_context_args(args);
    if (len_darray(args) == 4) {
        actCli->context = REPLY;
        return;
    }
}

void use_team2(team_t *team, sockcli_t *actCli, char **args)
{
    channel_t *channel = get_channel(team->channels, args[2]);
    if (!channel) {
        char *response = gen_resp("ERROR2", 1, args[2]);
        update_wbuffer(actCli, response);
        free(response);
        return;
    }
    free_darray(actCli->contextArgs);
    actCli->contextArgs = get_context_args(args);
    if (len_darray(args) == 3) {
        actCli->context = THREAD;
        return;
    }
    use_team3(channel, actCli, args);
}

void use_team(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (len_darray(args) == 1) {
        actCli->context = TEAM;
        return;
    }
    team_t *team = get_team(teams->ntw->allTeam, args[1]);
    if (!team) {
        char *error = gen_resp("ERROR1", 1, args[1]);
        update_wbuffer(actCli, error);
        free(error);
        return;
    }
    actCli->contextArgs = get_context_args(args);
    if (len_darray(args) == 2) {
        actCli->context = CHANNEL;
        return;
    }
    use_team2(team, actCli, args);
}
