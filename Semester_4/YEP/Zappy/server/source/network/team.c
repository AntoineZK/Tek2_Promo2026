/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** team
*/

#include "zappy.h"

int get_nbr_team(char **teams)
{
    int i = 0;

    for (; teams[i]; i++);
    return (i);
}

int get_nbr_client_in_team(char **teams, char *team)
{
    int i = 0;

    for (; teams[i]; i++) {
        if (strcmp(teams[i], team) == 0)
            return (i);
    }
    return (-1);
}

static void egg_is_player(zappy_t *zap, client_t *tmp, int i)
{
    bool isEgg = false;
    zap->argv->teamClientsNb[i]--;
    tmp->teamName = strdup(zap->argv->teamNames[i]);
    tmp->cmd = remove_command(tmp->cmd);
    int x = rand() % zap->argv->width;
    int y = rand() % zap->argv->height;
    eggs_t *egg = get_egg_by_team_name(zap->eggs, tmp->teamName);
    egg != NULL ? x = egg->x, y = egg->y, isEgg = true : 0;
    tmp->player = init_player(x, y, rand() % 4);
    place_player(zap->map, tmp);
    isEgg ? egg_hatching(zap, tmp), zap->eggs = remove_egg(zap->eggs, egg) : 0;
    char *newCo = send_player_new_co(tmp);
    for (client_t *allCli = zap->ntw->clients; allCli; allCli = allCli->next)
        allCli->isGraphical == true ? update_wbuffer(allCli, newCo) : 0;
    free(newCo);
}

bool team_has_place(zappy_t *zap, client_t *tmp)
{
    if (strncasecmp("GRAPHIC", tmp->cmd->cmd, 7) == 0) {
        tmp->teamName = strdup("GRAPHIC");
        tmp->isGraphical = true;
        tmp->cmd = remove_command(tmp->cmd);
        return (true);
    }
    for (int i = 0; zap->argv->teamNames[i]; i++) {
        if (strncasecmp(zap->argv->teamNames[i], tmp->cmd->cmd,
        strlen(zap->argv->teamNames[i])) == 0 &&
        zap->argv->teamClientsNb[i] > 0) {
            egg_is_player(zap, tmp, i);
            return (true);
        }
    }
    return (false);
}
