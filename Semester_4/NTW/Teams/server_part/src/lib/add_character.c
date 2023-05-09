/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** add_character
*/

#include "server.h"

char *add_doublequote(char *baseStr)
{
    char *newStr = malloc(sizeof(char));

    newStr[0] = '\0';
    strcat_dynamic(&newStr, "\"");
    strcat_dynamic(&newStr, baseStr);
    strcat_dynamic(&newStr, "\"");
    return newStr;
}
