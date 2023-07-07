/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** eject_test
*/

#include "zappy_criterion.h"

void test_eject(zappy_t *zap)
{
    printf("\033[1;32mCheck eject\033[0m\n");
    cr_assert_eq(zap->ntw->clients->player->x, 5);
    cr_assert_eq(zap->ntw->clients->player->y, 5);
    cr_assert_eq(zap->ntw->clients->next->player->x, 6);
    cr_assert_eq(zap->ntw->clients->next->player->y, 5);
    cr_assert_eq(zap->ntw->clients->next->next->player->x, 6);
    cr_assert_eq(zap->ntw->clients->next->next->player->y, 5);
    cr_assert_eq(zap->ntw->clients->next->next->next->player->x, 2);
    cr_assert_eq(zap->ntw->clients->next->next->next->player->y, 7);
}

Test(eject, test_eject)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->map = init_map(zap->argv->width, zap->argv->height);
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = create_client_test(NULL, 1, 5, 5);
    place_player(zap->map, zap->ntw->clients);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 2, 5, 5);
    place_player(zap->map, zap->ntw->clients->next);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 3, 5, 5);
    place_player(zap->map, zap->ntw->clients->next->next);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 4, 2, 7);
    place_player(zap->map, zap->ntw->clients->next->next->next);
    commande_eject(zap, zap->ntw->clients, NULL);
    test_eject(zap);
}
