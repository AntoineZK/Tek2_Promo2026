/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** command_server
*/

#include "zappy.h"

static prompt_func_t func[] = {
    {"Quit", &break_server, 0},
    {"Nuke", &kill_all_player, 0},
    {"Send", &serv_to_graph, 1},
    {"Kill", &kill_by_id, 1},
    {NULL, NULL, 0}
};

static char **send_command(char **cmd)
{
    if (len_darray(cmd) > 1 && strcasecmp(cmd[0], "Send") == 0) {
        char *tmp = malloc(sizeof(char));
        tmp[0] = '\0';
        for (int i = 1; cmd[i] != NULL; i++) {
            strcat_dynamic(&tmp, cmd[i]);
            cmd[i + 1] != NULL ? strcat_dynamic(&tmp, " ") : 0;
        }
        free_darray(cmd);
        cmd = malloc(sizeof(char *) * 3);
        cmd[0] = strdup("Send");
        cmd[1] = strdup(tmp);
        cmd[2] = NULL;
        free(tmp);
        return (cmd);
    }
    return (cmd);
}

bool execute_prompt(zappy_t *zappy, char *line)
{
    char **cmd = send_command(stwa(line, " \n"));
    int len = len_darray(cmd);

    free(line);
    if (len_darray(cmd) == 0)
        return (true);
    for (int i = 0; func[i].cmd != NULL; i++) {
        if (strcasecmp(func[i].cmd, cmd[0]) == 0 && len - 1 == func[i].nbArgs) {
            bool ret = func[i].func(zappy, cmd);
            free_darray(cmd);
            return (ret);
        }
    }
    if (zappy->argv->isNcurses == false)
        printf("Unknown command\n");
    else
        zappy->ncurses->serverResponse =
        add_command(zappy->ncurses->serverResponse, "Unknown command", 0);
    free_darray(cmd);
    return (true);
}
