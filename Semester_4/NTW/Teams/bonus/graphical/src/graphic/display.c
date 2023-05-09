/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** display
*/

#include "graphic.h"

void display_all(graphic_t *gra)
{
    sfRectangleShape* chat_box = sfRectangleShape_create();
    sfRectangleShape_setSize(chat_box, (sfVector2f) {900, 30});
    sfRectangleShape_setFillColor(chat_box, sfWhite);
    sfRectangleShape_setPosition(chat_box, (sfVector2f) {700, 900});
    sfRectangleShape_setOutlineThickness(chat_box, 2);
    sfRectangleShape_setOutlineColor(chat_box, sfRed);
    sfRenderWindow_drawRectangleShape(gra->window, chat_box, NULL);
    sfRenderWindow_drawText(gra->window, gra->inputMessage, NULL);
    display_convs_list(gra);
    display_selected_conv(gra);
}
