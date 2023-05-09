/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** send
*/

#include "server.h"

void strcat_dynamic(char **dest, char *src)
{
    char *str = malloc(sizeof(char) * (strlen(*dest) + strlen(src) + 1));
    int i = 0;

    for (; (*dest)[i] != '\0'; i++)
        str[i] = (*dest)[i];
    for (; src[i - strlen(*dest)] != '\0'; i++)
        str[i] = src[i - strlen(*dest)];
    str[i] = '\0';
    free(*dest);
    (*dest) = str;
}

bool send_error(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) != 3) {
        update_wbuffer(actCli, "ERROR: Invalid number of arguments\n");
        return (true);
    }
    if (find_uuid(teams->ntw->cliCon, args[1]) == false) {
        char *response = gen_resp("ERROR4", 1, args[1]);
        update_wbuffer(actCli, response);
        free(response);
        return (true);
    }
    return (false);
}

void send_to_destclient(teams_t *teams, sockcli_t *actCli, char **args)
{
    char *response = gen_resp("SEND", 2, actCli->client->infos->uuid, args[2]);
    for (sockcli_t *cli = teams->ntw->cliCon; cli != NULL; cli = cli->next) {
        if (cli->client != NULL &&
        strcmp(cli->client->infos->uuid, args[1]) == 0)
            update_wbuffer(cli, response);
    }
    free(response);
}

void send_message(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (send_error(teams, actCli, args))
        return;
    server_event_private_message_sended(actCli->client->infos->uuid,
    args[1], args[2]);
    time_t t_mp;
    time(&t_mp);
    message_t *mp = gen_mp(args[2], actCli->client->infos->uuid, args[1],
    t_mp);
    teams->ntw->allMsg = add_message(teams->ntw->allMsg, mp);
    send_to_destclient(teams, actCli, args);
}
