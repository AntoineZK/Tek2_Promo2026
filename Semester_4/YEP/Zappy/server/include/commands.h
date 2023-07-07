/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** commands
*/

#pragma once

typedef struct command_s {
    char *cmd;
    int id;
    struct command_s *next;
} command_t;

command_t *add_command(command_t *list, char *cmd, int id);
command_t *remove_command(command_t *list);
int nb_command(command_t *list);
void free_command(command_t *list);
