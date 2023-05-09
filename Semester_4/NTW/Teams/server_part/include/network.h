/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** network
*/

#pragma once
#include "include.h"
#include "team.h"

enum CONTEXT {
    TEAM,
    CHANNEL,
    THREAD,
    REPLY
};

typedef struct message_s {
    char *body;
    time_t time;
    char *receiver_uuid;
    char *sender_uuid;
    struct message_s *next;
} message_t;

typedef struct infos_s {
    char *username;
    char *uuid;
} infos_t;

typedef struct client_s {
    bool is_connected;
    infos_t *infos;
    struct client_s *next;
} client_t;

typedef struct socket_client {
    int fd;
    int context;
    char **contextArgs;
    bool terminated;
    char rBuffer[MAX_BODY_LENGTH + 1];
    char *writeBuffer;
    size_t writeBufferLen;
    size_t rBufferLen;
    client_t *client;
    struct socket_client *next;
} sockcli_t;

typedef struct network_s {
    int fd;
    int port;
    int max_fd;
    int nbRemove;
    message_t *allMsg;
    team_t *allTeam;
    client_t *allCli;
    fd_set readfds;
    fd_set writefds;
    sockcli_t *cliCon;
    socklen_t addrlen;
    struct sockaddr_in addr;
} network_t;
