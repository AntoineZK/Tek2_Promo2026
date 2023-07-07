/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** main
*/

#include "zappy.h"

int helper(int retVal)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n");
    printf(" name1 name2 ... -c cliNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tcliNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution");
    printf(" of actions\n");
    return (retVal);
}

int main(int ac, char **av)
{
    zappy_t *zappy = NULL;
    argv_t *argv = NULL;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (helper(0));
    argv = parse_arg(ac, av);
    if (argv == NULL)
        return (helper(84));
    srand(time(NULL));
    zappy = init_zappy(argv);
    loop(zappy);
    return (0);
}
