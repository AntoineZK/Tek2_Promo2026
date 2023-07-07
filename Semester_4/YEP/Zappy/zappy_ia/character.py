import random
# import pygame
import sys
from maths import *
from constants import *
from client import NetworkAgent
import select
import os
import time
# from worker import Worker
# from queen import Queen
# from king import King
from agent_getters import *
# from fork import start_new_ia

RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"

class Character():
    def __init__(self, team, name, ip="127.0.0.1", port=4242):
        self.searching_state = 0
        self.workers_in_team = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0}
        self.queens_in_team = 0
        self.vision = {(0, 0): []}
        self.name = name
        self.king_pos = (0, 0)
        self.got_objectives = False
        self.ready_to_join = False
        

        self.x = 0
        self.y = 0
        self.level = 1
        self.direction = random.randint(1, 4)
        self.team = team
        self.food = 10
        self.linemate = 0
        self.deraumere = 0
        self.inventory = []
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
        self.doing_something = 0
        self.nb_workers = 0
        self.networkModule = NetworkAgent(team, ip, port)
        message = self.networkModule.receiveMessage()
        print(message)
        self.networkModule.sendMessage(team, name)
        data = self.networkModule.receiveMessage()
        self.id = int(data[0])
        print("id: ", self.id)
        tmp = data[1].split(" ")
        self.map_size = {
            "x": int(tmp[0]),
            "y": int(tmp[1])
        }
        print("map_size: ", self.map_size)
        self.response_by_action = {
            "take": ["ok", "ko"],
            "drop": ["ok", "ko"],
            "forward": ["ok"],
            "turn": ["ok"],
            "look": ["*"],
            "inventory": ["*"],
            "incantation": ["Elevation underway", "ko", "Current level:"],
            "fork": ["ok"],
            "broadcast": ["ok"],
            "eject": ["ok", "ko"],
        }
        self.last_params = {
            "rotate": "",
            "take": "",
            "drop": "",
            "fork": "",
            "incantation": "",
        }
        self.current_action = []
        self.is_alive = True

    def get_position(self):
        return (self.x, self.y)

    def get_inventory(self):
        return (self.food, self.linemate, self.deraumere, self.sibur, self.mendiane, self.phiras, self.thystame)

    def get_vision(self):
        return self.vision

    def get_direction(self):
        return self.direction

    def add_food(self, food):
        self.food += food

    def remove_food(self, food):
        self.food -= food

    def searching_resource(self):
        if self.searching_state == 0:
            self.look()
            self.searching_state = 1
            return
        if self.searching_state == 1 or self.searching_state == 2:
            self.move()
            self.searching_state += 1
            return
        if self.searching_state == 3:
            self.look()
            self.searching_state = 4
            return
        if self.searching_state == 4:
            random_turn = random.randint(0, 1)
            if random_turn == 0:
                self.turn("Left")
            else:
                self.turn("Right")
            self.searching_state = 0
            return

    def move(self, state="init"):
        if state == "init":
            self.current_action.append("forward")
            self.networkModule.sendMessage("Forward", self.name)
            self.king_pos = update_king_pos(self.king_pos, HAUT)
            self.vision = update_vision(self.vision, HAUT)
            return

    def turn(self, direction: str, state="init"):
        if state != "init":
            self.king_pos = update_king_pos(self.king_pos, direction)
            self.vision = rotate_vision(self.vision, direction, self.map_size)
            return
        self.current_action.append("turn")
        self.networkModule.sendMessage(direction, self.name)
        self.last_params["rotate"] = direction

    def take(self, item, state="init"):
        if state == "init":
            self.networkModule.sendMessage("Take " + item, self.name)
            self.current_action.append("take")
            self.last_params["take"] = item
            return
        if state == "ko":
            #ECHEC
            if item in self.vision[(0, 0)]:
                self.vision[(0, 0)].remove(item)
            return
        #SUCCES
        if item == 'food':
            self.food += 1
            if item in self.vision[(0, 0)]:
                self.vision[(0, 0)].remove(item)
            self.current_action.pop(0)
            # print("J'AI TANT DE BOUFFE : " + str(self.food))
            return
        self.inventory.append(item)
        # print("MON INVENTAIRE ACTUEL: ", self.inventory)
        self.vision[(0, 0)].remove(item)
        self.current_action.pop(0)
        self.broadcast("TEAM " + self.team + ", LEVEL " + str(self.level) + ", I FOUND SOME " + item + "!")
        return

    def drop(self, item, state="init"):
        if state == "init":
            self.current_action.append("drop")
            self.networkModule.sendMessage("Set " + item, self.name)
            self.last_params["drop"] = item
            return
        #ECHEC
        if state == "ko":
            while item in self.inventory:
                self.inventory.remove(item)
            return
        #SUCCES
        if item == 'food':
            self.food -= 1
        if item in self.inventory:
            self.inventory.remove(item)
            # print("MON INVENTAIRE APRES DROP: ", self.inventory)

    def look(self, state="init"):
        if state == "init":
            self.current_action.append("look")
            self.networkModule.sendMessage("Look", self.name)
            return
        #SUCCES
        state = state.replace("[", "").replace("]", "").replace("\n", "")
        state = state.split(',')
        i = 0
        j = 0
        for case in state:
            components_by_case = case.split(' ')
            if i == j + 1:
                i = -i
                j += 1
            # print("i am : %s case: %s in (%d, %d)" % (self.id, components_by_case, i, j))
            self.vision[(i, j)] = components_by_case
            i += 1
        # for key, value in self.vision.items():
        #     print(key, value)

    def broadcast(self, message, state="init"):
        # print("broadcast function")
        if state == "init":
            self.current_action.append("broadcast")
            # print("i am : %s i broadcast: %s" % (self.name, message))
            self.last_params["broadcast"] = message
            self.networkModule.sendMessage("Broadcast " + message, self.name)
            return
        if state == "ko":
            #ECHEC
            self.current_action.pop(0)
            return

    def eject(self, state="init"):
        # print("eject function")
        if state == "init":
            self.current_action.append("eject")
            self.networkModule.sendMessage("Eject", self.name)
            return
        if state == "ko":
            #ECHEC
            return
        print("i am : %s i eject" % (self.name))

    def fork(self, ia_type="worker", state="init"):
        # print("fork function")
        if state == "init":
            self.current_action.append("fork")
            self.networkModule.sendMessage("Fork", self.name)
            self.last_params["fork"] = ia_type
            return
        self.start_new_ia(ia_type, self.team, self.networkModule.port, self.networkModule.server)
        # print("i am : %s i fork: %s" % (self.name, ia_type))

    def can_evolve(self, map):
        if (self.doing_something != 0):
            return
        if (self.level == 1):
            # print("i am : %s i can evolve" % (self.name), map.get_case(self.x, self.y).get_items())
            for item in map.get_case(self.x, self.y).get_items():
                if item == 'linemate':
                    return 1

    def incantation(self, state="init"):
        print("incantation function", state)
        if state == "init":
            self.current_action.append("incantation")
            self.networkModule.sendMessage("incantation", self.name)
            return

        # print("oooh (%s) | Elevation underway" % (state))
        if state == "Elevation underway":
            print("i am : %s im in incantation" % (self.name))
            if not self.current_action or (self.current_action and self.current_action[0] != "incantation"):
                self.current_action.insert(0, "incantation")
            return
        #ko
        if state == "ko":
            if self.vision.get((0, 0)) is None:
                self.vision[(0, 0)] = []
            if self.level == 1 and 'linemate' in self.vision[(0, 0)]:
                self.vision[(0, 0)].remove('linemate')
            #TODO : trouver pourquoi ca a fail
            if self.current_action and self.current_action[0] == "incantation":
                self.current_action.pop(0)
            return
        #Current level: k
        self.level = int(state.split(":")[1].strip())
        self.got_objectives = False
        self.ready_to_join = False
        self.waiting_for_evolve = False
        if (self.current_action and self.current_action[0] == "incantation"):
            self.current_action.pop(0)
        self.broadcast("TEAM " + self.team + ", LEVEL " + str(self.level) + " I EVOLVED!")

    def fd_is_ready(self, socket):
        rlist, _, _ = select.select([socket], [], [], 0.01)
        if socket in rlist:
            return self.networkModule.receiveMessage()
        return None

    def check_string_in_array(self, input_string, string_array):
        for string in string_array:
            if string in input_string:
                return True
        return False

    def handle_message(self, msg: str):
        if "victory" in msg or "defeat" in msg:
            if "victory" in msg:
                print(GREEN + "On est trop fort en fait" + RESET)
            else:
                print(RED + "On a perdu defaite" + RESET)
            sys.exit(0)
        if "queen" not in self.name:
            print("i am : %s i received: %s and i am doing: %s" % (self.name + " (" + str(self.level) + ")", msg, self.current_action))

        if "message" in msg:
            if (self.current_action and self.current_action[0] == "broadcast") and self.last_params["broadcast"] in msg:
                self.current_action.pop(0)
            return msg
        elif "Current level:" in msg:
            self.incantation(msg)
            if self.current_action and self.current_action[0] == "incantation":
                self.current_action.pop(0)
        elif self.current_action and (self.check_string_in_array(msg, self.response_by_action[self.current_action[0]]) == True or self.current_action[0] == "look"):
            tmp_action = self.current_action[0]
            self.execute_action_by_response(msg)
            if not self.current_action:
                return None
            if tmp_action == self.current_action[0] and self.current_action[0] != "incantation":
                self.current_action.pop(0)
        elif "dead" in msg:
            self.is_alive = False
        return None

    def execute_action_by_response(self, msg: str):
        if not self.current_action:
            return
        if self.current_action[0] == "take":
            self.take(self.last_params["take"], msg)
        elif self.current_action[0] == "drop":
            self.drop(self.last_params["drop"], msg)
        elif self.current_action[0] == "incantation":
            self.incantation(msg)
        elif self.current_action[0] == "eject":
            self.eject(msg)
        elif self.current_action[0] == "fork":
            self.fork(self.last_params["fork"], msg)
        elif self.current_action[0] == "broadcast":
            self.broadcast("", msg)
        elif self.current_action[0] == "look":
            self.look(msg)
        elif self.current_action[0] == "turn":
            self.turn(self.last_params["rotate"], msg)
        return

    def start_new_ia(self, ia_type, team, port, ip):
        child_pid = os.fork()

        if child_pid != 0:
            if ia_type == "worker":
                self.workers_in_team[1] += 1
                self.nb_workers += 1
            elif ia_type == "queen":
                self.queens_in_team += 1
            return

        os.setsid()

        if ia_type == "worker":
            print("start worker")
            os.system("python3 agent.py -n " + team + " -p " + str(port) + " -h " + ip + " -ia worker -name " + str(self.nb_workers))
            # Worker(team, "child", port, ip)
        elif ia_type == "king":
            print("start king")
            os.system("python3 agent.py -n " + team + " -p " + str(port) + " -h " + ip + " -ia king")
            # King(team, "child", port, ip)
        elif ia_type == "queen":
            print("start queen")
            os.system("python3 agent.py -n " + team + " -p " + str(port) + " -h " + ip + " -ia queen -name " + str(self.queens_in_team))
            # Queen(team, "child", port, ip)
        sys.exit(0)

    def go_to(self, ressource):
        distance = get_closest_ressource(self.vision, ressource)
        #Distance = (left, right, up, down)
        distance_right = distance[1]
        distance_up = distance[2]
        if distance == None:
            self.searching_resource()
        elif distance[0] == 0 and distance[1] == 0 and distance[2] == 0 and distance[3] == 0:
            return True
        else:
            if distance_up > 0:
                print(self.vision)
                self.move()
                return False
            else:
                if distance_right > 0:
                    self.turn("Left")
                    return False
                else:
                    self.turn("Right")
                    return False

    def search_some(self, ressource):
        # print("Self.vision : ", self.vision)
        distance = get_closest_ressource(self.vision, ressource)
        if distance == None:
            self.searching_resource()
            return
        #Distance = (left, right, up, down)
        distance_right = distance[1]
        distance_up = distance[2]
        if distance[0] == 0 and distance[1] == 0 and distance[2] == 0 and distance[3] == 0:
            if self.king_pos != (0, 0):
                self.take(ressource)
            else:
                self.vision[(0, 0)].remove(ressource)
                self.move()
        else:
            if distance_up > 0:
                self.move()
            else:
                if distance_right > 0:
                    self.turn("Left")
                else:
                    self.turn("Right")

    def join_king(self):
        distance_to_king_up = self.king_pos[1]
        distance_to_king_right = self.king_pos[0]
        if distance_to_king_up > 0:
            self.move()
        else:
            if distance_to_king_right > 0:
                self.turn("Left")
            else:
                self.turn("Right")
