/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** info
*/

#include "server.h"

bool info_error(sockcli_t *cli, char **args)
{
    if (cli->client == NULL) {
        update_wbuffer(cli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) > 1) {
        update_wbuffer(cli, "ERROR: Invalid number of arguments\n");
        return (true);
    }
    return (false);
}

void info_thread(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    channel_t *channel = get_channel(team->channels, cli->contextArgs[1]);
    thread_t *thread = get_thread(channel->threads, cli->contextArgs[2]);
    char *res = gen_resp("INFO", 6, "THREAD", thread->uuid,
    cli->client->infos->uuid, time_to_str(thread->creation_date), thread->title,
    thread->message);
    update_wbuffer(cli, res);
    free(res);
}

void info_channel(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    channel_t *channel = get_channel(team->channels, cli->contextArgs[1]);
    char *res = gen_resp("INFO", 4, "CHANNEL", channel->uuid,
    channel->name, channel->description);
    update_wbuffer(cli, res);
    free(res);
}

void info_team(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    char *res = gen_resp("INFO", 4, "TEAM", team->uuid, team->name,
    team->description);
    update_wbuffer(cli, res);
    free(res);
}

void info(teams_t *teams, sockcli_t *cli, char **args)
{
    if (info_error(cli, args))
        return;
    if (cli->context == TEAM) {
        char *res = gen_resp("USER", 3, cli->client->infos->uuid,
        cli->client->infos->username, "1");
        update_wbuffer(cli, res);
        free(res);
    }
    cli->context == CHANNEL ? info_team(teams, cli) : 0;
    cli->context == THREAD ? info_channel(teams, cli) : 0;
    cli->context == REPLY ? info_thread(teams, cli) : 0;
}
