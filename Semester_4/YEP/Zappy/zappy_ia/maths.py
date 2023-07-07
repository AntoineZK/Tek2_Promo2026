HAUT = 1
DROITE = 2
BAS = 3
GAUCHE = 4

SIZEX = 10
SIZEY = 10

def vision_torus(vision, sizeX, sizeY):
    update_vision = {}
    for coords, items in vision.items():
        x, y = coords

        if x > sizeX / 2 and x > 0:
            x = x - sizeX
        if y > sizeY / 2 and y > 0:
            y = y - sizeY

        if x < -sizeX / 2 and x < 0:
            x = x + sizeX
        if y < -sizeY / 2 and y < 0:
            y = y + sizeY

        update_vision[(x, y)] = items

    return update_vision


def rotate_vision(old_vision, direction, map_size):
    #update vision quand le personnage tourne
    new_vision = {}

    if direction == "Left":
        for coords, items in old_vision.items():
            new_x = coords[1]
            new_y = -coords[0]
            new_coords = (new_x, new_y)
            new_vision[new_coords] = items
    elif direction == "Right":
        for coords, items in old_vision.items():
            new_x = -coords[1]
            new_y = coords[0]
            new_coords = (new_x, new_y)
            new_vision[new_coords] = items

    return vision_torus(new_vision, map_size["x"], map_size["y"])

def update_vision(old_vision, direction):
    #update vision quand le personnage avance de 1
    new_vision = {}

    for coords, items in old_vision.items():
        x, y = coords
        new_coords = (x, y - 1)
        new_vision[new_coords] = items
        
    return new_vision

def get_vision(level):

    if level == 1:
        return [(0, 0), (-1, 1), (0, 1), (1, 1)]
    elif level == 2:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2), (-1, 2), (0, 2), (1, 2), (2, 2)]
    elif level == 3:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2),(-1, 2), (0, 2), (1, 2), (2, 2),
                (-3, 3), (-2, 3), (-1, 3), (0, 3), (1, 3), (2, 3), (3, 3)]
    elif level == 4:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2), (-1, 2), (0, 2), (1, 2), (2, 2),
                (-3, 3), (-2, 3), (-1, 3), (0, 3), (1, 3), (2, 3), (3, 3),
                (-4, 4), (-3, 4), (-2, 4), (-1, 4), (0, 4), (1, 4), (2, 4), (3, 4), (4, 4)]
    elif level == 5:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2), (-1, 2), (0, 2), (1, 2), (2, 2),
                (-3, 3), (-2, 3), (-1, 3), (0, 3), (1, 3), (2, 3), (3, 3),
                (-4, 4), (-3, 4), (-2, 4), (-1, 4), (0, 4), (1, 4), (2, 4), (3, 4), (4, 4),
                (-5, 5), (-4, 5), (-3, 5), (-2, 5), (-1, 5), (0, 5), (1, 5), (2, 5), (3, 5), (4, 5), (5, 5)]
    elif level == 6:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2), (-1, 2), (0, 2), (1, 2), (2, 2),
                (-3, 3), (-2, 3), (-1, 3), (0, 3), (1, 3), (2, 3), (3, 3),
                (-4, 4), (-3, 4), (-2, 4), (-1, 4), (0, 4), (1, 4), (2, 4), (3, 4), (4, 4),
                (-5, 5), (-4, 5), (-3, 5), (-2, 5), (-1, 5), (0, 5), (1, 5), (2, 5), (3, 5), (4, 5), (5, 5),
                (-6, 6), (-5, 6), (-4, 6), (-3, 6), (-2, 6), (-1, 6), (0, 6), (1, 6), (2, 6), (3, 6), (4, 6), (5, 6), (6, 6)]
    elif level == 7:
        return [(0, 0), (-1, 1), (0, 1), (1, 1),
                (-2, 2), (-1, 2), (0, 2), (1, 2), (2, 2),
                (-3, 3), (-2, 3), (-1, 3), (0, 3), (1, 3), (2, 3), (3, 3),
                (-4, 4), (-3, 4), (-2, 4), (-1, 4), (0, 4), (1, 4), (2, 4), (3, 4), (4, 4),
                (-5, 5), (-4, 5), (-3, 5), (-2, 5), (-1, 5), (0, 5), (1, 5), (2, 5), (3, 5), (4, 5), (5, 5),
                (-6, 6), (-5, 6), (-4, 6), (-3, 6), (-2, 6), (-1, 6), (0, 6), (1, 6), (2, 6), (3, 6), (4, 6), (5, 6), (6, 6),
                (-7, 7), (-6, 7), (-5, 7), (-4, 7), (-3, 7), (-2, 7), (-1, 7), (0, 7), (1, 7), (2, 7), (3, 7), (4, 7), (5, 7), (6, 7), (7, 7)]

def character_vision_to_map_vision(character_vision):
    new_dictionary = {}
    for key, value in character_vision.items():
        new_key = (key[0], -key[1])  # Mettre à jour le y en multipliant par -1
        new_dictionary[new_key] = value
    return new_dictionary

def change_y_vision(vision):
    # Mettre à jour le y en multipliant par -1
    #vision = ((x, y), (x, y), (x, y), (x, y))
    new_vision = []
    for coords in vision:
        new_coords = (coords[0], -coords[1])
        new_vision.append(new_coords)
    return new_vision

def total_workers(workers):
    nb_workers = 0
    for value in workers.values():
        nb_workers += value
    return nb_workers

def update_king_pos(king_pos: tuple, direction):
    # king_pos = (x, y) par rapport au worker
    if direction == HAUT:
        king_pos = (king_pos[0], king_pos[1] - 1)
    elif direction == "Right":
        king_pos = (king_pos[1], -king_pos[0])
    elif direction == "Left":
        king_pos = (-king_pos[1], king_pos[0])
    return king_pos
