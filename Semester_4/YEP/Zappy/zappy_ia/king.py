from character import Character
from agent_getters import *
from constants import *
from maths import *
#Queens goal is to bring food to the king

class King(Character):
    def __init__(self, team, name="patate", ip="127.0.0.1", port=4242):
        super().__init__(team, "king", ip, port)
        print("King created")
        self.vision[(0, 0)] = []
        self.spawned_queen = 0
        self.worker_fork_at_level_3 = 0
        self.worker_fork_at_level_5 = 0
        self.have_look = 0
        self.worker_fork_at_level_6 = 0
        self.ressources_by_level = {
            2: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            3: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            4: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            5: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            6: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            7: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            8: {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
        }
        self.characters_on_king_by_level = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6:0, 7: 0}
        self.is_level_evolving = {
            2: False,
            3: False,
            4: False,
            5: False,
            6: False,
            7: False,
        }
        self.must_give_objectives = {
            1: False,
            2: False,
            3: False,
            4: False,
            5: False,
            6: False,
            7: False,
        }
        self.joining_asked = {
            1: False,
            2: False,
            3: False,
            4: False,
            5: False,
            6: False,
            7: False
        }
        #self.cjaracters_on_king = {'level': number}, example {'1': 2, '2': 1, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0}
        self.run()

    def has_enough_ressources(self, level):
        for ressource in self.ressources_by_level[level]:
            if self.ressources_by_level[level][ressource] < ressources_to_evolve[level + 1][ressource]:
                return False
        return True

    def has_enough_members(self):
        if self.queens_in_team < character_needed_at_level[self.level]['queen']:
            return "queen"
        if total_workers(self.workers_in_team) < character_needed_at_level[self.level]['worker']:
            return "worker"
        return "OK"

    def get_needed_ressources_to_evolve_by_level(self, level):
        needed_ressources = []
        ressources_by_level = self.ressources_by_level[level]
        total_ressources_needed_to_evolve = ressources_to_evolve[level + 1]

        #ressources_by_level = {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
        #total_ressources_needed_to_evolve = {'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0}

        for ressource in ressources_by_level:
            diff = total_ressources_needed_to_evolve[ressource] - ressources_by_level[ressource]
            for i in range(diff):
                needed_ressources.append(ressource)
        return needed_ressources

    def is_setup(self):
        if self.vision.get((0, 0)) is None:
            self.vision[(0, 0)] = []
        if self.level == 1:
            if 'linemate' in self.vision[(0, 0)]:
                if self.spawned_queen < 2:
                    self.fork("queen")
                    self.spawned_queen += 1
                    return False
                if self.has_enough_members() == "OK":
                    self.incantation()
                    return False
                else:
                    print("-------------------- king fork 1: {} --------------------".format(self.has_enough_members()))
                    self.fork(self.has_enough_members())
                    return False
            elif is_in_vision(self.vision, 'linemate'):
                self.go_to('linemate')
                return False
            else:
                self.searching_resource()
                return False
        if self.level == 4 and self.worker_fork_at_level_3 < 2:
            self.worker_fork_at_level_3 += 1
            # print("JE SUIS LEVEL 3 JE FORK UN WORKER")
            self.fork('worker')
            return False
        
        if self.level == 5 and self.worker_fork_at_level_5 < 2:
            self.worker_fork_at_level_5 += 1
            self.fork('worker')
            return False

        if self.level == 6 and self.worker_fork_at_level_6 < 2 and self.workers_in_team[4] > 0:
            self.worker_fork_at_level_6 += 1
            self.fork('worker')
            return False

        return True

    def get_broadcast(self, message):
        # print("King broadcast received: {}".format(message))
        if message.startswith("FROM KING"):
            return
        #Exemple message 1: "TEAM 1, LEVEL 2, I FOUND SOME LINEMATE !"
        #Exemple message 2: "TEAM 1, LEVEL 3, I EVOLVED !"
        team = message.split("TEAM ")[1].split(",")[0]
        level = message.split("LEVEL ")[1].split(",")[0].split(" ")[0]
        level = int(level)
        if team != self.team:
            return
        if "I'M HERE" in message:
            self.characters_on_king_by_level[level] += 1
        if "FOUND SOME" in message:
            item = message.split("FOUND SOME ")[1].split(" !")[0]
            item = item[0:-1]
            self.ressources_by_level[level][item] += 1
        if "EVOLVED" in message:
            self.is_level_evolving[level - 1] = False
            self.must_give_objectives[level] = True
            # print("JE DOIS DONNER DES OBJECTIFS AUX LEVEL " + str(level))
            self.characters_on_king_by_level[level - 1] = 0
            self.ressources_by_level[level - 1] = {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
            self.workers_in_team[level] += 1
            self.workers_in_team[level - 1] -= 1


    def team_has_enough_resources(self, level):
        if self.ressources_by_level[level]['linemate'] < ressources_to_evolve[level + 1]['linemate'] and self.ressources_by_level[level]['deraumere'] < ressources_to_evolve[level + 1]['deraumere'] and self.ressources_by_level[level]['sibur'] < ressources_to_evolve[level + 1]['sibur'] and self.ressources_by_level[level]['mendiane'] < ressources_to_evolve[level + 1]['mendiane'] and self.ressources_by_level[level]['phiras'] < ressources_to_evolve[level + 1]['phiras'] and self.ressources_by_level[level]['thystame'] < ressources_to_evolve[level + 1]['thystame']:
            return False
        return True

    def do_action(self):
        msg = self.fd_is_ready(self.networkModule.client)
        if msg != None:
            # print("King received: [{}]".format(msg))
            for message in msg:
                result = self.handle_message(message)
                if result != None:
                    self.get_broadcast(result)
        if self.current_action:
            return
        if self.is_setup() == False:
            return
        if self.food < 20:
            self.take("food")
            return

        for key,value in self.characters_on_king_by_level.items():
            if key == self.level:
                value += 1
            # if self.level == 6 and value >= workers_to_evolve[7] and self.team_has_enough_resources(6):
            #     if self.have_look == 0:
            #         self.have_look = 1
            #         self.look()
            #         return
            #     else:
            #         print("KING VISION LEVEL 6")
            #         print(RED + str(self.vision[(0, 0)]) + RESET)
            #         self.incantation()
            #         return

            if value >= workers_to_evolve[key + 1] and self.team_has_enough_resources(key) and self.is_level_evolving[key] == False:
                self.broadcast("FROM KING, TEAM " + self.team + ", LEVEL " + str(key) + ", YOU CAN EVOLVE !")
                self.is_level_evolving[key] = True
                return
        for key,value in self.workers_in_team.items():
            if self.must_give_objectives[key] == True:
                message = "FROM KING, TEAM " + self.team + ", LEVEL " + str(key) + ", GET ME SOME "
                needed_ressources = self.get_needed_ressources_to_evolve_by_level(key)
                for ressource in needed_ressources:
                    message += "'"+ ressource + "' "
                self.broadcast(message)
                self.must_give_objectives[key] = False
                return
        for key,value in self.workers_in_team.items():
            if value > 0:
                needed_ressources = self.get_needed_ressources_to_evolve_by_level(key)
                if needed_ressources == [] and self.joining_asked[key] == False:
                    self.broadcast("FROM KING, TEAM " + self.team + ", LEVEL " + str(key) + ", JOIN ME!")
                    self.joining_asked[key] = True
                    return
        if self.food < 400:
            self.take("food")
        return

    def run(self):
        while self.is_alive:
            self.do_action()