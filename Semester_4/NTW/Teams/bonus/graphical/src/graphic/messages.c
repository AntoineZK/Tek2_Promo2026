/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** messages
*/

#include "graphic.h"

sfText *get_messages(graphic_t *gra, int i)
{
    sfText *text = sfText_create();
    sfText_setFont(text, gra->font);
    sfText_setCharacterSize(text, 20);
    sfText_setFillColor(text, sfBlack);
    sfText_setString(text, gra->selected_conv->messages->message);
    if (gra->selected_conv->messages->sender == USER) {
        sfText_setFillColor(text, sfBlue);
        sfFloatRect textRect = sfText_getLocalBounds(text);
        sfVector2f origin = {textRect.width, 0};
        sfText_setOrigin(text, origin);
        sfText_setPosition(text, (sfVector2f) {1580, i * 30 + 175});
    } else {
        sfText_setFillColor(text, sfRed);
        sfText_setPosition(text, (sfVector2f) {710, i * 30 + 175});
    }
    return (text);
}

void display_messages(graphic_t *gra)
{
    int i = 0;
    message_t *tmp = gra->selected_conv->messages;
    while (gra->selected_conv->messages != NULL) {
        sfText *text = get_messages(gra, i);
        sfRenderWindow_drawText(gra->window, text, NULL);
        gra->selected_conv->messages =
        gra->selected_conv->messages->next;
        i++;
    }
    gra->selected_conv->messages = tmp;
}

void add_message_at_end_for_selected_conv(graphic_t *gra, const
char *message, int sender)
{
    message_t *new_message = malloc(sizeof(message_t));
    new_message->message = strdup(message);
    new_message->sender = sender;
    new_message->next = NULL;
    if (gra->selected_conv->messages == NULL) {
        gra->selected_conv->messages = new_message;
    } else {
        message_t *tmp = gra->selected_conv->messages;
        while (gra->selected_conv->messages->next != NULL) {
            gra->selected_conv->messages =
            gra->selected_conv->messages->next;
        }
        gra->selected_conv->messages->next = new_message;
        gra->selected_conv->messages = tmp;
    }
}
