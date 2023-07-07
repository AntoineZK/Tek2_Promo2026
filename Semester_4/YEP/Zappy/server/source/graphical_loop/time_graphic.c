/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** time_graphic
*/

#include "zappy.h"

void time_request(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int maxSize = snprintf(NULL, 0, "sgt %d\n", zap->argv->freq);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "sgt %d\n", zap->argv->freq);
    update_wbuffer(client, str);
}

void time_modification(zappy_t *zap, client_t *client, char **cmd)
{
    zap->argv->freq = atoi(cmd[1]);
    int maxSize = snprintf(NULL, 0, "sst %d\n", atoi(cmd[1]));
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "sst %d\n", atoi(cmd[1]));
    update_wbuffer(client, str);
}
