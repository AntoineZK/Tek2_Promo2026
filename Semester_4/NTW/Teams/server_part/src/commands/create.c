/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** create
*/

#include "server.h"

bool create_error(char **args, sockcli_t *actCli)
{
    if (len_darray(args) != 3 && len_darray(args) != 2) {
        update_wbuffer(actCli, "Invalid number of arguments\n");
        return true;
    }
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return true;
    }
    return false;
}

void create_team(teams_t *teams, sockcli_t *actCli, char **args)
{
    teams->ntw->allTeam = add_team(teams->ntw->allTeam, args[1], args[2]);
    team_t *team = get_last_team(teams->ntw->allTeam);
    server_event_team_created(team->uuid, team->name,
    actCli->client->infos->uuid);
    char *rep = gen_resp("CREATE", 5, "TEAM", team->uuid, team->name,
    team->description, "1");
    char *rep2 = gen_resp("CREATE", 5, "TEAM", team->uuid, team->name,
    team->description, "0");
    for (sockcli_t *cliCo = teams->ntw->cliCon; cliCo; cliCo = cliCo->next) {
        if (cliCo->client != NULL && same_sockcli(cliCo, actCli) == false)
            update_wbuffer(cliCo, rep2);
        if (cliCo->client != NULL && same_sockcli(cliCo, actCli) == true)
            update_wbuffer(cliCo, rep);
    }
    free(rep);
    free(rep2);
}

static void create_chan2(teams_t *teams, sockcli_t *actCli, team_t *team,
channel_t *chan)
{
    char *rep = gen_resp("CREATE", 5, "CHANNEL", chan->uuid, chan->name,
    chan->description, "1");
    char *rep2 = gen_resp("CREATE", 5, "CHANNEL", chan->uuid, chan->name,
    chan->description, "0");
    for (sockcli_t *cliCo = teams->ntw->cliCon; cliCo; cliCo = cliCo->next) {
        if (cliCo->client != NULL && ismember(team, cliCo->client->infos->uuid))
            same_sockcli(cliCo, actCli) == false ?
            update_wbuffer(cliCo, rep2) : update_wbuffer(cliCo, rep);
    }
    free(rep);
    free(rep2);
}

void create_channel(teams_t *teams, sockcli_t *actCli, char **args)
{
    team_t *team = get_team(teams->ntw->allTeam, actCli->contextArgs[0]);
    if (ismember(team, actCli->client->infos->uuid) == false) {
        update_wbuffer(actCli, "ERROR5\n");
        return;
    }
    team->channels = add_channel(team->channels, args[1], args[2]);
    channel_t *chan = get_last_channel(team->channels);
    server_event_channel_created(team->uuid, chan->uuid, chan->name);
    create_chan2(teams, actCli, team, chan);
}

void create(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (create_error(args, actCli) == true)
        return;
    if (len_darray(args) == 3) {
        actCli->context == TEAM ? create_team(teams, actCli, args) : 0;
        actCli->context == CHANNEL ? create_channel(teams, actCli, args) : 0;
        actCli->context == THREAD ? create_thread(teams, actCli, args) : 0;
    }
    if (len_darray(args) == 2)
        actCli->context == REPLY ? create_reply(teams, actCli, args) : 0;
}
