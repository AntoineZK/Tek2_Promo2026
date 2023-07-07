/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** argv_struct
*/

#include "zappy.h"

argv_t *init_argv(void)
{
    argv_t *argv = malloc(sizeof(argv_t));

    argv->port = -1;
    argv->width = -1;
    argv->height = -1;
    argv->teamNames = NULL;
    argv->teamClientsNb = NULL;
    argv->maxClientNb = -1;
    argv->freq = 100;
    argv->isNcurses = false;
    return (argv);
}

argv_t *debug_argv(void)
{
    argv_t *argv = malloc(sizeof(argv_t));

    argv->port = 8080;
    argv->width = 10;
    argv->height = 10;
    argv->teamNames = malloc(sizeof(char *) * 2);
    argv->teamNames[0] = strdup("Team1");
    argv->teamNames[1] = NULL;
    argv->teamClientsNb = malloc(sizeof(int) * 2);
    argv->teamClientsNb[0] = 2;
    argv->teamClientsNb[1] = 2;
    argv->maxClientNb = 2;
    argv->freq = 50;
    argv->isNcurses = false;
    return (argv);
}

static bool check_argv_2(argv_t *argv)
{
    if (argv->teamNames == NULL) {
        printf("-n option must be set\n");
        return (false);
    }
    int teamNb = get_nbr_team(argv->teamNames);
    argv->teamClientsNb = malloc(sizeof(int) * (teamNb + 1));
    for (int i = 0; i < teamNb; i++)
        argv->teamClientsNb[i] = argv->maxClientNb;
    argv->teamClientsNb[teamNb] = -1;
    return (true);
}

bool check_argv(argv_t *argv)
{
    if (argv->width < 10 || argv->width > 30 || argv->height < 10
    || argv->height > 30) {
        printf("-x or -y option must be between 10 and 30\n");
        return (false);
    }
    if (argv->maxClientNb < 1) {
        printf("-c option must be greater than 0\n");
        return (false);
    }
    if (argv->freq < 1 || argv->freq > 10000) {
        printf("-f option must be between 1 and 1000\n");
        return (false);
    }
    if (argv->port < 1024 || argv->port > 65535) {
        printf("-p option must be between 1024 and 65535\n");
        return (false);
    }
    return (check_argv_2(argv));
}

void free_argv(argv_t *argv)
{
    if (argv->teamNames != NULL) {
        for (int i = 0; argv->teamNames[i]; i++)
            free(argv->teamNames[i]);
        free(argv->teamNames);
    }
    if (argv->teamClientsNb)
        free(argv->teamClientsNb);
    free(argv);
}
