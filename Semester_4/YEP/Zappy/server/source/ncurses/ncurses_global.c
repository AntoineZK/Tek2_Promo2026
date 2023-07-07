/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** ncurses_global
*/

#include "zappy.h"

ncurses_t *init_ncurses(void)
{
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    ncurses_t *ncurses = malloc(sizeof(ncurses_t));
    ncurses->boxes = create_all_box();
    ncurses->sendingCommand = NULL;
    ncurses->receivingCommand = NULL;
    ncurses->serverCommand = NULL;
    ncurses->serverResponse = NULL;
    return (ncurses);
}

void destroy_ncurses(ncurses_t *ncurses)
{
    for (int i = 0; ncurses->boxes[i]; i++) {
        free(ncurses->boxes[i]->name);
        delwin(ncurses->boxes[i]->win);
        free(ncurses->boxes[i]);
    }
    free(ncurses->boxes);
    free(ncurses);
    endwin();
}

void display_ncurses(ncurses_t *ncurses)
{
    clear();
    for (int i = 0; ncurses->boxes[i]; i++) {
        box(ncurses->boxes[i]->win, 0, 0);
        wattron(ncurses->boxes[i]->win, COLOR_PAIR(RED));
        mvwprintw(ncurses->boxes[i]->win, 1, 1, "%s", ncurses->boxes[i]->name);
        wattroff(ncurses->boxes[i]->win, COLOR_PAIR(RED));
        wrefresh(ncurses->boxes[i]->win);
    }
    display_network_ncurses(ncurses);
    refresh();
}

void display_network_ncurses(ncurses_t *cur)
{
    format_boxes(cur);
    int size = 2;
    for (command_t *cmd = cur->receivingCommand; cmd; cmd = cmd->next) {
        wattron(cur->boxes[0]->win, COLOR_PAIR(RED));
        mvwprintw(cur->boxes[0]->win, size, 1, "%s from %d", cmd->cmd, cmd->id);
        wattroff(cur->boxes[0]->win, COLOR_PAIR(RED));
        wrefresh(cur->boxes[0]->win);
        size += calculate_size(cur->boxes[0], cmd->cmd);
    }
    size = 2;
    for (command_t *cmd = cur->sendingCommand; cmd; cmd = cmd->next) {
        wattron(cur->boxes[1]->win, COLOR_PAIR(BLUE));
        mvwprintw(cur->boxes[1]->win, size, 1, "%s to %d", cmd->cmd, cmd->id);
        wattroff(cur->boxes[1]->win, COLOR_PAIR(BLUE));
        wrefresh(cur->boxes[1]->win);
        size += calculate_size(cur->boxes[1], cmd->cmd);
    }
    display_box(cur->boxes[2], cur->serverCommand, GREEN);
    display_box(cur->boxes[3], cur->serverResponse, YELLOW);
}
