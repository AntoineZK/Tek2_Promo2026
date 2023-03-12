/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** lib
*/

#include "ftp.h"

int my_str_is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}

char *to_uppercase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return (str);
}

int len_darray(char **array)
{
    int i = 0;

    for (; array[i]; i++);
    return (i);
}

int fd_max(ftp_t *ftp)
{
    int max = ftp->server_fd;

    for (lk_list *tmp = ftp->clients; tmp; tmp = tmp->next) {
        if (tmp->client_fd > max)
            max = tmp->client_fd;
    }
    return (max);
}

char *my_strncpy(char *dest, const char *src, int n)
{
    int i = 0;

    for (; i != n; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
