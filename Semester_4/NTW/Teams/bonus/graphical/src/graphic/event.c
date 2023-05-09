/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** event
*/

#include "graphic.h"

void event_text_input(graphic_t *gra)
{
    if (gra->event.type == sfEvtTextEntered) {
        if (gra->event.text.unicode == 8 && strlen(gra->input) > 0) {
            gra->input[strlen(gra->input) - 1] = '\0';
        } else if (gra->event.text.unicode < 128
        && gra->event.text.unicode != 13) {
            strncat(gra->input, (char*)&gra->event.text.unicode, 1);
        }
        sfText_setString(gra->inputMessage, gra->input);
    }
}

void event_manager(general_t *g)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(g->graphic->window);
    sfVector2f viewMouse = sfRenderWindow_mapPixelToCoords(g->graphic->window,
    mouse, g->graphic->view);

    if (g->graphic->event.type == sfEvtClosed)
        sfRenderWindow_close(g->graphic->window);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(g->graphic->window);
    if (g->graphic->event.type == sfEvtKeyPressed &&
    g->graphic->event.key.code == sfKeyReturn) {
        char *tmp = g->graphic->input;
        if (strlen(tmp) > 0)
            g->network->header = create_header(tmp);
        sfText_setString(g->graphic->inputMessage, "_");
        g->graphic->input[0] = '\0';
    }
    event_text_input(g->graphic);
    if (g->graphic->event.type == sfEvtMouseButtonReleased) {
        g->graphic->selected_conv = get_conv_by_hitbox(g->graphic, viewMouse);
    }
}
