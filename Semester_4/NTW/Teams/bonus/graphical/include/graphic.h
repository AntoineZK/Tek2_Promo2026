/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** graphic
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

//include for the sfml
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Network.h>

// define for the client
#define IP "127.0.0.1"
#define MAX_BODY_LENGTH 512

// project include
#include "../../../libs/header/header.h"

enum {
    USER,
    DEST,
};

typedef struct hitbox_s {
    sfVector2f pos;
    sfVector2f size;
} hitbox_t;

typedef struct message_s {
    int id;
    char *message;
    int sender;
    sfText *text;
    struct message_s *next;
} message_t;

typedef struct conv_s {
    message_t *messages;
    char *name;
    sfRectangleShape *hitbox;
    struct conv_s *next;
} conv_t;

typedef struct contact_s {
    char *name;
    char *uuid;
    struct contact_s *next;
} contact_t;

typedef struct network_s {
    header_t *header;
    struct sockaddr_in address;
    int server_fd;
    socklen_t addrlen;
    fd_set readfds;
    fd_set writefds;
    struct timeval timeout;
} network_t;

typedef struct graphic_s {
    sfRenderWindow *window;
    sfView *view;
    sfEvent event;
    sfText *inputMessage;
    sfFont *font;
    char input[512];
    sfClock *clock;
    sfTime time;
    float seconds;
    conv_t *selected_conv;
    conv_t *conv_list;
    contact_t *contacts;
} graphic_t;

typedef struct general_s {
    network_t *network;
    graphic_t *graphic;
} general_t;


//network
network_t *init_network(char *ip, int port);
void setup_select(network_t *net);
void send_to_server(network_t *net);
void read_from_server(network_t *net);
void handle_network(network_t *net);
header_t *create_header(char *buffer);

//graphic
graphic_t *init_graphic(void);
void event_manager(general_t *g);
void display_all(graphic_t *gra);

void display_convs_list(graphic_t *gra);
void display_selected_conv(graphic_t *gra);
void add_conv_at_end(graphic_t *gra, char *name);
conv_t *get_conv_by_name(graphic_t *gra, char *name);
conv_t *get_conv_by_hitbox(graphic_t *gra, sfVector2f mouse);
void add_message_at_end_for_selected_conv(graphic_t *gra, const \
char *message, int sender);
void display_messages(graphic_t *gra);
sfText *get_messages(graphic_t *gra, int i);
