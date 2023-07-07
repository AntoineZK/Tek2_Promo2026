/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** forward
*/

#include "zappy_criterion.h"

void test_move(int x, int y, int direction, int exp_x, int exp_y)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->height = 10;
    zap->argv->width = 10;
    client_t *cli = alloca(sizeof(client_t));
    cli->player = init_player(x, y, direction);
    switch (direction) {
        case 0:
            move_right(zap, cli);
            cr_assert_eq(exp_x, cli->player->x);
            break;
        case 1:
            move_down(zap, cli);
            cr_assert_eq(exp_y, cli->player->y);
            break;
        case 2:
            move_left(zap, cli);
            cr_assert_eq(exp_x, cli->player->x);
            break;
        case 3:
            move_up(zap, cli);
            cr_assert_eq(exp_y, cli->player->y);
            break;
    }
}

Test(commands_forward, check_forward_to_right)
{
    printf("\033[1;32mCheck basic forward to right\033[0m\n");
    test_move(8, 8, 0, 9, 8);
    printf("\033[1;32mCheck hard forward to right\033[0m\n");
    test_move(0, 8, 0, 1, 8);
}

Test(commands_forward, check_forward_to_down)
{
    printf("\033[1;32mCheck basic forward to down\033[0m\n");
    test_move(8, 8, 1, 8, 9);
    printf("\033[1;32mCheck hard forward to down\033[0m\n");
    test_move(8, 0, 1, 8, 1);
}

Test(commands_forward, check_forward_to_left)
{
    printf("\033[1;32mCheck basic forward to left\033[0m\n");
    test_move(1, 1, 2, 0, 1);
    printf("\033[1;32mCheck hard forward to left\033[0m\n");
    test_move(9, 1, 2, 8, 1);
}

Test(commands_forward, check_forward_to_up)
{
    printf("\033[1;32mCheck basic forward to up\033[0m\n");
    test_move(1, 1, 3, 1, 0);
    printf("\033[1;32mCheck hard forward to up\033[0m\n");
    test_move(1, 9, 3, 1, 8);
}
