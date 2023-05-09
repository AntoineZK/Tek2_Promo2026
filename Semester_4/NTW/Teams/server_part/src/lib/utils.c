/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** uuid
*/

#include "server.h"

char *generate_uuid(void)
{
    uuid_t uuid;
    char *str = malloc(sizeof(char) * 37);

    uuid_generate_random(uuid);
    uuid_unparse(uuid, str);
    return str;
}

bool find_uuid(sockcli_t *client, char *uuid)
{
    for (sockcli_t *tmp = client; tmp; tmp = tmp->next) {
        if (tmp->client != NULL && strcmp(tmp->client->infos->uuid, uuid) == 0)
            return true;
    }
    return false;
}

char *time_to_str(time_t initialTime)
{
    struct tm *timeinfo;
    char *str = malloc(sizeof(char) * 20);

    timeinfo = localtime(&initialTime);
    strftime(str, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return str;
}

char *gen_resp(char *func, int nbArg, ...)
{
    va_list argList;
    char *resp = malloc(sizeof(char));

    resp[0] = '\0';
    strcat_dynamic(&resp, func);
    strcat_dynamic(&resp, " ");
    va_start(argList, nbArg);
    for (int i = 0; i < nbArg; i++) {
        char *dquote = add_doublequote(va_arg(argList, char *));
        strcat_dynamic(&resp, dquote);
        free(dquote);
        if (i != nbArg - 1)
            strcat_dynamic(&resp, " ");
    }
    va_end(argList);
    strcat_dynamic(&resp, "\n");
    return resp;
}
