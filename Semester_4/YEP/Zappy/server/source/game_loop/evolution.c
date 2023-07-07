/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** evolution
*/

#include "zappy.h"

static evol_cond_t critere[] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1},
};

bool check_player(client_t *client, client_t *list)
{
    client_t *tmp = list;
    int nb = 0;
    for (; tmp != NULL; tmp = tmp->next_on_tile) {
        if (tmp == client) {
            nb++;
            continue;
        }
        if (tmp->player->level == client->player->level)
            nb++;
    }
    if (nb >= critere[client->player->level - 1].nbPlayer)
        return (true);
    return (false);
}

void remove_ressource(invent_t *inv, int level)
{
    inv->linemate -= critere[level].linemate;
    inv->deraumere -= critere[level].deraumere;
    inv->sibur -= critere[level].sibur;
    inv->mendiane -= critere[level].mendiane;
    inv->phiras -= critere[level].phiras;
    inv->thystame -= critere[level].thystame;
}

void evolution(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int x = client->player->x;
    int y = client->player->y;
    if (check_player(client, zap->map[y][x]->player)) {
        update_player_incan(client, zap->map[y][x]->player, 1, zap);
        int maxSize = snprintf(NULL, 0, "Current level: %d\n",
        client->player->level);
        char *str = alloca(sizeof(char) * (maxSize + 1));
        snprintf(str, maxSize + 1, "Current level: %d\n",
        client->player->level);
        update_wbuffer(client, str);
        end_incantation(zap, client, "true");
    } else {
        update_wbuffer(client, "ko\n");
        end_incantation(zap, client, "false");
    }
}
