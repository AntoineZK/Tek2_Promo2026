/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** team
*/

#pragma once
#include "include.h"

typedef struct reply_s {
    char *body;
    char *uuid;
    char *author_uuid;
    time_t creation_date;
    struct reply_s *next;
} reply_t;

typedef struct thread_s {
    char *title;
    char *message;
    char *author_uuid;
    char *uuid;
    time_t creation_date;
    reply_t *replies;
    struct thread_s *next;
} thread_t;

typedef struct channel_s {
    char *name;
    char *description;
    char *uuid;
    thread_t *threads;
    struct channel_s *next;
} channel_t;

typedef struct member_s {
    char *name;
    char *uuid;
    struct member_s *next;
} member_t;

typedef struct team_s {
    char *name;
    char *description;
    char *uuid;
    member_t *members;
    channel_t *channels;
    struct team_s *next;
} team_t;

team_t *add_team(team_t *team, char *name, char *desc);
bool team_exist(team_t *team, char *uuid);
team_t *get_team(team_t *team, char *uuid);
channel_t *add_channel(channel_t *channel, char *name, char *desc);
bool channel_exist(channel_t *channel, char *uuid);
channel_t *get_channel(channel_t *channel, char *uuid);
thread_t *add_thread(thread_t *thread, char *title, char *msg, char *author);
bool thread_exist(thread_t *thread, char *uuid);
thread_t *get_thread(thread_t *thread, char *uuid);
member_t *add_member(member_t *member, char *name, char *uuid);
void remove_member(member_t **head, char *name, char *uuid);
reply_t *add_reply(reply_t *reply, char *body, char *author);
bool ismember(team_t *team, char *uuid);
