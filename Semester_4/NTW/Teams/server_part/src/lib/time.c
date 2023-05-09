/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** time
*/

#include "server.h"

time_t parse_time(char *tok, struct tm timeinfo)
{
    tok = strtok(NULL, ":");
    if (tok == NULL)
        return -1;
    timeinfo.tm_hour = atoi(tok);
    tok = strtok(NULL, ":");
    if (tok == NULL)
        return -1;
    timeinfo.tm_min = atoi(tok);
    tok = strtok(NULL, "");
    if (tok == NULL)
        return -1;
    timeinfo.tm_sec = atoi(tok);
    timeinfo.tm_isdst = -1;
    return mktime(&timeinfo);
}

time_t str_to_time(char *str)
{
    struct tm timeinfo = {0};

    char *tok = strtok(str, "-");
    if (tok == NULL)
        return -1;
    timeinfo.tm_year = atoi(tok) - 1900;
    tok = strtok(NULL, "-");
    if (tok == NULL)
        return -1;
    timeinfo.tm_mon = atoi(tok) - 1;
    tok = strtok(NULL, " ");
    if (tok == NULL)
        return -1;
    timeinfo.tm_mday = atoi(tok);
    return parse_time(tok, timeinfo);
}
