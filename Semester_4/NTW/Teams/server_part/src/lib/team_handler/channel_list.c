/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** channel_list
*/

#include "server.h"

channel_t *add_channel(channel_t *channel, char *name, char *desc)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    channel_t *tmp = channel;

    if (!new_channel)
        return NULL;
    new_channel->name = strdup(name);
    new_channel->description = strdup(desc);
    new_channel->uuid = generate_uuid();
    new_channel->threads = NULL;
    new_channel->next = NULL;
    if (!channel)
        return new_channel;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_channel;
    return channel;
}

bool channel_exist(channel_t *channel, char *uuid)
{
    channel_t *tmp = channel;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return true;
    return false;
}

channel_t *get_channel(channel_t *channel, char *uuid)
{
    channel_t *tmp = channel;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
    return NULL;
}

channel_t *get_last_channel(channel_t *allChannel)
{
    channel_t *tmp = allChannel;

    for (; tmp->next; tmp = tmp->next);
    return tmp;
}

void free_channel(channel_t *channel)
{
    channel_t *current = channel;
    channel_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->description);
        free(current->uuid);
        if (current->threads)
            free_thread(current->threads);
        free(current);
        current = next;
    }
}
