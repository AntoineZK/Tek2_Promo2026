/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** lib_lklist
*/

#include "ftp.h"

int list_size(lk_list *list)
{
    lk_list *tmp = list;
    int size = 0;

    for (; tmp; tmp = tmp->next)
        size++;
    return (size);
}

lk_list *add_node_last(lk_list *list, int data, char *path)
{
    lk_list *new = malloc(sizeof(lk_list));
    new->client_fd = data;
    new->terminated = false;
    new->directory = strdup(path);
    new->port = 0;
    new->ip = NULL;
    new->pasv_fd = -1;
    new->logged = false;
    new->username = NULL;
    new->pasv = false;
    new->active = false;
    new->next = NULL;
    new->buffer = malloc(sizeof(char));
    new->buffer[0] = '\0';
    if (list == NULL)
        return (new);
    lk_list *tmp = list;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    return (list);
}

lk_list *pop_node_front(lk_list *list)
{
    lk_list *tmp = list;

    if (list == NULL)
        return (NULL);
    list = list->next;
    free(tmp->directory);
    free(tmp);
    return (list);
}

lk_list *pop_node_back(lk_list *list)
{
    lk_list *tmp = list;

    if (list == NULL)
        return (NULL);
    if (list->next == NULL) {
        free(list->directory);
        free(list);
        return (NULL);
    }
    for (; tmp->next->next != NULL; tmp = tmp->next);
    free(tmp->next->directory);
    free(tmp->next);
    tmp->next = NULL;
    return (list);
}

lk_list *pop_node_index(lk_list *list, int index)
{
    if (index == 0)
        return (pop_node_front(list));
    if (index == list_size(list) - 1)
        return (pop_node_back(list));
    lk_list *prev = list;
    lk_list *current = list->next;
    for (; index != 1; index--) {
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    free(current->directory);
    free(current);
    current = NULL;
    return (list);
}
