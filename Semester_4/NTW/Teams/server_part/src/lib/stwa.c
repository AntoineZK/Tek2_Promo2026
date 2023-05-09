/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** stwa
*/

#include "server.h"

static int alpha_num(char character, char *del)
{
    for (int i = 0; del[i]; i++)
        if (character == del[i] || character == '\0')
            return (0);
    return (1);
}

static int count_words(char const *str, char *del)
{
    int nb_words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (alpha_num(str[i], del) && !alpha_num(str[i + 1], del))
            nb_words++;
    }
    return (nb_words);
}

char **stwa(char const *str, char *del)
{
    char **word_array = malloc(sizeof(char *) * (count_words(str, del) + 1));
    int nb_words = 0;
    int i_array = 0;

    if (word_array == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (alpha_num(str[i], del))
            nb_words++;
        if (alpha_num(str[i], del) && !alpha_num(str[i + 1], del)) {
            word_array[i_array] = malloc(nb_words + 1);
            strncpy(word_array[i_array], &str[i - nb_words + 1], nb_words);
            word_array[i_array][nb_words] = '\0';
            nb_words = 0;
            i_array++;
        }
    }
    word_array[i_array] = NULL;
    return (word_array);
}

void free_darray(char **darray)
{
    for (int i = 0; darray[i]; i++)
        free(darray[i]);
    free(darray);
}

int len_darray(char **darray)
{
    int i = 0;

    for (; darray[i]; i++);
    return (i);
}
