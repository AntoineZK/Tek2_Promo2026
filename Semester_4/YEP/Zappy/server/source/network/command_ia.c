/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** command
*/

#include "zappy.h"

static ia_func_t func[] = {
    {"Forward", &move_player_forward, 0, 7},
    {"Right", &turn_player_right, 0, 7},
    {"Left", &turn_player_left, 0, 7},
    {"Look", &commande_look, 0, 7},
    {"Inventory", &inventory_command, 0, 1},
    {"Broadcast", &broadcast_to_all, 1, 7},
    {"Connect_nbr", &connectnbr_command, 0, 0},
    {"Fork", &fork_command, 0, 42},
    {"Eject", &commande_eject, 0, 7},
    {"Take", &take_object, 1, 7},
    {"Set", &set_object, 1, 7},
    {"Incantation", &evolution, 0, 300},
    {NULL, NULL, 0, 0}
};

static void condition_time_ia(zappy_t *zappy, client_t *tmp, char **cmd, int i)
{
    if (tmp->player->nbCycle <= 0 && tmp->player->canAct == true) {
        if (strcasecmp(cmd[0], "Incantation") == 0 &&
        check_evolution(zappy, tmp) == false) {
            tmp->cmd = remove_command(tmp->cmd);
            free_darray(cmd);
            return;
        }
        if (strcasecmp(cmd[0], "Fork") == 0)
            egg_laying(zappy, tmp);
        tmp->player->nbCycle = func[i].timeVal;
        tmp->player->canAct = false;
    }
    if (tmp->player->nbCycle <= 0 && tmp->player->canAct == false) {
        func[i].func(zappy, tmp, cmd);
        tmp->cmd = remove_command(tmp->cmd);
        tmp->player->canAct = true;
    }
    free_darray(cmd);
}

static char **handle_broadcast(char **cmd)
{
    if (len_darray(cmd) > 1 && strcasecmp(cmd[0], "Broadcast") == 0) {
        char *tmp = malloc(sizeof(char));
        tmp[0] = '\0';
        for (int i = 1; cmd[i] != NULL; i++) {
            strcat_dynamic(&tmp, cmd[i]);
            cmd[i + 1] != NULL ? strcat_dynamic(&tmp, " ") : 0;
        }
        free_darray(cmd);
        cmd = malloc(sizeof(char *) * 3);
        cmd[0] = strdup("Broadcast");
        cmd[1] = strdup(tmp);
        cmd[2] = NULL;
        free(tmp);
        return (cmd);
    }
    return (cmd);
}

void execute_ia(zappy_t *zappy, client_t *tmp)
{
    char **cmd = handle_broadcast(stwa(tmp->cmd->cmd, " \n"));
    int len = len_darray(cmd);

    if (len_darray(cmd) == 0)
        return;
    for (int i = 0; func[i].cmd != NULL; i++) {
        if (strcasecmp(cmd[0], func[i].cmd) == 0 && len - 1 == func[i].nbArgs) {
            condition_time_ia(zappy, tmp, cmd, i);
            return;
        }
    }
    tmp->cmd = remove_command(tmp->cmd);
    update_wbuffer(tmp, "ko\n");
    free_darray(cmd);
}

void resp_to_ia(zappy_t *zappy, client_t *tmp)
{
    int rTeam = get_nbr_client_in_team(zappy->argv->teamNames, tmp->teamName);
    int nbActTeam = zappy->argv->teamClientsNb[rTeam];
    int xMap = zappy->argv->width;
    int yMap = zappy->argv->height;
    int maxSize = snprintf(NULL, 0, "%d\n%d %d\n", nbActTeam, xMap, yMap);
    char *str = malloc(sizeof(char) * (maxSize + 1));

    snprintf(str, maxSize + 1, "%d\n%d %d\n", nbActTeam, xMap, yMap);
    update_wbuffer(tmp, str);
    free(str);
}
