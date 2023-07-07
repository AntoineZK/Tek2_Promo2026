/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** map_graphic
*/

#include "zappy.h"

void map_size(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int maxSize = snprintf(NULL, 0, "msz %d %d\n", zap->argv->width,
    zap->argv->height);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "msz %d %d\n", zap->argv->width,
    zap->argv->height);
    update_wbuffer(client, str);
}

void fill_map_buffer(client_t *client, int x, int y, tile_t ***map)
{
    int maxSize = snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d\n",
    x, y, map[y][x]->item->food, map[y][x]->item->linemate,
    map[y][x]->item->deraumere, map[y][x]->item->sibur,
    map[y][x]->item->mendiane, map[y][x]->item->phiras,
    map[y][x]->item->thystame);
    char *str = alloca(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "bct %d %d %d %d %d %d %d %d %d\n",
    x, y, map[y][x]->item->food, map[y][x]->item->linemate,
    map[y][x]->item->deraumere, map[y][x]->item->sibur,
    map[y][x]->item->mendiane, map[y][x]->item->phiras,
    map[y][x]->item->thystame);
    update_wbuffer(client, str);
}

void content_tile(zappy_t *zap, client_t *client, char **cmd)
{
    int x = atoi(cmd[1]);
    int y = atoi(cmd[2]);

    fill_map_buffer(client, x, y, zap->map);
}

void map_content(zappy_t *zap, client_t *client, char **cmd)
{
    (void)cmd;
    int y = 0;
    int x = 0;

    for (y = 0; y < zap->argv->height; y++) {
        for (x = 0; x < zap->argv->width; x++) {
            fill_map_buffer(client, x, y, zap->map);
        }
    }
}
