/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** team_graphic
*/

#include "zappy.h"

void all_team_name(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int maxNbTeam = get_nbr_team(zap->argv->teamNames);
    for (int i = 0; i < maxNbTeam; i++) {
        int maxSize = snprintf(NULL, 0, "tna %s\n", zap->argv->teamNames[i]);
        char *str = alloca(sizeof(char) * (maxSize + 1));

        snprintf(str, maxSize + 1, "tna %s\n", zap->argv->teamNames[i]);
        update_wbuffer(client, str);
    }
}

void broadcast_to_gui(zappy_t *zap, client_t *client, char *cmd)
{
    int maxSize = snprintf(NULL, 0, "pbc %d %s\n", client->id, cmd);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pbc %d %s\n", client->id, cmd);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
