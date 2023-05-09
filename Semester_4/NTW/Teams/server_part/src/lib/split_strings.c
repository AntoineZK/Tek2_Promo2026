/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** split_strings
*/

#include "server.h"

static bool is_valid(char c)
{
    if (c == ' ' || c == '\n' || c == '\0')
        return false;
    return true;
}

static int len_word_quote(char *str, int i)
{
    int len = 0;

    for (i++; str[i] != '"' && str[i] != '\0'; i++)
        len++;
    return len;
}

static int count_words(char *str)
{
    int nb_words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            nb_words++;
            i += len_word_quote(str, i) + 1;
            continue;
        }
        if (is_valid(str[i]) && !is_valid(str[i + 1]))
            nb_words++;
    }
    return nb_words;
}

static int len_word(char *str, int i)
{
    int len = 0;

    for (; is_valid(str[i]) && str[i] != '\0'; i++)
        len++;
    return len;
}

char **split_string(char *str)
{
    char **array = malloc(sizeof(char *) * (count_words(str) + 1));
    int index_array = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            int len = len_word_quote(str, i);
            array[index_array] = strndup(str + i + 1, len);
            i += len + 1;
            index_array++;
        } if (is_valid(str[i]) && !(str[i] == '"')) {
            int len = len_word(str, i);
            array[index_array] = strndup(str + i, len);
            i += len;
            index_array++;
        }
        if (i == (int)strlen(str))
            break;
    }
    array[index_array] = NULL;
    return array;
}
