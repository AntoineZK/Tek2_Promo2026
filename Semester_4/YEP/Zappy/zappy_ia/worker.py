from character import Character
from agent_getters import *

#Queens goal is to bring food to the king

class Worker(Character):
    def __init__(self, team, name="patate", ip="127.0.0.1", port=4242):
        super().__init__(team, "worker (" + name + ")", ip, port)
        self.vision[(0, 0)] = ['thystame']
        self.searching_for = []
        self.taken_food = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0}
        self.joining_king = False
        self.ready_to_join = False
        self.started_forward = 0
        print("Worker created")
        self.need_to_start_evolve = False
        self.run()

    def get_food(self):
        return self.food

    def get_closest_searching_ressource(self):
        total_distance = 0
        closest = 100
        closest_ressource = None
        for ressource in self.searching_for:
            distance_to_ressource = get_closest_ressource(self.vision, ressource)
            if distance_to_ressource == None:
                continue
            for distance in distance_to_ressource:
                total_distance += distance
            if total_distance < closest:
                closest = total_distance
                closest_ressource = ressource
        return closest_ressource
    
    def is_setup(self):
        if self.started_forward < 2:
            self.started_forward += 1
            self.move()
            return False
        if self.vision.get((0, 0)) is None:
            self.vision[(0, 0)] = []
        if self.level == 1:
            if 'linemate' in self.vision[(0, 0)] and self.king_pos != (0, 0):
                    self.vision[(0, 0)].remove('linemate')
                    self.incantation()
                    return False
            elif is_in_vision(self.vision, 'linemate') == True:
                self.go_to('linemate')
                return False
            else:
                self.searching_resource()
                return False
        return True
    
    def get_broadcast(self, objective):
    # Objective example: "TEAM '1', GET ME SOME 'linemate' 'deraumere' 'sibur' 'linemate'"
    # Objective example2: "TEAM '1', JOIN KING"
    # Objective example3: "TEAM '1', LEVEL '2', EVOLVE"
    #Exemple message 1: "TEAM 1, LEVEL 2, I FOUND SOME LINEMATE !"
        print("Broadcast received: " + objective)
        team = objective.split("TEAM ")[1].split(",")[0]
        level = objective.split("LEVEL ")[1].split(",")[0].split(" ")[0]
        level = int(level)
        if team != self.team or level != self.level:
            return
        if "FOUND SOME" in objective:
            item = objective.split("FOUND SOME ")[1].split(" !")[0]
            item = item[0:-1]
            if item in self.searching_for:
                self.searching_for.remove(item)
            return
        if "JOIN" in objective:
            self.joining_king = True
            self.searching_for = []
            return
        if "EVOLVE " in objective:
            self.need_to_start_evolve = True
        if "GET ME SOME" in objective:
            self.got_objectives = True
            self.ready_to_join = False
            en_recherche = []
            resource_list = objective.split("GET ME SOME ")[1].split("'")
            for resource in resource_list:
                if resource.strip():  # Vérification si la ressource n'est pas une chaîne vide
                    en_recherche.append(resource.strip("'"))
            self.searching_for = en_recherche
            print("SEARCHING FOR: " + str(self.searching_for))


    def broadcast_to_king(self, item):
        message = "TEAM " + str(self.team) + "LEVEL " + str(self.level) + "I FOUND SOME " + item
        return super().broadcast(message)

    def do_action(self):
        msg = self.fd_is_ready(self.networkModule.client)
        if msg != None:
            # print("worker received: [{}]" .format(msg))
            for message in msg:
                result = self.handle_message(message)
                if result != None:
                    self.get_broadcast(result)
        if self.current_action:
            return
        # print("WORKER CHECK IF SETUP")
        if self.is_setup() == False:
            return
        #print("WORKER FOOD = {}".format(self.food))
        if self.need_to_start_evolve == True:
            self.need_to_start_evolve = False
            self.incantation()
        
        if 'food' in self.vision[(0, 0)] and self.king_pos != (0, 0):
            self.take("food")
            return
        # print("WORKER DO ACTION AFTER SETUP")
        if self.food < 5 and self.king_pos == (0, 0):
            self.take("food")
            return
        if self.food < 5 or self.got_objectives == False:
            self.search_some("food")
            return
        elif self.food > 5 and self.searching_for:
            # print("JE RECHERCHE ACTUELLEMENT: " + str(self.searching_for))
            ressource = self.get_closest_searching_ressource()
            # print("RESSOURCE LA PLUS PROCHE: " + str(ressource))
            if ressource == None:
                print("JE NAI PAS DE RESSOURCE DANS MA VISION ALORS JE CHECHE")
                self.searching_resource()
                return
            self.search_some(ressource)
        else:
            #TODO: bring ressource to king
            if self.king_pos == (0, 0):
                if self.inventory:
                    self.drop(self.inventory[0])
                else:
                    self.joining_king = False
                    if self.taken_food[self.level] < 20:
                        self.taken_food[self.level] += 1
                        self.take("food")
                        return
                    if self.waiting_for_evolve == False:
                        super().broadcast("TEAM " + str(self.team) + ", LEVEL " + str(self.level) + ", I'M HERE!")
                        self.waiting_for_evolve = True
                        return
                    if self.taken_food[self.level] < 40:
                        self.taken_food[self.level] += 1
                        self.take("food")
                        return
                    if self.level == 6:
                        if self.taken_food[self.level] < 40:
                            self.take("food")
            else:
                if self.food > 8:
                    self.ready_to_join = True
                if self.ready_to_join == False:
                    print("IL ME MANQUE DE LA FOOD AVANT DE REJOINDRE LE KING, LA FOOD QUE JAI: " + str(self.food))
                    self.search_some("food")
                print("I'M TRYING TO GO TO KING, HE IS AT" + str(self.king_pos))
                self.join_king()

    def run(self):
        while self.is_alive:
            self.do_action()
