/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** error_helper
*/

#include "ftp.h"

int helper(int value)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens.\n");
    printf("\tpath is the path to the home directory for ");
    printf("the Anonymous user.\n");
    return value;
}

int error_handling(int ac, char **av)
{
    DIR *dir;

    if (ac != 3 || !my_str_is_num(av[1]))
        return helper(84);
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return helper(0);
    dir = opendir(av[2]);
    if (dir == NULL)
        return helper(84);
    closedir(dir);
    return (1);
}
