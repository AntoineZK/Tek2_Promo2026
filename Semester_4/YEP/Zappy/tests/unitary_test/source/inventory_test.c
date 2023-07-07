/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** inventory
*/

#include "zappy_criterion.h"

Test(inventory, check_inventory_command)
{
    printf("\033[1;32mCheck inventory command\033[0m\n");
    client_t *client = alloca(sizeof(client_t));
    client->player = alloca(sizeof(player_t));
    client->player->inventory = alloca(sizeof(invent_t));
    client->player->inventory->food = 1;
    client->player->inventory->linemate = 2;
    client->player->inventory->deraumere = 3;
    client->player->inventory->sibur = 4;
    client->player->inventory->mendiane = 5;
    client->player->inventory->phiras = 6;
    client->player->inventory->thystame = 7;
    client->wBuffer = NULL;
    client->wBuffLen = 0;
    char *exp = "[food 1, linemate 2, deraumere 3, sibur 4, mendiane 5, phiras 6, thystame 7]\n";
    inventory_command(NULL, client, NULL);
    cr_assert_eq(strcmp(exp, client->wBuffer), 0);
}

client_t *decal_wbuffer(client_t *cli)
{
    cli->wBuffLen -= cli->wBuffLen;
    memmove(cli->wBuffer, cli->wBuffer + cli->wBuffLen, cli->wBuffLen);
    cli->wBuffer = realloc(cli->wBuffer, cli->wBuffLen);
    return cli;
}

tile_t ***generate_test_map(tile_t ***map, int x, int y)
{
    map = init_map(x, y);
    map[4][6]->item->deraumere = 1;
    map[5][6]->item->food = 2;
    map[6][6]->item->mendiane = 2;
    map[4][4]->item->linemate = 1;
    map[5][4]->item->phiras = 2;
    map[6][4]->item->sibur = 2;
    map[4][5]->item->thystame = 1;
    map[6][5]->item->deraumere = 1;
    map[5][5]->item->food = 2;
    return map;
}

Test(look, check_look_command)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->width = 10;
    zap->argv->height = 10;
    zap->map = generate_test_map(zap->map, 10, 10);
    client_t *cli = alloca(sizeof(client_t));
    cli->wBuffer = NULL;
    cli->wBuffLen = 0;
    cli->player = alloca(sizeof(player_t));
    cli->player->x = 5;
    cli->player->y = 5;
    cli->player->direction = 0;
    cli->player->level = 1;
    char allResp[][75] = {"[food food,deraumere,food food,mendiane mendiane]\n",
    "[food food,mendiane mendiane,deraumere,sibur sibur]\n",
    "[food food,sibur sibur,phiras phiras,linemate]\n",
    "[food food,linemate,thystame,deraumere]\n"};

    for (int i = 0; i < 4; i++) {
        commande_look(zap, cli, NULL);
        cr_assert_eq(strcmp(allResp[i], cli->wBuffer), 0);
        cli = decal_wbuffer(cli);
        cli->player->direction++;
    }
}
