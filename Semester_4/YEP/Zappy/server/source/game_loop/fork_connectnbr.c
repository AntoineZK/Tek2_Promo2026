/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** fork_connectnbr
*/

#include "zappy.h"

void fork_command(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int rTeam = get_nbr_client_in_team(zap->argv->teamNames, client->teamName);
    zap->argv->teamClientsNb[rTeam]++;
    eggs_t *egg = malloc(sizeof(eggs_t));
    egg->id = zap->idegg;
    egg->team_name = strdup(client->teamName);
    egg->x = client->player->x;
    egg->y = client->player->y;
    egg->next = NULL;
    if (zap->eggs == NULL)
        zap->eggs = egg;
    else {
        eggs_t *tmp = zap->eggs;
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = egg;
    }
    zap->idegg++;
    update_wbuffer(client, "ok\n");
    egg_laid(zap, client);
}

void connectnbr_command(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int rTeam = get_nbr_client_in_team(zap->argv->teamNames, client->teamName);
    int nbActTeam = zap->argv->teamClientsNb[rTeam];
    if (rTeam == -1)
        nbActTeam = -1;
    int maxSize = snprintf(NULL, 0, "%d\n", nbActTeam);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "%d\n", nbActTeam);
    update_wbuffer(client, str);
}
