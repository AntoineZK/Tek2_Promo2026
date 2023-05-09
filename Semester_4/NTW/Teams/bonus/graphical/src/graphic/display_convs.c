/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myteams-antoine.khalidy
** File description:
** display_convs
*/

#include "graphic.h"

void display_selected_conv(graphic_t *gra)
{
    sfRectangleShape* chat_box = sfRectangleShape_create();
    sfRectangleShape_setSize(chat_box, (sfVector2f) {900, 700});
    sfRectangleShape_setPosition(chat_box, (sfVector2f) {700, 100});
    sfRectangleShape_setFillColor(chat_box, sfWhite);
    sfRectangleShape_setOutlineColor(chat_box, sfBlack);
    sfRectangleShape_setOutlineThickness(chat_box, 2);
    sfRenderWindow_drawRectangleShape(gra->window, chat_box, NULL);
    sfText *text = sfText_create();
    sfText_setFont(text, gra->font);
    sfText_setCharacterSize(text, 20);
    sfText_setFillColor(text, sfBlack);
    sfText_setString(text, gra->selected_conv->name);
    sfText_setPosition(text, (sfVector2f) {710, 125});
    sfRenderWindow_drawText(gra->window, text, NULL);
    display_messages(gra);
}

void add_conv_at_end(graphic_t *gra, char *name)
{
    conv_t *new_conv = malloc(sizeof(conv_t));
    new_conv->name = name;
    new_conv->messages = NULL;
    new_conv->next = NULL;
    if (gra->conv_list == NULL) {
        gra->conv_list = new_conv;
        return;
    }
    conv_t *tmp = gra->conv_list;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_conv;
}

conv_t *get_conv_by_name(graphic_t *gra, char *name)
{
    conv_t *tmp = gra->conv_list;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

conv_t *get_conv_by_hitbox(graphic_t *gra, sfVector2f mouse)
{
    conv_t *tmp = gra->conv_list;

    while (tmp != NULL) {
        if (mouse.x >= sfRectangleShape_getPosition(tmp->hitbox).x
        && mouse.x <= sfRectangleShape_getPosition(tmp->hitbox).x +
        sfRectangleShape_getSize(tmp->hitbox).x && mouse.y >=
        sfRectangleShape_getPosition(tmp->hitbox).y && mouse.y <=
        sfRectangleShape_getPosition(tmp->hitbox).y +
        sfRectangleShape_getSize(tmp->hitbox).y)
            return tmp;
        tmp = tmp->next;
    }
    return gra->selected_conv;
}
