/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** broadcast_test
*/

#include "zappy_criterion.h"

client_t *create_client_test(client_t *cli, int id, int x, int y)
{
    client_t *new = malloc(sizeof(client_t));
    new->id = id;
    new->wBuffer = NULL;
    new->wBuffLen = 0;
    new->isGraphical = false;
    new->player = init_player(x, y, 1);
    new->player->direction = 0;
    if (cli == NULL)
        return new;
    client_t *tmp = cli;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return (cli);
}

void test_brod(zappy_t *zap)
{
    printf("\033[1;32mCheck broadcast\033[0m\n");
    cr_assert_str_eq(zap->ntw->clients->next->wBuffer, "message 8, test\n");
    cr_assert_str_eq(zap->ntw->clients->next->next->wBuffer,
     "message 7, test\n");
    cr_assert_str_eq(zap->ntw->clients->next->next->next->wBuffer,
     "message 8, test\n");
    cr_assert_str_eq(zap->ntw->clients->next->next->next->next->wBuffer,
     "message 4, test\n");
    cr_assert_str_eq(zap->ntw->clients->next->next->next->next->next->wBuffer,
     "message 3, test\n");
    cr_assert_str_eq(
        zap->ntw->clients->next->next->next->next->next->next->wBuffer,
     "message 2, test\n");
    cr_assert_str_eq(
        zap->ntw->clients->next->next->next->next->next->next->next->wBuffer,
     "message 5, test\n");
}

Test(broadcast, test_broadcast)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = create_client_test(NULL, 1, 5, 5);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 2, 9, 9);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 3, 5, 6);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 4, 6, 6);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 5, 4, 4);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 6, 5, 4);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 7, 6, 4);
    zap->ntw->clients = create_client_test(zap->ntw->clients, 8, 4, 5);
    char **cmd = stwa("broadcast test\n", " \n");
    broadcast_to_all(zap, zap->ntw->clients, cmd);
    test_brod(zap);
}
