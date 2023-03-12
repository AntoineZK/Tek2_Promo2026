/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** lib_lklist2
*/

#include "ftp.h"

lk_list *update_lklist(lk_list *list, int index)
{
    lk_list *tmp = list;

    for (int i = 0; i < index; i++)
        tmp = tmp->next;
    tmp->terminated = true;
    return (list);
}

lk_list *remove_node_terminated(lk_list *list)
{
    lk_list *tmp = list;

    if (list == NULL)
        return (NULL);
    if (list->terminated == true) {
        list = list->next;
        free(tmp->directory);
        free(tmp);
        return (list);
    }
    for (lk_list *tmp2 = list; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->next->terminated == true) {
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp2->directory);
            free(tmp2);
            return (list);
        }
    }
    return (list);
}

void lk_list_destroy(lk_list *list)
{
    lk_list *tmp = list;

    while (list != NULL) {
        tmp = list;
        list = list->next;
        close(tmp->client_fd);
        free(tmp->directory);
        free(tmp);
    }
}
