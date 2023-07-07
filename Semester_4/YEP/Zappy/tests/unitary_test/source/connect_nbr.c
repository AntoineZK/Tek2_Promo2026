/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** connect_nbr
*/

#include "zappy_criterion.h"

void testConnectNbr(zappy_t *zap, client_t *cli, char *tN, char *expOut)
{
    cli->teamName = strdup(tN);
    printf("\033[1;32mCheck connect_nbr %s\033[0m\n", tN);
    connectnbr_command(zap, cli, NULL);
    cr_assert_str_eq(cli->wBuffer, expOut);
    free(cli->teamName);
    cli = decal_wbuffer(cli);
}

Test(connect_nbr, test_connect_nbr_value)
{
    zappy_t *zap = alloca(sizeof(zappy_t));
    zap->argv = alloca(sizeof(argv_t));
    zap->argv->teamNames = stwa("team1 team2", " ");
    zap->argv->teamClientsNb = alloca(sizeof(int) * 2);
    zap->argv->teamClientsNb[0] = 1;
    zap->argv->teamClientsNb[1] = 2;

    client_t *cli = alloca(sizeof(client_t));
    cli->wBuffer = NULL;
    cli->wBuffLen = 0;

    testConnectNbr(zap, cli, "team1", "1\n");
    testConnectNbr(zap, cli, "team2", "2\n");
    testConnectNbr(zap, cli, "team3", "-1\n");
}
