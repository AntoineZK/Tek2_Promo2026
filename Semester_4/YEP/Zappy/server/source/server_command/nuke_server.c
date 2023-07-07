/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** nuke_server
*/

#include "zappy.h"

bool kill_all_player(zappy_t *zappy, char **cmd)
{
    (void)cmd;
    message_from_serv(zappy, "NUCLEAR");
    for (client_t *cli = zappy->ntw->clients; cli; cli = cli->next) {
        if (cli->player != NULL) {
            update_wbuffer(cli, "dead\n");
            send_player_death(zappy, cli);
        }
    }
    zappy->argv->isNcurses ? zappy->ncurses->serverResponse =
    add_command(zappy->ncurses->serverResponse, "NUKE BEEN LAUNCHED", 0) : 0;
    return (true);
}
