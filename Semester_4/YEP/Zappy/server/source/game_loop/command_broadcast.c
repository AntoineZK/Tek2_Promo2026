/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_broadcast
*/

#include "zappy.h"
#include <math.h>

static int get_better_y(zappy_t *zap, int y1, int y2)
{
    int y = abs(y1 - y2);
    if (y > zap->argv->height / 2)
        y = zap->argv->height - y;
    if (y1 - y2 > 0)
        return y;
    return -y;
}

static int get_better_x(zappy_t *zap, int x1, int x2)
{
    int x = abs(x1 - x2);
    if (x > zap->argv->width / 2)
        x = zap->argv->width - x;
    if (x1 - x2 > 0)
        return x;
    return -x;
}

static double get_angle(zappy_t *zap, client_t *cli, client_t *guy)
{
    int x0 = guy->player->x;
    int y0 = guy->player->y;
    int x1 = guy->player->x;
    int y1 = guy->player->y;
    guy->player->direction == 0 ? x1 = guy->player->x + 1 : 0;
    guy->player->direction == 1 ? y1 = guy->player->y + 1 : 0;
    guy->player->direction == 2 ? x1 = guy->player->x - 1 : 0;
    guy->player->direction == 3 ? y1 = guy->player->y - 1 : 0;
    int x = x0 + get_better_x(zap, x0, cli->player->x);
    int y = y0 + get_better_y(zap, y0, cli->player->y);
    double dx = x - x0;
    double dy = y - y0;
    double dx1 = x1 - x0;
    double dy1 = y1 - y0;
    double angle_radians = atan2(dy1, dx1) - atan2(dy, dx);
    double angle_degrees = angle_radians * (180.0 / PI);
    if (angle_degrees < 0)
        angle_degrees += 360.0;
    return angle_degrees;
}

static int get_direction(zappy_t *zap, client_t *cli, client_t *guy)
{
    double angle = get_angle(zap, cli, guy);
    if (angle <= 22.5 || angle > 337.5)
        return 1;
    for (int i = 0; i < 7; i++) {
        if (angle > 22.5 + i * 45 && angle <= 22.5 + (i + 1) * 45)
            return i + 2;
    }
    return 8;
}

void broadcast_to_all(zappy_t *zap, client_t *client, char **cmd)
{
    client_t *tmp = zap->ntw->clients;
    int nb = 0;
    int size = 0;
    char *text = NULL;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player == NULL)
            continue;
        if (tmp == client)
            nb = 0;
        else
            nb = get_direction(zap, client, tmp);
        size = snprintf(NULL, 0, "message %d, %s\n", nb, cmd[1]);
        text = alloca(sizeof(char) * size + 1);
        snprintf(text, size + 1, "message %d, %s\n", nb, cmd[1]);
        update_wbuffer(tmp, text);
    }
    broadcast_to_gui(zap, client, cmd[1]);
}
