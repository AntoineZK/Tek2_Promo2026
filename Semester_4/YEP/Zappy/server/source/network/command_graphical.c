/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** command_graphical
*/

#include "zappy.h"

static graph_func_t func[] = {
    {"msz", &map_size, 0},
    {"bct", &content_tile, 2},
    {"mct", &map_content, 0},
    {"tna", &all_team_name, 0},
    {"ppo", &send_player_position, 1},
    {"plv", &send_player_level, 1},
    {"pin", &send_player_inventory, 1},
    {"sgt", &time_request, 0},
    {"sst", &time_modification, 1},
    {NULL, NULL, 0}
};

void execute_graphic(zappy_t *zappy, client_t *tmp)
{
    char **cmd = stwa(tmp->cmd->cmd, " \n");
    int len = len_darray(cmd);

    if (len_darray(cmd) == 0)
        return;
    for (int i = 0; func[i].cmd != NULL; i++) {
        if (strcasecmp(cmd[0], func[i].cmd) == 0 && len - 1 == func[i].nbArgs) {
            func[i].func(zappy, tmp, cmd);
            free_darray(cmd);
            tmp->cmd = remove_command(tmp->cmd);
            return;
        }
    }
    update_wbuffer(tmp, "suc\n");
    free_darray(cmd);
    tmp->cmd = remove_command(tmp->cmd);
}

void resp_to_graphic(zappy_t *zappy, client_t *tmp)
{
    map_size(zappy, tmp, NULL);
    time_request(zappy, tmp, NULL);
    map_content(zappy, tmp, NULL);
    all_team_name(zappy, tmp, NULL);
    for (client_t *ply = zappy->ntw->clients; ply; ply = ply->next) {
        if (ply->isGraphical == false && ply->teamName != NULL) {
            char *str = send_player_new_co(ply);
            update_wbuffer(tmp, str);
            free(str);
        }
    }
}
