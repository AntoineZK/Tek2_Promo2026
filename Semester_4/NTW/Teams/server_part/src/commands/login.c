/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** login
*/

#include "server.h"

bool login_error(sockcli_t *actClient, char **args)
{
    if (len_darray(args) != 2) {
        update_wbuffer(actClient, "ERROR: Invalid arguments\n");
        return (true);
    }
    if (actClient->client != NULL) {
        update_wbuffer(actClient, "ERROR: Already logged in\n");
        return (true);
    }
    return (false);
}

void update_client_exist(teams_t *teams, sockcli_t *actClient)
{
    if (actClient->client == NULL)
        return;
    char *response = gen_resp("LOGIN", 2,
    actClient->client->infos->uuid, actClient->client->infos->username);
    for (sockcli_t *cli = teams->ntw->cliCon; cli != NULL; cli = cli->next) {
        if (cli->client != NULL)
            update_wbuffer(cli, response);
    }
    free(response);
}

void login(teams_t *teams, sockcli_t *actClient, char **args)
{
    if (login_error(actClient, args) == true)
        return;
    for (client_t *tmp = teams->ntw->allCli; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->infos->username, args[1]) == 0) {
            tmp->is_connected = true;
            actClient->client = duplicate_client(tmp);
            server_event_user_logged_in(actClient->client->infos->uuid);
        }
    }
    if (actClient->client == NULL) {
        char *uuid_str = generate_uuid();
        server_event_user_created(uuid_str, args[1]);
        teams->ntw->allCli = add_client(teams->ntw->allCli, args[1], uuid_str);
        client_t *tmp = get_last_client(teams->ntw->allCli);
        tmp->is_connected = true;
        actClient->client = duplicate_client(tmp);
        server_event_user_logged_in(uuid_str);
        free(uuid_str);
    }
    update_client_exist(teams, actClient);
}
