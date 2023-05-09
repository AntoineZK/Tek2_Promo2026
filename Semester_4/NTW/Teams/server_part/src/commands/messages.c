/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** messages
*/

#include "server.h"

bool message_error(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (actCli->client == NULL) {
        update_wbuffer(actCli, "ERROR5\n");
        return (true);
    }
    if (len_darray(args) != 2) {
        update_wbuffer(actCli, "ERROR: Invalid arguments\n");
        return (true);
    }
    if (client_exist(teams->ntw->allCli, args[1]) == false) {
        char *res = gen_resp("ERROR4", 1, args[1]);
        update_wbuffer(actCli, res);
        free(res);
        return (true);
    }
    return (false);
}

void check_sender_receiver(message_t *tmp, sockcli_t *actCli, char *uuid1,
char *uuid2)
{
    if (strcmp(tmp->sender_uuid, uuid1) == 0 &&
        strcmp(tmp->receiver_uuid, uuid2) == 0) {
        char *time = time_to_str(tmp->time);
        char *res = gen_resp("MESSAGES", 3, uuid1, time, tmp->body);
        update_wbuffer(actCli, res);
        free(res);
        free(time);
    } else if (strcmp(tmp->sender_uuid, uuid2) == 0 &&
    strcmp(tmp->receiver_uuid, uuid1) == 0) {
        char *time = time_to_str(tmp->time);
        char *res = gen_resp("MESSAGES", 3, uuid2, time, tmp->body);
        update_wbuffer(actCli, res);
        free(res);
        free(time);
    }
}

void list_message(teams_t *teams, sockcli_t *actCli, char **args)
{
    if (message_error(teams, actCli, args))
        return;
    message_t *tmp = teams->ntw->allMsg;
    char *uuid1 = args[1];
    char *uuid2 = actCli->client->infos->uuid;
    for (; tmp != NULL; tmp = tmp->next) {
        check_sender_receiver(tmp, actCli, uuid1, uuid2);
    }
}
