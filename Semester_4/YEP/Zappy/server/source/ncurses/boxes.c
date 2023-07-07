/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** boxes
*/

#include "zappy.h"

boxes_t *create_box(int pos[2], int size[2], char *name)
{
    boxes_t *box = malloc(sizeof(boxes_t));

    box->pos[0] = pos[0];
    box->pos[1] = pos[1];
    box->size[0] = size[0];
    box->size[1] = size[1];
    box->name = strdup(name);
    box->win = derwin(stdscr, size[1], size[0], pos[1], pos[0]);
    return (box);
}

static boxes_t **create_all_box2(int xMax, int yMax, boxes_t **boxes)
{
    boxes[4] = create_box((int[2]){xMax / 2, yMax / 2}, (int[2]){xMax / 4,
    yMax / 2 - 1}, "Players: ");
    boxes[5] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2},
    (int[2]){xMax / 4, 3}, "Port: ");
    boxes[6] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2 + 3},
    (int[2]){xMax / 4, 3}, "Graphical: ");
    boxes[7] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2 + 6},
    (int[2]){xMax / 4, 3}, "Frequency: ");
    boxes[8] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2 + 9},
    (int[2]){xMax / 4, 3}, "Map Size: ");
    boxes[9] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2 + 12},
    (int[2]){xMax / 4, 3}, "IA: ");
    boxes[10] = create_box((int[2]){xMax / 2 + xMax / 4, yMax / 2 + 15},
    (int[2]){xMax / 4, 3}, "Team: ");
    boxes[11] = NULL;
    return boxes;
}

boxes_t **create_all_box(void)
{
    boxes_t **boxes = malloc(sizeof(boxes_t) * 11);
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    boxes[0] = create_box((int[2]){0, 0}, (int[2]){xMax / 2 - 1, yMax / 2},
    "Receiving:");
    boxes[1] = create_box((int[2]){xMax / 2, 0}, (int[2]){xMax / 2, yMax / 2},
    "Sending:");
    boxes[2] = create_box((int[2]){0, yMax / 2}, (int[2]){xMax / 2, yMax / 4},
    "Server Command:");
    boxes[3] = create_box((int[2]){0, yMax - yMax / 4 - 2}, (int[2]){xMax / 2,
    yMax / 4}, "Server Response:");
    return create_all_box2(xMax, yMax, boxes);
}

void format_boxes(ncurses_t *ncurses)
{
    for (; is_higher_than_box(ncurses->boxes[0], ncurses->receivingCommand);)
        ncurses->receivingCommand = remove_command(ncurses->receivingCommand);
    for (; is_higher_than_box(ncurses->boxes[1], ncurses->sendingCommand);)
        ncurses->sendingCommand = remove_command(ncurses->sendingCommand);
    for (; is_higher_than_box(ncurses->boxes[2], ncurses->serverCommand);)
        ncurses->serverCommand = remove_command(ncurses->serverCommand);
    for (; is_higher_than_box(ncurses->boxes[3], ncurses->serverResponse);)
        ncurses->serverResponse = remove_command(ncurses->serverResponse);
}

void display_box(boxes_t *box, command_t *cmd, int color)
{
    int size = 2;
    for (command_t *tmp = cmd; tmp != NULL; tmp = tmp->next) {
        wattron(box->win, COLOR_PAIR(color));
        mvwprintw(box->win, size, 1, "%s", tmp->cmd);
        wattroff(box->win, COLOR_PAIR(color));
        wrefresh(box->win);
        size += calculate_size(box, tmp->cmd);
    }
}
