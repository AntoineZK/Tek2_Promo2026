/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** loop
*/

#include "zappy.h"

bool running = 0;

static void signal_handler(int signum)
{
    if (signum == SIGINT)
        running = 1;
}

static bool handle_zappy(zappy_t *zap, struct timeval tv)
{
    zap->argv->isNcurses ? display_ncurses(zap->ncurses) : 0;
    zap->argv->isNcurses ? display_ncurses_information(zap) : 0;
    setup_select(zap);
    int act = select(max_fd(zap), &zap->ntw->rfds, &zap->ntw->wfds, NULL, &tv);
    if (act == -1)
        return (false);
    accept_client(zap);
    tv = handle_time(zap, tv);
    handle_client(zap);
    if (handle_prompt(zap) == 0)
        return (false);
    if (handle_win(zap) == false)
        handle_player(zap);
    for (; zap->ntw->nbRemove > 0; zap->ntw->nbRemove--)
        zap->ntw->clients = remove_cli(zap->ntw->clients);
    return (true);
}

int loop(zappy_t *zap)
{
    signal(SIGINT, signal_handler);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000000 / zap->argv->freq;
    while (!running) {
        bool shouldBreak = handle_zappy(zap, tv);
        if (shouldBreak == false)
            break;
    }
    printf("Server closed\n");
    zap->argv->isNcurses ? destroy_ncurses(zap->ncurses) : 0;
    free_zappy(zap);
    return (0);
}
