/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** subscribe
*/

#include "server.h"

bool subscribe_error(char **args, sockcli_t *actCli, teams_t *a)
{
    if (len_darray(args) != 2) {
        update_wbuffer(actCli, "ERROR: Invalid number of arguments\n");
        return true;
    }
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return true;
    }
    if (team_exist(a->ntw->allTeam, args[1]) == false) {
        char *response = gen_resp("ERROR4", 1, args[1]);
        update_wbuffer(actCli, response);
        free(response);
        return true;
    }
    return false;
}

void subscribe(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (subscribe_error(args, actCli, teams))
        return;
    team_t *team = get_team(teams->ntw->allTeam, args[1]);
    if (ismember(team, actCli->client->infos->uuid) == true) {
        update_wbuffer(actCli, "ERROR: Already subscribed\n");
        return;
    }
    team->members = add_member(team->members, actCli->client->infos->username,
    actCli->client->infos->uuid);
    server_event_user_subscribed(team->uuid, actCli->client->infos->uuid);
    char *response = gen_resp("SUBSCRIBE", 2,
    actCli->client->infos->uuid, team->uuid);
    update_wbuffer(actCli, response);
    free(response);
}
