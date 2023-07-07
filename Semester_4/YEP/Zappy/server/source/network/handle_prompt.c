/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** handle_prompt
*/

#include "zappy.h"

static int receive_server_non_gui(zappy_t *zappy)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

    if (read == -1)
        return (0);
    if (execute_prompt(zappy, line) == false)
        return (0);
    return (1);
}

static int receive_server_ncurses(zappy_t *zappy)
{
    boxes_t *box = zappy->ncurses->boxes[2];
    int max_input_size = box->size[0] - 2;
    char *input = malloc(sizeof(char) * (max_input_size + 1));
    wmove(box->win, 1, strlen(box->name) + 1);
    wgetnstr(box->win, input, max_input_size - strlen(box->name) - 1);
    input[max_input_size] = '\0';
    zappy->ncurses->serverCommand =
    add_command(zappy->ncurses->serverCommand, input, 0);
    wrefresh(box->win);
    if (execute_prompt(zappy, input) == false)
        return (0);
    return (1);
}

int handle_prompt(zappy_t *zappy)
{
    if (FD_ISSET(STDIN_FILENO, &zappy->ntw->rfds)) {
        if (zappy->argv->isNcurses == true)
            return (receive_server_ncurses(zappy));
        return (receive_server_non_gui(zappy));
    }
    return (1);
}
