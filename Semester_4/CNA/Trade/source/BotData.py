##
## EPITECH PROJECT, 2023
## B-CNA-410-NCY-4-1-trade-yoan.gerard
## File description:
## BotData
##

import sys
from Candle import Candle

def calculateAverage(nbAverage: int, candlesList):
    average = 0
    for i in range(nbAverage):
        average += candlesList[-i].close
    return average / nbAverage

def calculateAffordable(currency: str, stacks, candlesList):
    if currency == "USDT":
        return stacks[currency] / candlesList[-1].close
    else:
        return stacks[currency]


class BotData:
    def __init__(self):
        self.playerNames = ""
        self.timeBank = 0
        self.maxTimeBank = 0
        self.timePerMove = 1
        self.candleInterval = 1
        self.candleFormat = []
        self.candlesTotal = 0
        self.candlesGiven = 0
        self.initialStack = 0
        self.transactionFee = 0.1
        self.candlesList = []
        self.stacks = dict()
        self.lastAction = ""
        self.rsi = -100

    def updateSettings(self, key: str, value):
        if key == "player_names":
            self.playerNames = value
        if key == "timebank":
            self.maxTimeBank = int(value)
            self.timeBank = int(value)
        if key == "time_per_move":
            self.timePerMove = int(value)
        if key == "candle_interval":
            self.candleInterval = int(value)
        if key == "candle_format":
            self.candleFormat = value.split(",")
        if key == "candles_total":
            self.candlesTotal = int(value)
        if key == "candles_given":
            self.candlesGiven = int(value)
        if key == "initial_stack":
            self.initialStack = int(value)
        if key == "transaction_fee_percent":
            self.transactionFee = float(value)

    def updateStacks(self, key: str, value: float):
        self.stacks[key] = value

    def updateGame(self, key: str, value: str):
        if key == "next_candles":
            candleData = Candle(self.candleFormat, value)
            self.candlesList.append(candleData)
        if key == "stacks":
            currencyName = value.split(",")
            for stack in currencyName:
                currencyValue = stack.split(":")
                self.updateStacks(currencyValue[0], float(currencyValue[1]))
            print(f"All currency\n {self.stacks}", file=sys.stderr)

    def allIn(self):
        bigAverage = calculateAverage(100, self.candlesList)
        smallAverage = calculateAverage(25, self.candlesList)
        print(f'bigAverage {bigAverage} smallAverage {smallAverage}', file=sys.stderr)
        if smallAverage > bigAverage:
            if self.lastAction == "BUY":
                print("no_moves", flush=True)
            else:
                self.lastAction = "BUY"
                affordable = calculateAffordable("USDT", self.stacks, self.candlesList)
                print(f'buy USDT_BTC {affordable}', flush=True)
        else:
            if self.lastAction == "SELL":
                print("no_moves", flush=True)
            else:
                self.lastAction = "SELL"
                affordable = calculateAffordable("BTC", self.stacks, self.candlesList)
                if affordable <= 0.0:
                    print("no_moves", flush=True)
                else:
                    print(f'sell USDT_BTC {affordable}', flush=True)

    def standDeviation(self):
        n = len(self.candlesList)
        mean = sum([candle.close for candle in self.candlesList]) / n
        squared_diff_list = [(candle.close - mean)**2 for candle in self.candlesList]
        mean = sum(squared_diff_list) / n
        std_dev = mean ** 0.5
        return std_dev

    def bollingerBands(self):
        midBand = calculateAverage(20, self.candlesList)
        standardDeviation = self.standDeviation()

        band_width = 1.6

        upperBand = midBand + (band_width * standardDeviation)
        lowerBand = midBand - (band_width * standardDeviation)

        currentPrice = self.candlesList[-1].close
        print(f"currentPrice {currentPrice} upperBand {upperBand} lowerBand {lowerBand}", file=sys.stderr)
        if currentPrice > upperBand:
            if self.lastAction == "SELL":
                print("no_moves", flush=True)
            else:
                self.lastAction = "SELL"
                affordable = calculateAffordable("BTC", self.stacks, self.candlesList)
                if affordable <= 0.0:
                    print("no_moves", flush=True)
                else:
                    print(f'sell USDT_BTC {affordable}', flush=True)
        elif currentPrice <= lowerBand:
            if self.lastAction == "BUY":
                print("no_moves", flush=True)
            else:
                self.lastAction = "BUY"
                affordable = calculateAffordable("USDT", self.stacks, self.candlesList)
                print(f'buy USDT_BTC {affordable}', flush=True)
        else:
            print("no_moves", flush=True)

    # def doAction(self):
    #     self.bollingerBands()

    def calculateRSI(self):
        if len(self.candlesList) < 15:
            return None

        candles = self.candlesList[-15:]  # Select the last 15 candles for RSI calculation

        gains = []
        losses = []
        for i in range(1, len(candles)):
            prevClose = candles[i - 1].close
            currClose = candles[i].close
            diff = currClose - prevClose

            if diff > 0:
                gains.append(diff)
                losses.append(0)
            else:
                gains.append(0)
                losses.append(abs(diff))

        avgGain = sum(gains) / 14
        avgLoss = sum(losses) / 14

        if avgLoss == 0:
            rsi = 100
        else:
            rs = avgGain / avgLoss
            rsi = 100 - (100 / (1 + rs))

        return rsi

    #def doAction(self):
    #    # rsi = self.calculateRSI()
    #    # if self.rsi is -100:
    #    #     self.rsi = rsi
    #    bigAverage = calculateAverage(10, self.candlesList))
    #    smallAverage = calculateAverage(25, self.candlesList)
    #    # print("BUY rsi = ", rsi, file=sys.stderr)
    #    print(f'bigAverage {bigAverage} smallAverage {smallAverage}', file=sys.stderr)
    #    if smallAverage > bigAverage:  # Add RSI condition for overbought
    #        if self.lastAction == "BUY":
    #            print("no_moves", flush=True)
    #        else:
    #            self.lastAction = "BUY"
    #            affordable = calculateAffordable("USDT", self.stacks, self.candlesList)
    #            print(f'buy USDT_BTC {affordable}', flush=True)
    #            # print("BUY rsi = ", rsi, file=sys.stderr)
    #    elif smallAverage < bigAverage:  # Add RSI condition for oversold
    #        if self.lastAction == "SELL":
    #            print("no_moves", flush=True)
    #        else:
    #            self.lastAction = "SELL"
    #            affordable = calculateAffordable("BTC", self.stacks, self.candlesList)
    #            if affordable <= 0.0:
    #                print("no_moves", flush=True)
    #            else:
    #                positionSize = self.calculatePositionSize("BTC")  # Calculate position size
    #                positionSize = min(positionSize, affordable)  # Ensure position size is affordable
    #                print(f'sell USDT_BTC {positionSize}', flush=True)

    ###########################
    def doAction(self):
        rsi = self.calculateRSI()
        bigAverage = calculateAverage(100, self.candlesList)
        smallAverage = calculateAverage(25, self.candlesList)
        print(f'bigAverage {bigAverage} smallAverage {smallAverage}', file=sys.stderr)
        if smallAverage > bigAverage and rsi > 80:  # Add RSI condition for overbought
            if self.lastAction == "BUY":
                print("no_moves", flush=True)
            else:
                self.lastAction = "BUY"
                affordable = calculateAffordable("USDT", self.stacks, self.candlesList)
                print(f'buy USDT_BTC {affordable}', flush=True)
        elif smallAverage < bigAverage and rsi < 20:  # Add RSI condition for oversold
            if self.lastAction == "SELL":
                print("no_moves", flush=True)
            else:
                self.lastAction = "SELL"
                affordable = calculateAffordable("BTC", self.stacks, self.candlesList)
                if affordable <= 0.0:
                    print("no_moves", flush=True)
                else:
                    print(f'sell USDT_BTC {affordable}', flush=True)
        else:
            print("no_moves", flush=True)
