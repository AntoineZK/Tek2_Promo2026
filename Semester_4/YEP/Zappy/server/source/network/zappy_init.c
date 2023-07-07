/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** network_init
*/

#include "zappy.h"

zappy_t *init_zappy(argv_t *argv)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    zappy->argv = argv;
    zappy->ntw = malloc(sizeof(network_t));
    zappy->ntw->sock = create_server(argv->port);
    zappy->ntw->clients = NULL;
    zappy->ntw->maxFD = zappy->ntw->sock;
    zappy->ntw->nbRemove = 0;
    zappy->ntw->addrlen = sizeof(zappy->ntw->addr);
    zappy->map = init_map(argv->width, argv->height);
    zappy->ressources = init_ressource(argv->width, argv->height);
    zappy->eggs = NULL;
    zappy->idegg = 0;
    zappy->cycletime = 20;
    file_map_ressources(zappy->map, zappy->ressources);
    zappy->ncurses = zappy->argv->isNcurses ? init_ncurses() : NULL;
    return (zappy);
}
