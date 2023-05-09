/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** server
*/

#pragma once
#include "network.h"

typedef struct teams_s {
    header_t *header;
    network_t *ntw;
    bool shouldStop;
} teams_t;

typedef struct command_s {
    char *name;
    void (*function)(teams_t *teams, sockcli_t *actClient, char **args);
} command_t;

// network/
int create_socket(int port);
void setup_select(teams_t *teams);
void accept_new_client(teams_t *teams);
void handle_request(teams_t *teams);
void update_rbuffer(sockcli_t *cli, header_t *);
void update_wbuffer(sockcli_t *cli, char *);

// lib/
sockcli_t *add_socket_client(sockcli_t *list, int fd);
sockcli_t *disconnect_sockcli(sockcli_t *list);
void print_socket_client(sockcli_t *list);
char **stwa(char const *str, char *delim);
void free_darray(char **darray);
int len_darray(char **darray);
header_t *get_header(char *buffer);
client_t *add_client(client_t *client, char *name, char *uuid);
client_t *load_all_cli(teams_t *teams);
client_t *duplicate_client(client_t *src);
client_t *get_last_client(client_t *allCli);
char *generate_uuid(void);
client_t *free_client(client_t *client);
bool find_uuid(sockcli_t *client, char *uuid);
void strcat_dynamic(char **dest, char *src);
char **split_string(char *str);
char *add_doublequote(char *baseStr);
message_t *gen_mp(char *body, char *send_uuid, char *recv_uuid, time_t t);
message_t *add_message(message_t *allMsg, message_t *new);
char *time_to_str(time_t initialTime);
bool client_exist(client_t *list, char *uuid);
char *gen_resp(char *func, int nbArg, ...);
team_t *get_last_team(team_t *allTeam);
thread_t *get_last_thread(thread_t *allThread);
channel_t *get_last_channel(channel_t *allChannel);
reply_t *get_last_reply(reply_t *allReply);
void free_reply(reply_t *reply);
void free_thread(thread_t *thread);
void free_channel(channel_t *channel);
void free_team(team_t *team);
void free_member(member_t *member);
void free_all_client(client_t *list);
void free_socket_client(sockcli_t *list);
void free_message(message_t *msg);

// commands/
void execute_command(teams_t *teams, sockcli_t *client);
void login(teams_t *teams, sockcli_t *actClient, char **args);
void logout(teams_t *teams, sockcli_t *actClient, char **args);
void send_message(teams_t *teams, sockcli_t *actClient, char **args);
void users(teams_t *teams, sockcli_t *actCli, char **args);
void user(teams_t *teams, sockcli_t *actCli, char **args);
void help(teams_t *server, sockcli_t *actCli, char **args);
void list_message(teams_t *teams, sockcli_t *actCli, char **args);
void create(teams_t *teams, sockcli_t *actCli, char **args);
void subscribe(teams_t *teams, sockcli_t *actCli, char **args);
void subscribed(teams_t *teams, sockcli_t *actCli, char **args);
void unsubscribe(teams_t *teams, sockcli_t *actCli, char **args);
void use_team(teams_t *teams, sockcli_t *actCli, char **args);
void info(teams_t *teams, sockcli_t *actCli, char **args);
void list_team_channel_thread(teams_t *teams, sockcli_t *actCli, char **args);
void stop_server(teams_t *teams, sockcli_t *tmp, char **args);
void exit_server(teams_t *teams, sockcli_t *actCli, char **args);
bool same_sockcli(sockcli_t *cli1, sockcli_t *cli2);
void create_thread(teams_t *teams, sockcli_t *actCli, char **args);
void create_reply(teams_t *teams, sockcli_t *actCli, char **args);
