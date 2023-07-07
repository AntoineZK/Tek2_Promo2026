/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** take_set_test
*/

#include "zappy_criterion.h"

client_t *client_test(void)
{
    client_t *cli = malloc(sizeof(client_t));
    cli->player = malloc(sizeof(player_t));
    cli->player->x = 5;
    cli->player->y = 5;
    cli->isGraphical = false;
    cli->player->inventory = malloc(sizeof(invent_t));
    cli->player->inventory->food = 3;
    cli->player->inventory->linemate = 2;
    cli->player->inventory->deraumere = 1;
    cli->player->inventory->sibur = 1;
    cli->player->inventory->mendiane = 1;
    cli->player->inventory->phiras = 1;
    cli->player->inventory->thystame = 1;
    cli->wBuffer = NULL;
    cli->wBuffLen = 0;
    cli->next = NULL;
    cli->id = 1;
    return (cli);
}

tile_t ***generate_test_map2(tile_t ***map, int x, int y)
{
    map = init_map(x, y);
    map[5][5]->item->food = 2;
    map[5][5]->item->linemate = 1;
    map[5][5]->item->deraumere = 3;
    map[5][5]->item->sibur = 1;
    map[5][5]->item->mendiane = 7;
    map[5][5]->item->phiras = 4;
    map[5][5]->item->thystame = 8;
    return map;
}

Test(take, check_take_command)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->map = generate_test_map2(zap->map, 10, 10);
    zap->ressources = init_ressource(10, 10);
    client_t *cli = client_test();
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = cli;
    char **tab = malloc(sizeof(char *) * 2);
    tab[0] = strdup("take");
    tab[1] = strdup("food");
    printf("\033[1;32mTest take food\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->food, 4);
    cr_assert_eq(zap->map[5][5]->item->food, 1);
    tab[1] = strdup("linemate");
    printf("\033[1;32mTest take linemate\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->linemate, 3);
    cr_assert_eq(zap->map[5][5]->item->linemate, 0);
    tab[1] = strdup("deraumere");
    printf("\033[1;32mTest take deraumere\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->deraumere, 2);
    cr_assert_eq(zap->map[5][5]->item->deraumere, 2);
    tab[1] = strdup("sibur");
    printf("\033[1;32mTest take sibur\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->sibur, 2);
    cr_assert_eq(zap->map[5][5]->item->sibur, 0);
    tab[1] = strdup("mendiane");
    printf("\033[1;32mTest take mendiane\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->mendiane, 2);
    cr_assert_eq(zap->map[5][5]->item->mendiane, 6);
    tab[1] = strdup("phiras");
    printf("\033[1;32mTest take phiras\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->phiras, 2);
    cr_assert_eq(zap->map[5][5]->item->phiras, 3);
    tab[1] = strdup("thystame");
    printf("\033[1;32mTest take thystame\033[0m\n");
    take_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->thystame, 2);
    cr_assert_eq(zap->map[5][5]->item->thystame, 7);
}

Test(set, test_set_command)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->map = generate_test_map2(zap->map, 10, 10);
    zap->ressources = init_ressource(10, 10);
    client_t *cli = client_test();
    zap->ntw = alloca(sizeof(network_t));
    zap->ntw->clients = cli;
    char **tab = malloc(sizeof(char *) * 2);
    tab[0] = strdup("take");
    tab[1] = strdup("food");
    printf("\033[1;32mTest set food\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->food, 2);
    cr_assert_eq(zap->map[5][5]->item->food, 3);
    tab[1] = strdup("linemate");
    printf("\033[1;32mTest set linemate\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->linemate, 1);
    cr_assert_eq(zap->map[5][5]->item->linemate, 2);
    tab[1] = strdup("deraumere");
    printf("\033[1;32mTest set deraumere\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->deraumere, 0);
    cr_assert_eq(zap->map[5][5]->item->deraumere, 4);
    tab[1] = strdup("sibur");
    printf("\033[1;32mTest set sibur\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->sibur, 0);
    cr_assert_eq(zap->map[5][5]->item->sibur, 2);
    tab[1] = strdup("mendiane");
    printf("\033[1;32mTest set mendiane\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->mendiane, 0);
    cr_assert_eq(zap->map[5][5]->item->mendiane, 8);
    tab[1] = strdup("phiras");
    printf("\033[1;32mTest set phiras\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->phiras, 0);
    cr_assert_eq(zap->map[5][5]->item->phiras, 5);
    tab[1] = strdup("thystame");
    printf("\033[1;32mTest set thystame\033[0m\n");
    set_object(zap, cli, tab);
    cr_assert_eq(cli->player->inventory->thystame, 0);
    cr_assert_eq(zap->map[5][5]->item->thystame, 9);
}
