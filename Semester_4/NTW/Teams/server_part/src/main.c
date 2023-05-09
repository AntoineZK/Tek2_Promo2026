/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** main
*/

#include "server.h"

int helper(int returnValue)
{
    printf("USAGE: ./myteams_server port\n");
    printf("\tport is the port number on which the server socket listens.\n");
    return returnValue;
}

teams_t *init_server(char *port)
{
    teams_t *teams = malloc(sizeof(teams_t));

    teams->ntw = malloc(sizeof(network_t));
    teams->ntw->port = atoi(port);
    teams->ntw->fd = create_socket(teams->ntw->port);
    if (teams->ntw->fd == -1) {
        free(teams->ntw);
        free(teams);
        return (NULL);
    }
    teams->ntw->cliCon = NULL;
    teams->ntw->allMsg = NULL;
    teams->ntw->addrlen = sizeof(teams->ntw->addr);
    teams->ntw->allCli = NULL;
    teams->ntw->nbRemove = 0;
    teams->ntw->max_fd = 0;
    teams->shouldStop = false;
    teams->ntw->allTeam = NULL;
    return teams;
}

void free_all(teams_t *teams)
{
    free_message(teams->ntw->allMsg);
    free_socket_client(teams->ntw->cliCon);
    free_all_client(teams->ntw->allCli);
    free_team(teams->ntw->allTeam);
    free(teams->ntw);
    free(teams);
}

int server_loop(teams_t *teams)
{
    while (true) {
        if (teams->shouldStop)
            break;
        setup_select(teams);
        if (select(FD_SETSIZE, &teams->ntw->readfds,
        &teams->ntw->writefds, NULL, NULL) < 0)
            return (84);
        if (FD_ISSET(teams->ntw->fd, &teams->ntw->readfds))
            accept_new_client(teams);
        handle_request(teams);
        print_socket_client(teams->ntw->cliCon);
    }
    free_all(teams);
    return (0);
}

int main(int ac, char **av)
{
    teams_t *teams = NULL;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return helper(0);
    if (ac != 2)
        return helper(84);
    teams = init_server(av[1]);
    if (teams == NULL)
        return (84);
    teams->ntw->allCli = load_all_cli(teams);
    return (server_loop(teams));
}
