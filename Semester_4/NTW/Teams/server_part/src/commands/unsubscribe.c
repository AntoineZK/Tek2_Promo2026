/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** unsubscribe
*/

#include "server.h"

bool unsubscribe_error(char **args, sockcli_t *actCli, teams_t *teams)
{
    if (len_darray(args) != 2) {
        update_wbuffer(actCli, "ERROR: Invalid number of arguments\n");
        return true;
    }
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return true;
    }
    if (team_exist(teams->ntw->allTeam, args[1]) == false) {
        char *response = gen_resp("ERROR1", 1, args[1]);
        update_wbuffer(actCli, response);
        free(response);
        return true;
    }
    return false;
}

void unsubscribe(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (unsubscribe_error(args, actCli, teams))
        return;
    team_t *team = get_team(teams->ntw->allTeam, args[1]);
    if (ismember(team, actCli->client->infos->uuid) == false) {
        update_wbuffer(actCli,
        "ERROR: You are not subscribed to this team\n");
        return;
    }
    remove_member(&team->members, actCli->client->infos->username,
    actCli->client->infos->uuid);
    server_event_user_unsubscribed(team->uuid, actCli->client->infos->uuid);
    char *response = gen_resp("UNSUBSCRIBE", 2,
    actCli->client->infos->uuid, team->uuid);
    update_wbuffer(actCli, response);
    free(response);
}
