/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** reply_list
*/

#include "server.h"

reply_t *add_reply(reply_t *reply, char *body, char *author)
{
    reply_t *new_reply = malloc(sizeof(reply_t));
    reply_t *tmp = reply;

    if (!new_reply)
        return NULL;
    new_reply->body = strdup(body);
    new_reply->author_uuid = strdup(author);
    new_reply->uuid = generate_uuid();
    new_reply->creation_date = time(NULL);
    new_reply->next = NULL;
    if (!reply)
        return new_reply;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_reply;
    return reply;
}

reply_t *get_last_reply(reply_t *allReply)
{
    reply_t *tmp = allReply;

    for (; tmp->next; tmp = tmp->next);
    return tmp;
}

void free_reply(reply_t *reply)
{
    reply_t *current = reply;
    reply_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->body);
        free(current->author_uuid);
        free(current->uuid);
        free(current);
        current = next;
    }
}
