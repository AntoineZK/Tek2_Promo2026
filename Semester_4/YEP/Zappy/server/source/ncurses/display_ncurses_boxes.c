/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** display_ncurses_two
*/

#include "zappy.h"

static void display_ncurses_info_four(zappy_t *zap)
{
    boxes_t *boxe7 = zap->ncurses->boxes[4];
    int i = 2;
    for (client_t *cli = zap->ntw->clients; cli; cli = cli->next, i++) {
        if (cli->player != NULL && i < boxe7->size[1]) {
            wattron(boxe7->win, COLOR_PAIR(GREEN));
            mvwprintw(boxe7->win, i, 1, "ID: %d at %d %d with level %d",
            cli->id, cli->player->x, cli->player->y,
            cli->player->level);
            wattroff(boxe7->win, COLOR_PAIR(GREEN));
        }
    }
    for (int i = 4; i < 11; i++)
        wrefresh(zap->ncurses->boxes[i]->win);

}

static void display_ncurses_info_three(zappy_t *zap, boxes_t *boxe6)
{
    int mTeam = get_nbr_team(zap->argv->teamNames);
    int *checkTeamCo = malloc(sizeof(int) * (mTeam + 1));
    for (int i = 0; i < mTeam; i++)
        checkTeamCo[i] = 0;
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next) {
        if (tmp->teamName != NULL) {
            int rTeam = get_nbr_client_in_team(zap->argv->teamNames,
            tmp->teamName);
            zap->argv->teamClientsNb[rTeam] > 0 ? checkTeamCo[rTeam] = 1 : 0;
        }
    }
    int nTeam = 0;
    for (int i = 0; i < mTeam; i++)
        nTeam += checkTeamCo[i];
    wattron(boxe6->win, COLOR_PAIR(MAGENTA));
    mvwprintw(boxe6->win, 1, strlen(boxe6->name) + 1, "%d / %d", nTeam, mTeam);
    wattroff(boxe6->win, COLOR_PAIR(MAGENTA));
    display_ncurses_info_four(zap);
}

static void display_ncurses_information_two(zappy_t *zap)
{
    boxes_t *boxe4 = zap->ncurses->boxes[8];
    wattron(boxe4->win, COLOR_PAIR(YELLOW));
    mvwprintw(boxe4->win, 1, strlen(boxe4->name) + 1,
    "x : %d | y : %d", zap->argv->width, zap->argv->height);
    wattroff(boxe4->win, COLOR_PAIR(YELLOW));
    boxes_t *boxe5 = zap->ncurses->boxes[9];
    int nbIA = 0;
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next)
        tmp->player != NULL ? nbIA++ : 0;
    wattron(boxe5->win, COLOR_PAIR(BLUE));
    mvwprintw(boxe5->win, 1, strlen(boxe5->name) + 1, "%d", nbIA);
    wattroff(boxe5->win, COLOR_PAIR(BLUE));
    boxes_t *boxe6 = zap->ncurses->boxes[10];
    display_ncurses_info_three(zap, boxe6);
}

void display_ncurses_information(zappy_t *zap)
{
    boxes_t *boxe = zap->ncurses->boxes[5];
    wattron(boxe->win, COLOR_PAIR(CYAN));
    mvwprintw(boxe->win, 1, strlen(boxe->name) + 1, "%d", zap->argv->port);
    wattroff(boxe->win, COLOR_PAIR(CYAN));
    int nbGraphic = 0;
    for (client_t *tmp = zap->ntw->clients; tmp; tmp = tmp->next)
        tmp->isGraphical ? nbGraphic++ : 0;
    boxes_t *boxe2 = zap->ncurses->boxes[6];
    wattron(boxe2->win, COLOR_PAIR(RED));
    mvwprintw(boxe2->win, 1, strlen(boxe2->name) + 1, "%d", nbGraphic);
    wattroff(boxe2->win, COLOR_PAIR(RED));
    boxes_t *boxe3 = zap->ncurses->boxes[7];
    wattron(boxe3->win, COLOR_PAIR(GREEN));
    mvwprintw(boxe3->win, 1, strlen(boxe3->name) + 1, "%d", zap->argv->freq);
    wattroff(boxe3->win, COLOR_PAIR(GREEN));
    display_ncurses_information_two(zap);
}
