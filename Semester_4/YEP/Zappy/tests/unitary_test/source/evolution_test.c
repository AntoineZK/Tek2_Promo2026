/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** evolution
*/

#include "zappy_criterion.h"

void test_evolution(zappy_t * zap)
{
    printf("\033[1;32mCheck evolution\033[0m\n");
    cr_assert(check_evolution(zap, zap->ntw->clients));
    cr_assert_not(check_evolution(zap, zap->ntw->clients->next->next));
    zap->ntw->clients->next->player->level = 3;
    cr_assert(check_evolution(zap, zap->ntw->clients->next->next));
    evolution(zap, zap->ntw->clients, NULL);
    cr_assert_not(check_evolution(zap, zap->ntw->clients));
}

Test(evolution, test_evolution)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->map = init_map(zap->argv->width, zap->argv->height);
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = create_client_test(NULL, 1, 5, 5);
    place_player(zap->map, zap->ntw->clients);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 2, 6, 6);
    place_player(zap->map, zap->ntw->clients->next);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 3, 6, 6);
    place_player(zap->map, zap->ntw->clients->next->next);
    zap->ntw->clients->next->next->player->level = 3;
    zap->map[5][5]->item->linemate = 2;
    zap->map[6][6]->item->linemate = 2;
    zap->map[6][6]->item->phiras = 2;
    zap->map[6][6]->item->sibur = 1;
    test_evolution(zap);
}