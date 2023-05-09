/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** users
*/

#include "server.h"

bool users_error(sockcli_t *actCli, char **args)
{
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) != 1) {
        update_wbuffer(actCli, "ERROR: Invalid number of arguments\n");
        return (true);
    }
    return (false);
}

void users(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (users_error(actCli, args))
        return;
    for (client_t *cli = teams->ntw->allCli; cli != NULL; cli = cli->next) {
        char *con = cli->is_connected == true ? "1" : "0";
        char *response = gen_resp("USERS", 3, cli->infos->uuid,
        cli->infos->username, con);
        update_wbuffer(actCli, response);
        free(response);
    }
}
