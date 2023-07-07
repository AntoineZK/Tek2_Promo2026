/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** main_test
*/

#include "zappy_criterion.h"

Test(commands_rotation, check_turn_right)
{
    printf("\033[1;32mCheck basic turn right\033[0m\n");
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->height = 10;
    zap->argv->width = 10;
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = NULL;
    client_t *cli = alloca(sizeof(client_t));
    cli->player = init_player(0, 0, 0);
    cli->wBuffLen = 0;
    cli->wBuffer = NULL;
    cli->isGraphical = false;
    turn_player_right(zap, cli, NULL);
    cr_assert_eq(1, cli->player->direction);
    turn_player_right(zap, cli, NULL);
    cr_assert_eq(2, cli->player->direction);
    turn_player_right(zap, cli, NULL);
    cr_assert_eq(3, cli->player->direction);
    turn_player_right(zap, cli, NULL);
    cr_assert_eq(0, cli->player->direction);
}

Test(commands_rotation, check_turn_left)
{
    printf("\033[1;32mCheck basic turn left\033[0m\n");
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->height = 10;
    zap->argv->width = 10;
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = NULL;
    client_t *cli = alloca(sizeof(client_t));
    cli->player = init_player(0, 0, 0);
    cli->wBuffLen = 0;
    cli->wBuffer = NULL;
    cli->isGraphical = false;
    turn_player_left(zap, cli, NULL);
    cr_assert_eq(3, cli->player->direction);
    turn_player_left(zap, cli, NULL);
    cr_assert_eq(2, cli->player->direction);
    turn_player_left(zap, cli, NULL);
    cr_assert_eq(1, cli->player->direction);
    turn_player_left(zap, cli, NULL);
    cr_assert_eq(0, cli->player->direction);
}
