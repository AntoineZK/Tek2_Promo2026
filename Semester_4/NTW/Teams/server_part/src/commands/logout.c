/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** disconnect
*/

#include "server.h"

bool logout_error(sockcli_t *actCli)
{
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return (true);
    }
    return (false);
}

int nb_sock_list(teams_t *teams, char *username)
{
    int nb = 0;

    for (sockcli_t *cli = teams->ntw->cliCon; cli != NULL; cli = cli->next) {
        if (cli->client != NULL &&
        strcmp(cli->client->infos->username, username) == 0)
            nb++;
    }
    return (nb);
}

void set_client_to_false(teams_t *teams, sockcli_t *actCli)
{
    for (client_t *tmp = teams->ntw->allCli; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->infos->username, actCli->client->infos->username) == 0)
            tmp->is_connected = false;
    }
}

void logout(teams_t *teams, sockcli_t *actCli, char **args)
{
    (void)teams;
    (void)args;
    if (logout_error(actCli))
        return;
    server_event_user_logged_out(actCli->client->infos->uuid);
    char *response = gen_resp("LOGOUT", 2, actCli->client->infos->uuid,
    actCli->client->infos->username);
    for (sockcli_t *cli = teams->ntw->cliCon; cli != NULL; cli = cli->next) {
        if (cli->client != NULL)
            update_wbuffer(cli, response);
    }
    free(response);
    if (nb_sock_list(teams, actCli->client->infos->username) == 1) {
        set_client_to_false(teams, actCli);
    }
    actCli->client = free_client(actCli->client);
}
