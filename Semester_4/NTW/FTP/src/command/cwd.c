/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** cwd
*/

#include "ftp.h"

char *remove_last_directory(char *str)
{
    for (int i = strlen(str); i > 0; i--) {
        if (str[i] == '/') {
            str[i] = '\0';
            break;
        }
    }
    return (str);
}

int check_valid(ftp_t *ftp)
{
    if (strncmp(ftp->commands[1], "..", 2) == 0 &&
    strcmp(ftp->tmp->directory, ftp->path) == 0) {
        dprintf(ftp->tmp->client_fd, M_550);
        return 1;
    }
    if (strncmp(ftp->commands[1], "..", 2) == 0 &&
    strcmp(ftp->tmp->directory, ftp->path) != 0) {
        ftp->tmp->directory =
        remove_last_directory(ftp->tmp->directory);
        dprintf(ftp->tmp->client_fd, M_250);
        return 1;
    }
    if (strncmp(ftp->commands[1], "/", 1) == 0) {
        dprintf(ftp->tmp->client_fd, M_550);
        return 1;
    }
    return 0;
}

ftp_t *cwd(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    struct stat sb;
    char *new_path = strdup(ftp->tmp->directory);
    my_strcat(&new_path, "/");
    my_strcat(&new_path, ftp->commands[1]);
    if (stat(new_path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        if (check_valid(ftp) == 1)
            return (ftp);
        free(new_path);
        my_strcat(&ftp->tmp->directory, "/");
        my_strcat(&ftp->tmp->directory, ftp->commands[1]);
        dprintf(ftp->tmp->client_fd, M_250);
    } else
        dprintf(ftp->tmp->client_fd, M_550);
    return (ftp);
}
