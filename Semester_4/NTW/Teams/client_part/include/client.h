/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** client
*/

#pragma once
//include linux basics lib
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>

//include for linux socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>

//include for the uuid
#include <uuid/uuid.h>

// define for the client
#define IP "127.0.0.1"
#define MAX_BODY_LENGTH 512

// project include
#include "../../libs/myteams/logging_client.h"
#include "../../libs/header/header.h"

typedef struct teams_s {
    header_t *header;
    int socket_fd;
    int socket_port;
    int max_fd;
    struct sockaddr_in address;
    socklen_t addrlen;
    fd_set readfds;
    fd_set writefds;
} teams_t;

typedef struct command_s {
    char *name;
    void (*function)(teams_t *teams, char **buffer);
} command_t;

// network/
int create_socket(const char *ip, int port);
void setup_select(teams_t *teams);
int send_message(teams_t *teams);
int receive_response(teams_t *teams);

// lib/
header_t *create_header(char *buffer);
char **split_string(char *str);
time_t str_to_time(char *str);

// command/
void login(teams_t *teams, char **args);
void logout(teams_t *teams, char **args);
void send_report(teams_t *teams, char **args);
void launch_commands(teams_t *teams, char *buffer);
void users(teams_t *teams, char **buffer);
void user(teams_t *teams, char **buffer);
void list_message(teams_t *teams, char **buffer);
void subscribe(teams_t *teams, char **buffer);
void unsubscribe(teams_t *teams, char **buffer);
void creating(teams_t *teams, char **args);
void list_all(teams_t *teams, char **args);
void info_data(teams_t *teams, char **args);
void error_team(teams_t *teams, char **args);
void error_channel(teams_t *teams, char **args);
void error_thread(teams_t *teams, char **args);
void error_user(teams_t *teams, char **args);
void error_unauthorized(teams_t *teams, char **args);
