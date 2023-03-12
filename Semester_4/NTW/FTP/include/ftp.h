/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** ftp
*/

#pragma once
#include "my.h"

#define M_120 "120 Service ready in nnn minutes.\r\n"
#define M_125 "125 Data connection already open; transfer starting.\r\n"
#define M_150 "150 File status okay; about to open data connection.\r\n"
#define M_200 "200 Command okay.\r\n"
#define M_202 "202 Command not implemented, superfluous at this site.\r\n"
#define M_211 "211 System status, or system help reply.\r\n"
#define M_212 "212 Directory status.\r\n"
#define M_213 "213 File status.\r\n"
#define M_214 "214 Help message.\r\n"
#define M_220 "220 Service ready for new user.\r\n"
#define M_221 "221 Service closing control connection.\r\n"
#define M_226 "226 Closing data connection.\r\n"
#define M_227 "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n"
#define M_230 "230 User logged in, proceed.\r\n"
#define M_250 "250 Requested file action okay, completed.\r\n"
#define M_257 "257 \"%s\" created.\r\n"
#define M_331 "331 User name okay, need password.\r\n"
#define M_332 "332 Need account for login.\r\n"
#define M_350 "350 Requested file action pending further information.\r\n"
#define M_421 "421 Service not available, closing control connection.\r\n"
#define M_425 "425 Can't open data connection.\r\n"
#define M_426 "426 Connection closed; transfer aborted.\r\n"
#define M_450 "450 Requested file action not taken.\r\n"
#define M_451 "451 Requested action aborted: local error in processing.\r\n"
#define M_452 "452 Requested action not taken.\r\n"
#define M_500 "500 Syntax error, command unrecognized.\r\n"
#define M_501 "501 Syntax error in parameters or arguments.\r\n"
#define M_502 "502 Command not implemented.\r\n"
#define M_503 "503 Bad sequence of commands.\r\n"
#define M_504 "504 Command not implemented for that parameter.\r\n"
#define M_530 "530 Not logged in.\r\n"
#define M_532 "532 Need account for storing files.\r\n"
#define M_550 "550 Requested action not taken.\r\n"
#define M_551 "551 Requested action aborted: page type unknown.\r\n"
#define M_552 "552 Requested file action aborted.\r\n"
#define M_553 "553 Requested action not taken.\r\n"

typedef struct lk_list_s {
    int client_fd;
    bool terminated;
    char *directory;
    int port;
    char *ip;
    int pasv_fd;
    int port_fd;
    bool logged;
    char *username;
    bool pasv;
    bool active;
    char *buffer;
    struct lk_list_s *next;
} lk_list;

typedef struct ftp_s {
    int port;
    char *path;
    int server_fd;
    fd_set readfds;
    struct sockaddr_in socket_addr;
    socklen_t socket_addr_len;
    lk_list *clients;
    char **commands;
    lk_list *tmp;
    int num_remove;
    char *helper;
} ftp_t;

typedef struct command_s {
    char *name;
    ftp_t *(*func)(ftp_t *, int);
    int nb_args;
} command_t;

int my_str_is_num(char *str);
int list_size(lk_list *list);
lk_list *add_node_last(lk_list *list, int data, char *path);
lk_list *pop_node_front(lk_list *list);
lk_list *pop_node_back(lk_list *list);
lk_list *pop_node_index(lk_list *list, int index);
lk_list *update_lklist(lk_list *list, int index);
lk_list *remove_node_terminated(lk_list *list);
void handle_connection(ftp_t *ftp);
void handle_requests(ftp_t *ftp);
int create_socket(int port);
void init_ftp(ftp_t *ftp, char **av);
void set_fd(ftp_t *ftp);
int helper(int value);
int error_handling(int ac, char **av);
ftp_t *disconnect(ftp_t *ftp, int i);
ftp_t *fd_is_set(ftp_t *ftp, int i);
char *to_uppercase(char *str);
char **my_stwa(char const *str, char *del);
void free_double_array(char **array);
void print_darray(char **array);
int len_darray(char **array);
ftp_t *execute_command(ftp_t *ftp, int i);
int fd_max(ftp_t *ftp);
char *my_strncpy(char *dest, const char *src, int n);
bool check_buffer(char *buffer);
ftp_t *list(ftp_t *ftp, int i);
void my_strcat(char **dest, char const *src);
ftp_t *cwd(ftp_t *ftp, int j);
ftp_t *noop(ftp_t *ftp, int j);
ftp_t *pwd(ftp_t *ftp, int j);
ftp_t *cdup(ftp_t *ftp, int j);
char *remove_last_directory(char *str);
ftp_t *dele(ftp_t *ftp, int j);
ftp_t *help(ftp_t *ftp, int j);
char *stat_file(char *filepath);
ftp_t *help_dele(ftp_t *ftp, int j);
ftp_t *help_pwd(ftp_t *ftp, int j);
ftp_t *help_pasv(ftp_t *ftp, int j);
ftp_t *help_port(ftp_t *ftp, int j);
ftp_t *help_list(ftp_t *ftp, int j);
ftp_t *help_cwd(ftp_t *ftp, int j);
ftp_t *help_cdup(ftp_t *ftp, int j);
ftp_t *help_noop(ftp_t *ftp, int j);
ftp_t *help_quit(ftp_t *ftp, int j);
ftp_t *help_retr(ftp_t *ftp, int j);
ftp_t *help_stor(ftp_t *ftp, int j);
ftp_t *help_user(ftp_t *ftp, int j);
ftp_t *help_pass(ftp_t *ftp, int j);
ftp_t *user(ftp_t *ftp, int j);
ftp_t *pass(ftp_t *ftp, int j);
ftp_t *retr(ftp_t *ftp, int j);
ftp_t *stor(ftp_t *ftp, int j);
ftp_t *port(ftp_t *ftp, int j);
void lk_list_destroy(lk_list *list);
ftp_t *pasv(ftp_t *ftp, int j);
