/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** zappy
*/

#pragma once
#include "include.h"
#include "ressource.h"
#include "argv.h"
#include "inventory.h"
#include "tile.h"
#include "commands.h"
#include "zap_ncurses.h"

typedef struct eggs_s {
    int x;
    int y;
    int id;
    char *team_name;
    struct eggs_s *next;
} eggs_t;

typedef struct player_s {
    int nbCycle;
    bool canAct;
    int x;
    int y;
    int level;
    int direction;
    int time_food;
    char *team_name;
    bool isEvolve;
    invent_t *inventory;
    struct player_s *next_list;
} player_t;

typedef struct client_s {
    bool isGraphical;
    char *teamName;
    int cliFD;
    int id;
    bool terminated;
    char rBuffer[MAX_BODY_LENGTH + 1];
    size_t rBuffLen;
    char *wBuffer;
    player_t *player;
    size_t wBuffLen;
    command_t *cmd;
    struct client_s *next;
    struct client_s *next_on_tile;
} client_t;

typedef struct network_s {
    int sock;
    int maxFD;
    int nbRemove;
    fd_set rfds;
    fd_set wfds;
    socklen_t addrlen;
    struct sockaddr_in addr;
    client_t *clients;
} network_t;

typedef struct zappy_s {
    argv_t *argv;
    network_t *ntw;
    tile_t ***map;
    ressource_t *ressources;
    eggs_t *eggs;
    int idegg;
    int cycletime;
    ncurses_t *ncurses;
} zappy_t;

typedef struct ptr_func_s {
    char *cmd;
    void (*func)(zappy_t *, client_t *, char **);
    int nbArgs;
    int timeVal;
} ia_func_t;

typedef struct graph_func_s {
    char *cmd;
    void (*func)(zappy_t *, client_t *, char **);
    int nbArgs;
} graph_func_t;

typedef struct prompt_func_s {
    char *cmd;
    bool (*func)(zappy_t *, char **cmd);
    int nbArgs;
} prompt_func_t;

typedef struct evol_cond_s {
    int level;
    int nbPlayer;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} evol_cond_t;

// network
int create_server(int port);
void setup_select(zappy_t *zappy);
client_t *add_client(client_t *client, int sock);
void accept_client(zappy_t *zappy);
void handle_client(zappy_t *zappy);
int loop(zappy_t *zap);
zappy_t *init_zappy(argv_t *argv);
client_t *remove_cli(client_t *list);
int get_nbr_team(char **teams);
client_t *get_last_client(client_t *list);
void update_wbuffer(client_t *cli, char *sending);
void resp_to_ia(zappy_t *zappy, client_t *tmp);
void execute_ia(zappy_t *zappy, client_t *tmp);
bool team_has_place(zappy_t *zappy, client_t *tmp);
int get_nbr_client_in_team(char **teams, char *team);
int handle_prompt(zappy_t *zappy);
void free_zappy(zappy_t *zappy);
void execute_graphic(zappy_t *zappy, client_t *tmp);
int max_fd(zappy_t *zappy);
void resp_to_graphic(zappy_t * zappy, client_t *tmp);
void handle_player(zappy_t *zap);
struct timeval handle_time(zappy_t *zap, struct timeval tv);
int get_last_id(client_t *list);
void handle_buffer(zappy_t *zap, client_t *tmp, int recvLen);

// lib
void strcat_dynamic(char **dest, char *src);
char **stwa(char const *str, char *del);
int len_darray(char **darray);
void free_darray(char **darray);

