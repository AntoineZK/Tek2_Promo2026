/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** thread_list
*/

#include "server.h"

thread_t *add_thread(thread_t *thread, char *title, char *msg, char *author)
{
    thread_t *new_thread = malloc(sizeof(thread_t));
    thread_t *tmp = thread;

    if (!new_thread)
        return NULL;
    new_thread->title = strdup(title);
    new_thread->message = strdup(msg);
    new_thread->author_uuid = strdup(author);
    new_thread->uuid = generate_uuid();
    new_thread->replies = NULL;
    new_thread->creation_date = time(NULL);
    new_thread->next = NULL;
    if (!thread)
        return new_thread;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_thread;
    return thread;
}

bool thread_exist(thread_t *thread, char *uuid)
{
    thread_t *tmp = thread;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return true;
    return false;
}

thread_t *get_thread(thread_t *thread, char *uuid)
{
    thread_t *tmp = thread;

    for (; tmp; tmp = tmp->next)
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
    return NULL;
}

thread_t *get_last_thread(thread_t *allThread)
{
    thread_t *tmp = allThread;

    for (; tmp->next; tmp = tmp->next);
    return tmp;
}

void free_thread(thread_t *thread)
{
    thread_t *current = thread;
    thread_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->title);
        free(current->message);
        free(current->author_uuid);
        free(current->uuid);
        if (current->replies)
            free_reply(current->replies);
        free(current);
        current = next;
    }
}
