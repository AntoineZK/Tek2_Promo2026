/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** execute_command
*/

#include "ftp.h"

static command_t command[] = {
    {"USER", user, 1},
    {"CWD", cwd, 1},
    {"CDUP", cdup, 0},
    {"QUIT", disconnect, 0},
    {"DELE", dele, 1},
    {"PWD", pwd, 0},
    {"PASV", pasv, 0},
    {"PORT", port, 1},
    {"NOOP", noop, 0},
    {"RETR", retr, 1},
    {"STOR", stor, 1},
    {NULL, NULL, 0}
};

int execute_help_list(ftp_t *ftp, int len)
{
    if (strcmp(to_uppercase(ftp->commands[0]), "LIST") == 0) {
        ftp = list(ftp, len);
        free_double_array(ftp->commands);
        return (1);
    }
    if (strcmp(to_uppercase(ftp->commands[0]), "HELP") == 0) {
        ftp = help(ftp, len);
        free_double_array(ftp->commands);
        return (1);
    }
    if (strcmp(to_uppercase(ftp->commands[0]), "PASS") == 0) {
        ftp = pass(ftp, len);
        free_double_array(ftp->commands);
        return (1);
    }
    return (0);
}

ftp_t *execute_generic(ftp_t *ftp, int i, int j, int len)
{
    if (len == command[i].nb_args) {
        ftp = command[i].func(ftp, j);
        free_double_array(ftp->commands);
        return (ftp);
    } else {
        dprintf(ftp->tmp->client_fd, M_550);
        free_double_array(ftp->commands);
        return (ftp);
    }
}

ftp_t *execute_command(ftp_t *ftp, int j)
{
    if (strcmp(ftp->tmp->buffer, "\r\n") == 0)
        return (ftp);
    ftp->commands = my_stwa(ftp->tmp->buffer, "\n\r ");
    int len = len_darray(ftp->commands);
    if (len <= 0) {
        dprintf(ftp->tmp->client_fd, M_500);
        free_double_array(ftp->commands);
        return (ftp);
    }
    len--;
    if (execute_help_list(ftp, len) == 1 && (len == 0 || len == 1))
        return (ftp);
    for (int i = 0; command[i].name; i++) {
        if (strcmp(to_uppercase(ftp->commands[0]), command[i].name) == 0) {
            return (execute_generic(ftp, i, j, len));
        }
    }
    dprintf(ftp->tmp->client_fd, M_500);
    free_double_array(ftp->commands);
    return (ftp);
}
