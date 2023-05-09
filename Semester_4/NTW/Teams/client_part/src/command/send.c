/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** send
*/

#include "client.h"

void send_report(teams_t *teams, char **buffer)
{
    (void)(teams);
    client_event_private_message_received(buffer[1], buffer[2]);
}
