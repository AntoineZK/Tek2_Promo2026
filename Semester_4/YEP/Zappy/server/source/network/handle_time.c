/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** handle_time
*/

#include "zappy.h"

static void remove_food(zappy_t *zap, client_t *tmp)
{
    tmp->player->inventory->food--;
    if (tmp->player->inventory->food < 0) {
        update_wbuffer(tmp, "dead\n");
        send_player_death(zap, tmp);
    } else {
        tmp->player->time_food = 126;
    }
}

static void update_client_time(zappy_t *zap)
{
    for (client_t *cli = zap->ntw->clients; cli; cli = cli->next) {
        if (cli->player != NULL) {
            cli->player->nbCycle--;
            cli->player->time_food--;
            cli->player->time_food == 0 ? remove_food(zap, cli) : 0;
        }
    }
    zap->cycletime--;
    if (zap->cycletime == 0) {
        zap->cycletime = 20;
        refile_map_ressources(zap->map, zap->ressources);
    }
}

struct timeval handle_time(zappy_t *zap, struct timeval tv)
{
    if (tv.tv_usec == 0) {
        tv.tv_usec = 1000000 / zap->argv->freq;
        update_client_time(zap);
    }
    return (tv);
}
