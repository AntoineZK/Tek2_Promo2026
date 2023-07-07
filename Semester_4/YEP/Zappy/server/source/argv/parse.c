/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** parse1
*/

#include "zappy.h"

static bool is_number(char *str)
{
    if (str == NULL)
        return (false);
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return (false);
    return (true);
}

static void argv_handler_int(int ac, char **av, int i, argv_t *argv)
{
    if (i + 1 <= ac && is_number(av[i + 1])) {
        if (strcmp(av[i], "-p") == 0)
            argv->port = atoi(av[i + 1]);
        if (strcmp(av[i], "-x") == 0)
            argv->width = atoi(av[i + 1]);
        if (strcmp(av[i], "-y") == 0)
            argv->height = atoi(av[i + 1]);
        if (strcmp(av[i], "-c") == 0)
            argv->maxClientNb = atoi(av[i + 1]);
        if (strcmp(av[i], "-f") == 0)
            argv->freq = atoi(av[i + 1]);
    }
}

static int argv_handler_str(int ac, char **av, int i, argv_t *argv)
{
    if (strcmp(av[i], "-n") == 0 && i + 1 <= ac) {
        int j = 0;
        for (; av[i + j + 1] && av[i + j + 1][0] != '-'; j++);
        if (j == 0)
            return (i);
        argv->teamNames = malloc(sizeof(char *) * (j + 1));
        for (int k = 0; k < j; k++)
            argv->teamNames[k] = strdup(av[i + k + 1]);
        argv->teamNames[j] = NULL;
        return (i + j);
    }
    return (i);
}

static void argv_handler_gui(char **av, int i, argv_t *argv)
{
    if (strcmp(av[i], "--ncurses") == 0)
        argv->isNcurses = true;
}

argv_t *parse_arg(int ac, char **av)
{
    argv_t *argv = NULL;

    if (ac < 2)
        return (NULL);
    if (ac == 2 && strcmp(av[1], "--debug") == 0)
        return (debug_argv());
    argv = init_argv();
    for (int i = 0; i < ac; i++) {
        argv_handler_int(ac, av, i, argv);
        i = argv_handler_str(ac, av, i, argv);
        argv_handler_gui(av, i, argv);
    }
    if (!check_argv(argv)) {
        free_argv(argv);
        return (NULL);
    }
    return (argv);
}
