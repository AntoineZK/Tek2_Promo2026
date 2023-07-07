HAUT = 1
DROITE = 2
BAS = 3
GAUCHE = 4

ressources_to_evolve = {
    2: {'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
    3: {'linemate': 2, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
    4: {'linemate': 2, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
    5: {'linemate': 2, 'deraumere': 2, 'sibur': 3, 'mendiane': 1, 'phiras': 2, 'thystame': 0},
    6: {'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
    7: {'linemate': 2, 'deraumere': 3, 'sibur': 4, 'mendiane': 0, 'phiras': 4, 'thystame': 0},
    8: {'linemate': 4, 'deraumere': 4, 'sibur': 4, 'mendiane': 4, 'phiras': 4, 'thystame': 1}
}

character_needed_at_level = {
    1: {'queen': 0, 'worker': 1},
    2: {'queen': 1, 'worker': 1},
    3: {'queen': 1, 'worker': 3},
    4: {'queen': 1, 'worker': 3},
    5: {'queen': 1, 'worker': 7},
    6: {'queen': 1, 'worker': 7},
    7: {'queen': 1, 'worker': 7},
}

workers_to_evolve = {
    2: 1,
    3: 2,
    4: 2,
    5: 4,
    6: 4,
    7: 6,
    8: 6
}

reverse_tuple_move = {
    HAUT: (0, 1),
    BAS: (0, -1),
    GAUCHE: (1, 0),
    DROITE: (-1, 0)
}