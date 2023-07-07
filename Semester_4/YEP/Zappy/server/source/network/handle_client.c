/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** handle
*/

#include "zappy.h"

void update_wbuffer(client_t *cli, char *sending)
{
    size_t len = strlen(sending);

    cli->wBuffer = realloc(cli->wBuffer, cli->wBuffLen + len + 1);
    memcpy(cli->wBuffer + cli->wBuffLen, sending, len + 1);
    cli->wBuffLen += len;
}

static void read_client(zappy_t *zappy, client_t *tmp)
{
    ssize_t recvLen = recv(tmp->cliFD, tmp->rBuffer + tmp->rBuffLen,
    MAX_BODY_LENGTH - tmp->rBuffLen, 0);

    if (recvLen <= 0) {
        tmp->terminated = true;
        zappy->ntw->nbRemove++;
        return;
    }
    handle_buffer(zappy, tmp, recvLen);
    if (tmp->rBuffLen >= MAX_BODY_LENGTH) {
        tmp->terminated = true;
        zappy->ntw->nbRemove++;
        return;
    }
}

static void remove_player_tile(zappy_t *zappy, client_t *cli)
{
    tile_t *tile = zappy->map[cli->player->y][cli->player->x];
    client_t *tmp = tile->player;
    if (tmp == cli) {
        tile->player = tmp->next_on_tile;
        return;
    }
    for (; tmp->next_on_tile != cli; tmp = tmp->next_on_tile);
    tmp->next_on_tile = cli->next_on_tile;
}

static void write_client(zappy_t *zappy, client_t *tmp)
{
    ssize_t sendLen = send(tmp->cliFD, tmp->wBuffer, tmp->wBuffLen, 0);

    if (zappy->argv->isNcurses) {
        for (size_t i = 0; i < tmp->wBuffLen; i++)
            tmp->wBuffer[i] == '\n' ? tmp->wBuffer[i] = ' ' : 0;
        zappy->argv->isNcurses ? zappy->ncurses->sendingCommand =
        add_command(zappy->ncurses->sendingCommand, tmp->wBuffer, tmp->id) : 0;
    }
    if (sendLen == -1 || !strncmp(tmp->wBuffer, "dead", 4) ||
    !strncmp(tmp->wBuffer, "victory", 7) ||
    !strncmp(tmp->wBuffer, "defeat", 6)) {
        remove_player_tile(zappy, tmp);
        tmp->terminated = true;
        zappy->ntw->nbRemove++;
        return;
    }
    tmp->wBuffLen -= sendLen;
    memmove(tmp->wBuffer, tmp->wBuffer + sendLen, tmp->wBuffLen);
    tmp->wBuffer = realloc(tmp->wBuffer, tmp->wBuffLen);
}

void handle_client(zappy_t *zappy)
{
    for (client_t *tmp = zappy->ntw->clients; tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->cliFD, &zappy->ntw->rfds))
            read_client(zappy, tmp);
        if (FD_ISSET(tmp->cliFD, &zappy->ntw->wfds))
            write_client(zappy, tmp);
    }
}
