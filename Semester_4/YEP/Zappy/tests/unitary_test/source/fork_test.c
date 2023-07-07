/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** fork_test
*/

#include "zappy_criterion.h"

zappy_t *create_zappy_test(void)
{
    zappy_t *zap = malloc(sizeof(zappy_t));
    zap->argv = malloc(sizeof(argv_t));
    zap->argv->teamNames = stwa("team1 team2", " ");
    zap->argv->teamClientsNb = malloc(sizeof(int) * 2);
    zap->argv->teamClientsNb[0] = 1;
    zap->argv->teamClientsNb[1] = 2;
    zap->eggs = NULL;
    zap->idegg = 0;
    zap->ntw = malloc(sizeof(network_t));
    client_t *cli = malloc(sizeof(client_t));
    cli->wBuffer = NULL;
    cli->wBuffLen = 0;
    cli->player = malloc(sizeof(player_t));
    cli->player->x = 8;
    cli->player->y = 7;
    cli->teamName = strdup("team1");
    cli->id = 1;
    zap->ntw->clients = cli;
    return zap;
}

Test(fork, test_fork)
{
    zappy_t *zap = create_zappy_test();

    fork_command(zap, zap->ntw->clients, NULL);
    printf("\033[1;32mCheck fork 1\033[0m\n");
    cr_assert_eq(zap->idegg, 1);
    cr_assert_eq(zap->eggs->id, 0);
    cr_assert_str_eq(zap->eggs->team_name, "team1");
    cr_assert_eq(zap->eggs->x, 8);
    cr_assert_eq(zap->eggs->y, 7);
    cr_assert_eq(zap->eggs->next, NULL);
    cr_assert_eq(zap->argv->teamClientsNb[0], 2);
    cr_assert_eq(zap->argv->teamClientsNb[1], 2);

    zap->ntw->clients->teamName = strdup("team2");
    fork_command(zap, zap->ntw->clients, NULL);
    printf("\033[1;32mCheck fork 2\033[0m\n");
    cr_assert_eq(zap->idegg, 2);
    cr_assert_eq(zap->eggs->next->id, 1);
    cr_assert_str_eq(zap->eggs->next->team_name, "team2");
    cr_assert_eq(zap->eggs->next->x, 8);
    cr_assert_eq(zap->eggs->next->y, 7);
    cr_assert_eq(zap->eggs->next->next, NULL);
    cr_assert_eq(zap->argv->teamClientsNb[0], 2);
    cr_assert_eq(zap->argv->teamClientsNb[1], 3);
}