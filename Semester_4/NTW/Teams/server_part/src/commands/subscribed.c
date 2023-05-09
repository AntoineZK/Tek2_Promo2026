/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** subscribed
*/

#include "server.h"

bool subscribed_error(sockcli_t *cli, char **args)
{
    if (cli->client == NULL) {
        update_wbuffer(cli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) > 2) {
        update_wbuffer(cli, "ERROR: Invalid number of arguments\n");
        return (true);
    }
    return (false);
}

void subscribed_list(teams_t *teams, sockcli_t *cli)
{
    team_t *team = teams->ntw->allTeam;
    for (; team; team = team->next) {
        if (ismember(team, cli->client->infos->uuid) == true) {
            char *teamData = gen_resp("LIST", 4, "TEAM", team->uuid,
            team->name, team->description);
            update_wbuffer(cli, teamData);
        }
    }
}

void subscribed_team(teams_t *teams, sockcli_t *cli, char *team_uuid)
{
    team_t *team = get_team(teams->ntw->allTeam, team_uuid);
    if (team == NULL) {
        char *rep = gen_resp("ERROR1", 1, team_uuid);
        update_wbuffer(cli, rep);
        free(rep);
        return;
    }
    if (ismember(team, cli->client->infos->uuid) == false) {
        update_wbuffer(cli, "ERROR5\n");
        return;
    }
    for (client_t *client = teams->ntw->allCli; client; client = client->next) {
        if (ismember(team, client->infos->uuid) == true) {
            char *con = client->is_connected == true ? "1" : "0";
            char *rep = gen_resp("USERS", 4, client->infos->uuid,
            client->infos->username, con);
            update_wbuffer(cli, rep);
            free(rep);
        }
    }
}

void subscribed(teams_t *teams, sockcli_t *cli, char **args)
{
    if (subscribed_error(cli, args))
        return;
    if (len_darray(args) == 1) {
        subscribed_list(teams, cli);
        return;
    }
    subscribed_team(teams, cli, args[1]);
}
