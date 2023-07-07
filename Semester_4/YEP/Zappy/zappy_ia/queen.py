from character import Character
from agent_getters import *
from maths import *

#Queens goal is to bring food to the king

class Queen(Character):
    def __init__(self, team, name="patate", ip="127.0.0.1", port=4242):
        super().__init__(team, "queen (" + name + ")", ip, port)
        self.nombre_de_queen_chiées = 0
        self.dir_tup = {
            HAUT: (0, -1),
            DROITE: (-1, 0),
            BAS: (0, -1),
            GAUCHE: (-1, 0)
        }
        self.run()

    def get_broadcast(self, message):
        return
    def get_food(self):
        return self.food
    
    def incantation(self, state="init"):
        print("incantation function", state)
        if state == "init":
            self.current_action.append("incantation")
            self.networkModule.sendMessage("incantation", self.name)
            return

        # print("oooh (%s) | Elevation underway" % (state))
        if state == "Elevation underway":
            print("i am : %s im in incantation" % (self.name))
            if self.current_action and self.current_action[0] != "incantation":
                self.current_action.insert(0, "incantation")
            return
        #ko
        if state == "ko":
            self.vision[(0, 0)].remove('linemate')
            #TODO : trouver pourquoi ca a fail
            self.current_action.pop(0)
            return
        #Current level:k
        self.level += 1
        self.got_objectives = False
        self.ready_to_join = False
        self.current_action.pop(0)

    def do_action(self):
        msg = self.fd_is_ready(self.networkModule.client)
        if msg != None:
            # print("queen received: [{}]".format(msg))
            for message in msg:
                result = self.handle_message(message)
                if result != None:
                    self.get_broadcast(result)
        if self.current_action:
            return
        # first the queen needs to get setup (level 2)
        if self.setup() == False:
            return
        if self.king_pos == (0, 0) and self.food > 5:
            self.drop("food")
        elif self.food < 10:
            self.search_some("food")
        else:
            self.join_king()

    def setup(self):
        if self.food > 1:
            self.drop("food")
            return False
        if self.nombre_de_queen_chiées == 0:
            self.nombre_de_queen_chiées = 1
            self.fork("queen")
            return False
        if self.food > 0:
            self.drop("food")
            return False
        self.move()
        return False
        if self.vision.get((0, 0)) is None:
            self.vision[(0, 0)] = []
        if self.level == 1:
            if 'linemate' in self.vision[(0, 0)] and self.king_pos != (0, 0):
                    self.incantation()
                    return False
            elif is_in_vision(self.vision, 'linemate') == True:
                self.go_to('linemate')
                return False
            else:
                self.searching_resource()
                return False
        return True

    def run(self):
        while self.is_alive:
            self.do_action()