// gameLoop
void look_till_inventory(invent_t *invent, client_t *client, int nb);
void look_right(zappy_t *zap, client_t *client);
void look_down(zappy_t *zap, client_t *client);
void look_left(zappy_t *zap, client_t *client);
void look_up(zappy_t *zap, client_t *client);
void fill_map(tile_t ***map, zone_object_t *obj, int mat);
void fill_random_ressource(zone_object_t *obj, int width);
int advance(int x, int limit, int sens);
void look_till(tile_t *tile, client_t *client);
void turn_player_left(zappy_t *zap, client_t *client, char **cmd);
void turn_player_right(zappy_t *zap, client_t *client, char **cmd);
void commande_look(zappy_t *zap, client_t *client, char **cmd);
void inventory_command(zappy_t *zappy, client_t *client, char **cmd);
player_t *init_player(int x, int y, int direction);
void place_player(tile_t ***map, client_t *client);
void move_up(zappy_t *zap, client_t *client);
void move_down(zappy_t *zap, client_t *client);
void move_left(zappy_t *zap, client_t *client);
void move_right(zappy_t *zap, client_t *client);
void commande_eject(zappy_t *zap, client_t *client, char **cmd);
void move_to_tile(tile_t *start, tile_t *arrive, client_t *client);
bool check_evolution(zappy_t *zap, client_t *client);
void evolution(zappy_t *zap, client_t *client, char **cmd);
tile_t ***init_map(int width, int height);
void file_map_ressources(tile_t ***map, ressource_t *r);
void refile_map_ressources(tile_t ***map, ressource_t *r);
void broadcast_to_all(zappy_t *zap, client_t *client, char **cmd);
void move_player_forward(zappy_t *zap, client_t *client, char **cmd);
void set_object(zappy_t *zap, client_t *client, char **cmd);
void take_object(zappy_t *zap, client_t *client, char **cmd);
void fork_command(zappy_t *zap, client_t *client, char **cmd);
void connectnbr_command(zappy_t *zap, client_t *client, char **cmd);
void update_ressource(res_type_t *obj, int x, int y);
void take_food(zappy_t *zap, client_t *client, char **cmd);
void set_food(zappy_t *zap, client_t *client, char **cmd);
void take_phiras(zappy_t *zap, client_t *client, char **cmd);
void set_phiras(zappy_t *zap, client_t *client, char **cmd);
void take_thystame(zappy_t *zap, client_t *client, char **cmd);
void set_thystame(zappy_t *zap, client_t *client, char **cmd);
void take_mendiane(zappy_t *zap, client_t *client, char **cmd);
void set_mendiane(zappy_t *zap, client_t *client, char **cmd);
void take_sibur(zappy_t *zap, client_t *client, char **cmd);
void set_sibur(zappy_t *zap, client_t *client, char **cmd);
void take_deraumere(zappy_t *zap, client_t *client, char **cmd);
void set_deraumere(zappy_t *zap, client_t *client, char **cmd);
void take_linemate(zappy_t *zap, client_t *client, char **cmd);
void set_linemate(zappy_t *zap, client_t *client, char **cmd);
void up_x(int *x, int *y, int width);
bool check_player(client_t *client, client_t *list);
void remove_ressource(invent_t *inv, int level);
void start_incantation_player(zappy_t *zap, client_t *client);
void update_player_incan(client_t *cli, client_t *list, int mod, zappy_t *zap);
void free_item(zone_object_t **item);
void free_ressources(ressource_t *r);
void free_map(tile_t ***map);
void free_player(player_t *player);
void place_player(tile_t ***map, client_t *client);
bool handle_win(zappy_t *zap);
void display_ncurses_information(zappy_t *zap);

// graphicalLoop
// egg
void egg_laid(zappy_t *zap, client_t *client);
void egg_laying(zappy_t *zap, client_t *client);
void egg_hatching(zappy_t *zap, client_t *client);
void egg_death(zappy_t *zap, client_t *client);

// map
void map_size(zappy_t *zap, client_t *client, char **cmd);
void content_tile(zappy_t *zap, client_t *client, char **cmd);
void map_content(zappy_t *zap, client_t *client, char **cmd);

// player
void send_player_level(zappy_t *zap, client_t *client, char **cmd);
void send_player_inventory(zappy_t *zap, client_t *client, char **cmd);
void send_player_position(zappy_t *zap, client_t *client, char **cmd);
char *send_player_new_co(client_t *client);
void send_player_expulsion(zappy_t *zap, client_t *client);
void send_player_death(zappy_t *zap, client_t *client);
char *send_player_position2(client_t *client);

// ressource
void ressource_dropping(zappy_t *zap, client_t *client, int ressrc);
void ressource_collecting(zappy_t *zap, client_t *client, int ressrc);

// team
void all_team_name(zappy_t *zap, client_t *client, char **cmd);
void broadcast_to_gui(zappy_t *zap, client_t *client, char *cmd);

// time
void time_request(zappy_t *zap, client_t *client, char **cmd);
void time_modification(zappy_t *zap, client_t *client, char **cmd);

// other
void end_game(zappy_t *zap, char *team);
void message_from_serv(zappy_t *zap, char *cmd);

// incantation
void end_incantation(zappy_t *zap, client_t *client, char *cmd);

// eggs
eggs_t *get_egg_by_team_name(eggs_t *list, char *team_name);
void free_egg(eggs_t *list);
eggs_t *remove_egg(eggs_t *list, eggs_t *toRemove);

// prompt
bool execute_prompt(zappy_t *zappy, char *line);
bool break_server(zappy_t *zappy, char **cmd);
bool kill_all_player(zappy_t *zappy, char **cmd);
bool serv_to_graph(zappy_t *zap, char **cmd);
bool kill_by_id(zappy_t *zap, char **cmd);
