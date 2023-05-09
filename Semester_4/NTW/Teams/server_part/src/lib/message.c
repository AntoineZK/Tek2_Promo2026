/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** message
*/

#include "server.h"

message_t *gen_mp(char *body, char *send_uuid, char *recv_uuid, time_t t)
{
    message_t *new = malloc(sizeof(message_t));

    new->body = strdup(body);
    new->sender_uuid = strdup(send_uuid);
    new->receiver_uuid = strdup(recv_uuid);
    new->time = t;
    new->next = NULL;
    return (new);
}

message_t *add_message(message_t *allMsg, message_t *new)
{
    message_t *tmp = allMsg;

    if (allMsg == NULL)
        return (new);
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return (allMsg);
}

void free_message(message_t *msg)
{
    message_t *current = msg;
    message_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->body);
        free(current->sender_uuid);
        free(current->receiver_uuid);
        free(current);
        current = next;
    }
}
