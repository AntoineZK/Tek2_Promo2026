/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** request
*/

#include "server.h"

int handle_receive_two(ssize_t recvLen, teams_t *teams, sockcli_t *tmp)
{
    tmp->rBufferLen += recvLen;
    tmp->rBuffer[tmp->rBufferLen] = '\0';
    if (tmp->rBufferLen < sizeof(header_t))
        return -1;
    teams->header = ((header_t *)tmp->rBuffer);
    if (tmp->rBufferLen < sizeof(header_t) + teams->header->size)
        return -1;
    printf("Client %d Type: %d\n", tmp->fd, teams->header->type);
    printf("Client %d Size: %ld\n", tmp->fd, teams->header->size);
    printf("Client %d Body: %s\n", tmp->fd, teams->header->body);
    update_rbuffer(tmp, teams->header);
    execute_command(teams, tmp);
    return 0;
}

int handle_receive(teams_t *teams, sockcli_t *tmp)
{
    ssize_t recvLen = recv(tmp->fd, tmp->rBuffer + tmp->rBufferLen,
    MAX_BODY_LENGTH - tmp->rBufferLen, 0);

    if (recvLen == -1) {
        printf("Error: %s\n", strerror(errno));
        tmp->terminated = true;
        teams->ntw->nbRemove++;
        return -1;
    } else if (recvLen == 0) {
        tmp->terminated = true;
        teams->ntw->nbRemove++;
    } else {
        return (handle_receive_two(recvLen, teams, tmp));
    }
    return 0;
}

int handle_send(teams_t *teams, sockcli_t *tmp)
{
    ssize_t sendLen = send(tmp->fd, tmp->writeBuffer, tmp->writeBufferLen, 0);

    if (sendLen == -1) {
        printf("Error: %s\n", strerror(errno));
        tmp->terminated = true;
        teams->ntw->nbRemove++;
        return -1;
    } else {
        tmp->writeBufferLen -= sendLen;
        memmove(tmp->writeBuffer, tmp->writeBuffer +
        sendLen, tmp->writeBufferLen);
        tmp->writeBuffer = realloc(tmp->writeBuffer, tmp->writeBufferLen);
    }
    return 0;
}

void handle_request(teams_t *teams)
{
    for (sockcli_t *tmp = teams->ntw->cliCon; tmp != NULL; tmp = tmp->next) {
        int ret = 0;
        if (FD_ISSET(tmp->fd, &teams->ntw->readfds))
            ret = handle_receive(teams, tmp);
        if (ret == -1)
            continue;;
        if (FD_ISSET(tmp->fd, &teams->ntw->writefds))
            handle_send(teams, tmp);
    }
    for (; teams->ntw->nbRemove > 0; teams->ntw->nbRemove--)
        teams->ntw->cliCon = disconnect_sockcli(teams->ntw->cliCon);
}
