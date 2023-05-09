/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** update_buffer
*/

#include "server.h"

void update_rbuffer(sockcli_t *cli, header_t *header)
{
    size_t sizeHeader = sizeof(header_t) + header->size;

    memcpy(cli->rBuffer, cli->rBuffer + sizeHeader,
    cli->rBufferLen - sizeHeader);
    cli->rBufferLen -= sizeHeader;
}

void update_wbuffer(sockcli_t *cli, char *response)
{
    size_t len = strlen(response);

    cli->writeBuffer = realloc(cli->writeBuffer, cli->writeBufferLen + len);
    memcpy(cli->writeBuffer + cli->writeBufferLen, response, len);
    cli->writeBufferLen += len;
}
