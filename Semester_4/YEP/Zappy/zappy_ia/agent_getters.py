import sys

def get_closest_ressource(vision:dict, ressource):
    closest_distance = sys.maxsize
    closest_coords = None
    
    for coords, items in vision.items():
        if ressource in items:
            x, y = coords
            distance = abs(x) + abs(y)
            
            if distance < closest_distance:
                closest_distance = distance
                closest_coords = coords
    
    if closest_coords is None:
        # print ('no ressource found')
        return None
    
    x, y = closest_coords
    left_distance = x
    right_distance = -x
    up_distance = y
    down_distance = -y

    if left_distance < 0:
        left_distance = 0
    if right_distance < 0:
        right_distance = 0
    if up_distance < 0:
        up_distance = 0
    if down_distance < 0:
        down_distance = 0
    
    return left_distance, right_distance, up_distance, down_distance

def get_player_case_items(vision):
    items = vision.get((0, 0))
    nbfood = 0
    nblinemate = 0
    nbderaumere = 0
    nbsibur = 0
    nbmendiane = 0
    nbphiras = 0
    nbthystame = 0

    if items is None:
        return 0, 0, 0, 0, 0, 0, 0
    for item in items:
        if item == 'food':
            nbfood += 1
        elif item == 'linemate':
            nblinemate += 1
        elif item == 'deraumere':
            nbderaumere += 1
        elif item == 'sibur':
            nbsibur += 1
        elif item == 'mendiane':
            nbmendiane += 1
        elif item == 'phiras':
            nbphiras += 1
        elif item == 'thystame':
            nbthystame += 1
    
    return nbfood, nblinemate, nbderaumere, nbsibur, nbmendiane, nbphiras, nbthystame

def is_in_vision(vision, ressource):
    for items in vision.values():
        if ressource in items:
            return True

    return False