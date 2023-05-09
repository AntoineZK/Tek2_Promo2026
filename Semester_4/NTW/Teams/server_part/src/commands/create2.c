/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** create2
*/

#include "server.h"

static void create_thread2(teams_t *teams, sockcli_t *actCli, thread_t *thread,
team_t *team)
{
    char *time = time_to_str(thread->creation_date);
    char *rep = gen_resp("CREATE", 7, "THREAD", thread->uuid,
    actCli->client->infos->uuid, time, thread->title, thread->message, "1");
    char *rep2 = gen_resp("CREATE", 7, "THREAD", thread->uuid,
    actCli->client->infos->uuid, time, thread->title, thread->message, "0");
    for (sockcli_t *cliCo = teams->ntw->cliCon; cliCo; cliCo = cliCo->next) {
        if (cliCo->client != NULL && ismember(team, cliCo->client->infos->uuid))
            same_sockcli(cliCo, actCli) == false ?
            update_wbuffer(cliCo, rep2) : update_wbuffer(cliCo, rep);
    }
    free(rep);
    free(rep2);
}

void create_thread(teams_t *teams, sockcli_t *actCli, char **args)
{
    team_t *team = get_team(teams->ntw->allTeam, actCli->contextArgs[0]);
    if (ismember(team, actCli->client->infos->uuid) == false) {
        update_wbuffer(actCli, "ERROR5\n");
        return;
    }
    channel_t *channel = get_channel(team->channels, actCli->contextArgs[1]);
    channel->threads = add_thread(channel->threads, args[1], args[2],
    actCli->client->infos->uuid);
    thread_t *thread = get_last_thread(channel->threads);
    server_event_thread_created(channel->uuid, thread->uuid,
    actCli->client->infos->uuid, thread->title, thread->message);
    create_thread2(teams, actCli, thread, team);
}

void create_reply2(teams_t *teams, sockcli_t *actCli, char **args, team_t *team)
{
    channel_t *channel = get_channel(team->channels, actCli->contextArgs[1]);
    thread_t *thread = get_thread(channel->threads, actCli->contextArgs[2]);
    thread->replies = add_reply(thread->replies, args[1],
    actCli->client->infos->uuid);
    reply_t *reply = get_last_reply(thread->replies);
    server_event_reply_created(thread->uuid, actCli->client->infos->uuid,
    reply->body);
    char *time = time_to_str(reply->creation_date);
    char *rep = gen_resp("CREATE", 7, "REPLY", team->uuid, thread->uuid,
    actCli->client->infos->uuid, reply->body, time, "1");
    char *rep2 = gen_resp("CREATE", 7, "REPLY", team->uuid, thread->uuid,
    actCli->client->infos->uuid, reply->body, time, "0");
    free(time);
    for (sockcli_t *cliCo = teams->ntw->cliCon; cliCo; cliCo = cliCo->next) {
        if (cliCo->client != NULL && ismember(team, cliCo->client->infos->uuid))
            same_sockcli(cliCo, actCli) == false ?
            update_wbuffer(cliCo, rep2) : update_wbuffer(cliCo, rep);
    }
    free(rep);
    free(rep2);
}

void create_reply(teams_t *teams, sockcli_t *actCli, char **args)
{
    team_t *team = get_team(teams->ntw->allTeam, actCli->contextArgs[0]);
    if (ismember(team, actCli->client->infos->uuid) == false) {
        update_wbuffer(actCli, "ERROR5\n");
        return;
    }
    create_reply2(teams, actCli, args, team);
}
