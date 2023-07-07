/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** player_graphic
*/

#include "zappy.h"

void send_player_level(zappy_t *zap, client_t *client, char **cmd)
{
    client_t *tmp = zap->ntw->clients;
    for (; tmp; tmp = tmp->next)
        if (tmp->player != NULL && tmp->id == atoi(cmd[1]))
            break;
    if (tmp == NULL) {
        update_wbuffer(client, "sbp\n");
        return;
    }
    int maxSize = snprintf(NULL, 0, "plv %d %d\n", tmp->id,
    tmp->player->level);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "plv %d %d\n", tmp->id,
    tmp->player->level);
    update_wbuffer(client, str);
}

void send_player_inventory(zappy_t *zap, client_t *client, char **cmd)
{
    client_t *tmp = zap->ntw->clients;
    for (; tmp; tmp = tmp->next)
        if (tmp->player != NULL && tmp->id == atoi(cmd[1]))
            break;
    if (tmp == NULL) {
        update_wbuffer(client, "sbp\n");
        return;
    }
    invent_t *inv = tmp->player->inventory;
    int maxSize = snprintf(NULL, 0, "pin %d %d %d %d %d %d %d %d %d %d\n",
    tmp->id, tmp->player->x, tmp->player->y, inv->food, inv->linemate,
    inv->deraumere, inv->sibur, inv->mendiane, inv->phiras, inv->thystame);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pin %d %d %d %d %d %d %d %d %d %d\n",
    tmp->id, tmp->player->x, tmp->player->y, inv->food, inv->linemate,
    inv->deraumere, inv->sibur, inv->mendiane, inv->phiras, inv->thystame);
    update_wbuffer(client, str);
}

void send_player_position(zappy_t *zap, client_t *client, char **cmd)
{
    client_t *choosedCli = zap->ntw->clients;
    for (; choosedCli; choosedCli = choosedCli->next)
        if (choosedCli->player != NULL && choosedCli->id == atoi(cmd[1]))
            break;
    if (choosedCli == NULL) {
        update_wbuffer(client, "sbp\n");
        return;
    }
    int direction = choosedCli->player->direction;
    direction += 2;
    direction = direction > 4 ? direction - 4 : direction;
    int maxSize = snprintf(NULL, 0, "ppo %d %d %d %d\n", choosedCli->id,
    choosedCli->player->x, choosedCli->player->y, direction);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "ppo %d %d %d %d\n", choosedCli->id,
    choosedCli->player->x, choosedCli->player->y, direction);
    update_wbuffer(client, str);
}

char *send_player_new_co(client_t *client)
{
    int direction = client->player->direction;
    direction += 2;
    if (direction > 4)
        direction -= 4;
    int maxSize = snprintf(NULL, 0, "pnw %d %d %d %d %d %s\n", client->id,
    client->player->x, client->player->y, direction, client->player->level,
    client->teamName);
    char *str = malloc(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pnw %d %d %d %d %d %s\n", client->id,
    client->player->x, client->player->y, direction, client->player->level,
    client->teamName);
    return (str);
}

void send_player_expulsion(zappy_t *zap, client_t *client)
{
    int maxSize = snprintf(NULL, 0, "pex %d\n", client->id);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "pex %d\n", client->id);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next) {
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, str);
    }
}
