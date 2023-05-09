/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** main
*/

#include "client.h"

int helper(int returnValue)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip address");
    printf(" on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
    return returnValue;
}

teams_t *init_client(char *ip, char *port)
{
    teams_t *teams = malloc(sizeof(teams_t));

    teams->socket_port = atoi(port);
    teams->socket_fd = create_socket(ip, teams->socket_port);
    teams->header = NULL;
    return teams;
}

int client_loop(teams_t *teams)
{
    int activity = 0;

    while (true) {
        setup_select(teams);
        activity = select(teams->socket_fd + 1,
        &teams->readfds, &teams->writefds, NULL, NULL);
        activity == -1 ? exit(EXIT_FAILURE) : 0;
        receive_response(teams);
        send_message(teams);
    }
}

int main(int ac, char **av)
{
    teams_t *teams = NULL;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return helper(0);
    if (ac != 3)
        return helper(84);
    teams = init_client(av[1], av[2]);
    client_loop(teams);
    return 0;
}
