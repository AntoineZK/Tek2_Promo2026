/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** user
*/

#include "server.h"

bool user_error(sockcli_t *actCli, char **args)
{
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) != 2) {
        update_wbuffer(actCli, "ERROR: Invalid number of arguments\n");
        return (true);
    }
    return (false);
}

void send_response(client_t *cli, sockcli_t *actCli)
{
    char *response = NULL;
    if (cli->is_connected == true) {
        response = gen_resp("USER", 3, cli->infos->uuid,
        cli->infos->username, "1");
    } else
        response = gen_resp("USER", 3, cli->infos->uuid,
        cli->infos->username, "0");
    update_wbuffer(actCli, response);
    free(response);
}

void user(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (user_error(actCli, args))
        return;
    for (client_t *cli = teams->ntw->allCli; cli != NULL; cli = cli->next) {
        if (strcmp(cli->infos->uuid, args[1]) == 0) {
            send_response(cli, actCli);
            return;
        }
    }
    char *response = gen_resp("ERROR4", 1, args[1]);
    update_wbuffer(actCli, response);
    free(response);
}
