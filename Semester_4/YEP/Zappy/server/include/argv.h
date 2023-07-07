/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** argv
*/

#pragma once

typedef struct argv_s {
    int port;
    int width;
    int height;
    char **teamNames;
    int *teamClientsNb;
    int maxClientNb;
    int freq;
    bool isNcurses;
} argv_t;

// argv
argv_t *init_argv(void);
bool check_argv(argv_t *argv);
argv_t *parse_arg(int ac, char **av);
argv_t *debug_argv(void);
void free_argv(argv_t *argv);
