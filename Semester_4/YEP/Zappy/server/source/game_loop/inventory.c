/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** inventory
*/

#include "zappy.h"

invent_t *init_invent(void)
{
    invent_t *stuff = malloc(sizeof(invent_t));
    stuff->food = 0;
    stuff->linemate = 0;
    stuff->deraumere = 0;
    stuff->sibur = 0;
    stuff->mendiane = 0;
    stuff->phiras = 0;
    stuff->thystame = 0;
    return (stuff);
}

void inventory_command(zappy_t *zappy, client_t *client, char **cmd)
{
    (void)cmd;
    (void)zappy;
    invent_t *inventory = client->player->inventory;
    char *str = alloca(sizeof(char) * 100);
    char *str2 = alloca(sizeof(char) * 100);
    sprintf(str, "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d,",
    inventory->food, inventory->linemate, inventory->deraumere,
    inventory->sibur, inventory->mendiane);
    sprintf(str2, " phiras %d, thystame %d]\n",
    inventory->phiras, inventory->thystame);
    update_wbuffer(client, str);
    update_wbuffer(client, str2);
}

int write_item_invent(int nb, char *str, int i, client_t *client)
{
    if (nb == 0)
        return (i);
    int size = strlen(str);
    char word[size + 2];
    word[0] = ' ';
    word[size + 1] = '\0';
    for (int j = 0; j < size; j++)
        word[j + 1] = str[j];
    for (int j = 0; j < nb; j++) {
        if (i != 0)
            update_wbuffer(client, word);
        else
            update_wbuffer(client, str);
        i++;
    }
    return (i);
}

void look_till_inventory(invent_t *invent, client_t *client, int nb)
{
    nb = write_item_invent(invent->food, "food", nb, client);
    nb = write_item_invent(invent->linemate, "linemate", nb, client);
    nb = write_item_invent(invent->deraumere, "deraumere", nb, client);
    nb = write_item_invent(invent->sibur, "sibur", nb, client);
    nb = write_item_invent(invent->mendiane, "mendiane", nb, client);
    nb = write_item_invent(invent->phiras, "phiras", nb, client);
    write_item_invent(invent->thystame, "thystame", nb, client);
}
