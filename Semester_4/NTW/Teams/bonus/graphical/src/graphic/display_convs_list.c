/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** display_convs_list
*/

#include "graphic.h"

sfRectangleShape *get_chatbox(graphic_t *gra, int i)
{
    sfRectangleShape* chat_box = sfRectangleShape_create();
    sfRectangleShape_setSize(chat_box, (sfVector2f) {600, 60});
    sfRectangleShape_setPosition(chat_box, (sfVector2f) {50, i * 70 + 300});
    sfRectangleShape_setFillColor(chat_box, sfWhite);
    sfRectangleShape_setOutlineColor(chat_box, sfBlack);
    sfRectangleShape_setOutlineThickness(chat_box, 2);
    sfRenderWindow_drawRectangleShape(gra->window, chat_box, NULL);
    return chat_box;
}

void display_convs_list(graphic_t *gra)
{
    int i = 0;
    conv_t *tmp = gra->conv_list;
    while (gra->conv_list != NULL) {
        sfRectangleShape* chat_box = get_chatbox(gra, i);
        sfText *text = sfText_create();
        sfText_setFont(text, gra->font);
        sfText_setCharacterSize(text, 20);
        sfText_setFillColor(text, sfBlack);
        sfText_setString(text, gra->conv_list->name);
        sfText_setPosition(text, (sfVector2f) {60, i * 70 + 315});
        sfRenderWindow_drawText(gra->window, text, NULL);
        gra->conv_list->hitbox = chat_box;
        gra->conv_list = gra->conv_list->next;
        i++;
    }
    gra->conv_list = tmp;
}
