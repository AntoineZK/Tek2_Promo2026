/*
** EPITECH PROJECT, 2023
** B-YEP-400-NCY-4-1-zappy-antoine.khalidy (Workspace)
** File description:
** command_object
*/

#include "zappy.h"

static bool is_inside(int x, int y, zone_object_t *obj)
{
    if (y == obj->y1 && x >= obj->x1)
        return (true);
    if (y == obj->y2 && x <= obj->x2)
        return (true);
    if (y > obj->y1 && y < obj->y2)
        return (true);
    return (false);
}

void update_ressource(res_type_t *obj, int x, int y)
{
    obj->is_changed = true;
    for (int i = 0; obj->item[i] != NULL; i++) {
        if (is_inside(x, y, obj->item[i])) {
            obj->item[i]->on = false;
            obj->item[i]->item_x = 0;
            obj->item[i]->item_y = 0;
            return;
        }
    }
}

void take_object(zappy_t *zap, client_t *tmp, char **cmd)
{
    take_food(zap, tmp, cmd);
}

void set_object(zappy_t *zap, client_t *tmp, char **cmd)
{
    set_food(zap, tmp, cmd);
}
