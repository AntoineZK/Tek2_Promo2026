/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** ncurses
*/

#pragma once
#include <ncurses.h>
#include "commands.h"

enum ZAP_COLOR {
    BLACK = 1,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

typedef struct boxes_s {
    int pos[2];
    int size[2];
    WINDOW *win;
    char *name;
} boxes_t;

typedef struct ncurses_s {
    boxes_t **boxes;
    command_t *sendingCommand;
    command_t *receivingCommand;
    command_t *serverCommand;
    command_t *serverResponse;
} ncurses_t;

boxes_t *create_box(int pos[2], int size[2], char *name);
ncurses_t *init_ncurses(void);
void destroy_ncurses(ncurses_t *ncurses);
void display_ncurses(ncurses_t *ncurses);
int calculate_size(boxes_t *box, char *cmd);
void display_network_ncurses(ncurses_t *ncurses);
bool is_higher_than_box(boxes_t *box, command_t *cmd);
boxes_t **create_all_box(void);
void format_boxes(ncurses_t *ncurses);
void display_box(boxes_t *box, command_t *cmd, int color);
