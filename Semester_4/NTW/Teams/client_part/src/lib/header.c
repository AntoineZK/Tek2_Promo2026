/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** header
*/

#include "client.h"

header_t *create_header(char *buffer)
{
    header_t *header = malloc(sizeof(header_t) + (strlen(buffer) + 1));

    header->type = TEXT;
    header->size = strlen(buffer);
    strcpy(header->body, buffer);
    return (header);
}
