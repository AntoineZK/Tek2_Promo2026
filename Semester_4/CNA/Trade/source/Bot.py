##
## EPITECH PROJECT, 2023
## B-CNA-410-NCY-4-1-trade-yoan.gerard
## File description:
## Bot
##

## IMPORTS ##
from BotData import BotData

class Bot:
    def __init__(self):
        self.botData = BotData()

    def run(self):
        while True:
            data = input()
            if (len(data) == 0):
                continue
            self.parseData(data)

    def parseData(self, info: str):
        splitData = info.split(" ")
        if splitData[0] == "settings":
            self.botData.updateSettings(splitData[1], splitData[2])
        if splitData[0] == "update" and splitData[1] == "game":
            self.botData.updateGame(splitData[2], splitData[3])
        if splitData[0] == "action":
            self.botData.doAction()
