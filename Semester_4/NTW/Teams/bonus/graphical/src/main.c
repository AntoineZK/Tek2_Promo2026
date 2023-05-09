/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** main
*/

#include "graphic.h"

int helper(int returnValue)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address");
    printf(" on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
    return returnValue;
}

general_t *init_general(char *ip, int port)
{
    general_t *g = malloc(sizeof(general_t));

    g->network = init_network(ip, port);
    g->graphic = init_graphic();
    return g;
}

void graphic_loop(general_t *g)
{
    while (sfRenderWindow_isOpen(g->graphic->window)) {
        handle_network(g->network);
        while (sfRenderWindow_pollEvent(g->graphic->window, &g->graphic->event))
            event_manager(g);
        sfRenderWindow_clear(g->graphic->window, sfBlack);
        display_all(g->graphic);
        sfRenderWindow_display(g->graphic->window);
    }
}

int main(int ac, char **av)
{
    general_t *g = NULL;
    setbuf(stdout, NULL);

    if (ac == 2 && (strcmp(av[1], "-help") == 0 || strcmp(av[1], "-h") == 0))
        return helper(0);
    if (ac != 3)
        return helper(84);
    g = init_general(av[1], atoi(av[2]));
    graphic_loop(g);
    return (0);
}
