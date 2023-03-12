/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** help
*/

#include "ftp.h"

static command_t command[] = {
    {"USER", help_user, 1},
    {"PASS", help_pass, 1},
    {"CWD", help_cwd, 1},
    {"CDUP", help_cdup, 1},
    {"QUIT", help_quit, 1},
    {"DELE", help_dele, 1},
    {"PWD", help_pwd, 1},
    {"PASV", help_pasv, 1},
    {"PORT", help_port, 1},
    {"NOOP", help_noop, 1},
    {"RETR", help_retr, 1},
    {"STOR", help_stor, 1},
    {"LIST", help_list, 1},
    {NULL, NULL, 0}
};

ftp_t *help(ftp_t *ftp, int j)
{
    dprintf(ftp->tmp->client_fd, M_214);
    if (j == 0)
        return (ftp);
    for (int i = 0; command[i].name != NULL; i++) {
        if (strcmp(command[i].name, to_uppercase(ftp->commands[1])) == 0) {
            command[i].func(ftp, 0);
            return (ftp);
        }
    }
    dprintf(ftp->tmp->client_fd, M_501);
    return (ftp);
}
