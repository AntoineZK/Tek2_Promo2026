/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy
** File description:
** str_fusion
*/

#include "zappy.h"

void strcat_dynamic(char **dest, char *src)
{
    char *str = malloc(sizeof(char) * (strlen(*dest) + strlen(src) + 1));
    int i = 0;

    for (; (*dest)[i] != '\0'; i++)
        str[i] = (*dest)[i];
    for (; src[i - strlen(*dest)] != '\0'; i++)
        str[i] = src[i - strlen(*dest)];
    str[i] = '\0';
    free(*dest);
    (*dest) = str;
}
