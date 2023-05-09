/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** init
*/

#include "graphic.h"

sfText *create_text(char *str, sfVector2f pos, sfFont *font, int size)
{
    sfText *text = sfText_create();

    sfText_setString(text, str);
    sfText_setPosition(text, pos);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfRed);
    return text;
}

void initialise_graphic_two(graphic_t *gra)
{
    gra->clock = sfClock_create();
    gra->time = sfClock_getElapsedTime(gra->clock);
    gra->seconds = gra->time.microseconds / 1000000.0;
    gra->conv_list = NULL;
    gra->selected_conv = NULL;
}

static void test_message(graphic_t *gra)
{
    add_conv_at_end(gra, "Hitler");
    add_conv_at_end(gra, "Staline");
    add_conv_at_end(gra, "Mao");
    add_conv_at_end(gra, "Lenine");
    add_conv_at_end(gra, "Mussolini");
    gra->selected_conv = get_conv_by_name(gra, "Hitler");
    add_message_at_end_for_selected_conv(gra, "Hello", DEST);
    add_message_at_end_for_selected_conv(gra, "How are you ?", DEST);
    add_message_at_end_for_selected_conv(gra, "I'm fine, and you ?", USER);
    add_message_at_end_for_selected_conv(gra, "I'm fine too", USER);
    add_message_at_end_for_selected_conv(gra, "Ok, bye", USER);
    add_message_at_end_for_selected_conv(gra, "Bye", USER);
    gra->selected_conv = get_conv_by_name(gra, "Staline");
    add_message_at_end_for_selected_conv(gra, "Hello", DEST);
    add_message_at_end_for_selected_conv(gra, "Comment ca va connard ?", DEST);
    add_message_at_end_for_selected_conv(gra, "Je vais bien, et toi ?", USER);
}

graphic_t *init_graphic(void)
{
    graphic_t *gra = malloc(sizeof(graphic_t));
    sfVideoMode mode = {1920, 1080, 32};
    sfUint32 style = sfClose | sfResize;

    gra->window = sfRenderWindow_create(mode, "MyTeams", style, NULL);
    sfRenderWindow_setFramerateLimit(gra->window, 60);
    gra->view = sfView_createFromRect((sfFloatRect) {0, 0, 1920, 1080});
    sfView_setViewport(gra->view, (sfFloatRect) {0, 0, 1, 1});
    sfRenderWindow_setView(gra->window, gra->view);
    gra->font = sfFont_createFromFile("bonus/graphical/assets/arial.ttf");
    gra->inputMessage = create_text("_", (sfVector2f) {710, 905}, gra->font, 20);
    gra->input[0] = '\0';
    initialise_graphic_two(gra);
    test_message(gra);
    return gra;
}
