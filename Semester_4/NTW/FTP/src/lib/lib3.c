/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** lib3
*/

#include "ftp.h"

void my_strcat(char **dest, char const *src)
{
    char *new_str = malloc(sizeof(char) * (strlen(*dest)
    + strlen(src) + 1));
    int i = 0;
    for (; (*dest)[i] != '\0'; i++)
        new_str[i] = (*dest)[i];
    for (; src[i - strlen(*dest)] != '\0'; i++)
        new_str[i] = src[i - strlen(*dest)];
    new_str[i] = '\0';
    free(*dest);
    (*dest) = new_str;
}

char *stat_file(char *filepath)
{
    struct stat statbuff;
    int file_d = 0;
    char *buffer = NULL;

    stat(filepath, &statbuff);
    file_d = open(filepath, O_RDONLY);
    if (file_d == -1)
        return (NULL);
    buffer = malloc(sizeof(char) * statbuff.st_size + 1);
    if (read(file_d, buffer, statbuff.st_size) <= 0)
        return (NULL);
    close(file_d);
    buffer[statbuff.st_size] = 0;
    return (buffer);
}

bool check_buffer(char *buffer)
{
    int returnval = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\r' || buffer[i] == '\n')
            returnval++;
    if (returnval == 2)
        return (true);
    return (false);
}
