/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** player2_graphic
*/

#include "zappy.h"

void send_player_death(zappy_t *zap, client_t *client)
{
    int maxSize = snprintf(NULL, 0, "pdi %d\n", client->id);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pdi %d\n", client->id);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}

char *send_player_position2(client_t *client)
{
    int direction = client->player->direction;
    direction += 2;
    direction = direction > 4 ? direction - 4 : direction;
    int maxSize = snprintf(NULL, 0, "ppo %d %d %d %d\n", client->id,
    client->player->x, client->player->y, direction);
    char *str = malloc(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "ppo %d %d %d %d\n", client->id,
    client->player->x, client->player->y, direction);
    return (str);
}
