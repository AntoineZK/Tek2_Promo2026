/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** evolution_check
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

static int level_good(zappy_t *zap, client_t *tmp, int nb, int mod)
{
    nb++;
    if (mod == 1) {
        tmp->player->level++;
        tmp->player->isEvolve = false;
        int maxSize = snprintf(NULL, 0, "Current level: %d\n",
        tmp->player->level);
        char *str = alloca(sizeof(char) * (maxSize + 1));
        snprintf(str, maxSize + 1, "Current level: %d\n",
        tmp->player->level);
        update_wbuffer(tmp, str);
    } else {
        tmp->player->nbCycle += 305;
        tmp->player->isEvolve = true;
        update_wbuffer(tmp, "Elevation underway\n");
        start_incantation_player(zap, tmp);
    }
    return nb;
}

void update_player_incan(client_t *cli, client_t *list, int mod, zappy_t *zap)
{
    int nb = 1;
    int level = cli->player->level - 1;
    if (mod != 1)
        start_incantation_player(zap, cli);
    client_t *tmp = list;
    for (; nb < critere[level].nbPlayer; tmp = tmp->next_on_tile) {
        if (tmp->player->level == cli->player->level && tmp != cli)
            nb = level_good(zap, tmp, nb, mod);
    }
    if (mod == 1)
        cli->player->level++;
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next)
        if (allCli->isGraphical == true)
            update_wbuffer(allCli, "\n");
}

static bool check_cond(int level, zappy_t *zap, int x, int y)
{
    invent_t *inv = zap->map[y][x]->item;
    if (inv->linemate >= critere[level].linemate && inv->deraumere >=
    critere[level].deraumere && inv->sibur >= critere[level].sibur &&
    inv->mendiane >= critere[level].mendiane && inv->phiras >=
    critere[level].phiras && inv->thystame >= critere[level].thystame)
        return (true);
    return (false);
}

bool check_evolution(zappy_t *zap, client_t *client)
{
    int x = client->player->x;
    int y = client->player->y;
    if (check_cond(client->player->level - 1, zap, x, y) &&
    check_player(client, zap->map[y][x]->player) && !client->player->isEvolve) {
        remove_ressource(zap->map[y][x]->item, client->player->level - 1);
        int maxSize = snprintf(NULL, 0, "pic %d %d %d", client->player->x,
        client->player->y, client->player->level);
        char *str = alloca(sizeof(char) * (maxSize + 1));
        snprintf(str, maxSize + 1, "pic %d %d %d", client->player->x,
        client->player->y, client->player->level);
        for (client_t *Clis = zap->ntw->clients; Clis; Clis = Clis->next)
            Clis->isGraphical == true ? update_wbuffer(Clis, str) : 0;
        update_player_incan(client, zap->map[y][x]->player, 0, zap);
        update_wbuffer(client, "Elevation underway\n");
        return (true);
    }
    update_wbuffer(client, "ko\n");
    return (false);
}
