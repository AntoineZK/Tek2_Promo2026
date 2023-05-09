/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** list
*/

#include "server.h"

bool list_error(sockcli_t *cli, char **args)
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

void list_reply(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    channel_t *chan = get_channel(team->channels, cli->contextArgs[1]);
    thread_t *thread = get_thread(chan->threads, cli->contextArgs[2]);
    for (reply_t *reply = thread->replies; reply; reply = reply->next) {
        char *time = time_to_str(reply->creation_date);
        char *replyData = gen_resp("LIST", 5, "REPLY",
        thread->uuid, reply->author_uuid, time, reply->body);
        update_wbuffer(cli, replyData);
        free(replyData);
        free(time);
    }
}

void list_thread(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    channel_t *chan = get_channel(team->channels, cli->contextArgs[1]);
    for (thread_t *thread = chan->threads; thread; thread = thread->next) {
        char *time = time_to_str(thread->creation_date);
        char *threadData = gen_resp("LIST", 6, "THREAD", thread->uuid,
        thread->author_uuid, time, thread->title, thread->message);
        update_wbuffer(cli, threadData);
        free(threadData);
        free(time);
    }
}

void list_channel(teams_t *teams, sockcli_t *cli)
{
    team_t *team = get_team(teams->ntw->allTeam, cli->contextArgs[0]);
    for (channel_t *chan = team->channels; chan; chan = chan->next) {
        char *chanData = gen_resp("LIST", 4, "CHANNEL", chan->uuid,
        chan->name, chan->description);
        update_wbuffer(cli, chanData);
        free(chanData);
    }
}

void list_team_channel_thread(teams_t *teams, sockcli_t *cli, char **args)
{
    if (list_error(cli, args))
        return;
    if (cli->context == TEAM) {
        for (team_t *team = teams->ntw->allTeam; team; team = team->next) {
            char *teamData = gen_resp("LIST", 4, "TEAM", team->uuid,
            team->name, team->description);
            update_wbuffer(cli, teamData);
            free(teamData);
        }
    }
    cli->context == CHANNEL ? list_channel(teams, cli) : 0;
    cli->context == THREAD ? list_thread(teams, cli) : 0;
    cli->context == REPLY ? list_reply(teams, cli) : 0;
}
