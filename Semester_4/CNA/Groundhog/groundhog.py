#!/usr/bin/env python3

import sys
import math

def helper(ret):
    help = "SYNOPSIS\n"
    help += "\tgroundhog period\n"
    help += "\nDESCRIPTION\n"
    help += "\tperiod\tthe number of days defining a period"
    print(help)
    return ret

def temperatureIncreaseAverage(temp, period):
    if (len(temp) <= period):
        return "nan"
    average = 0.0
    index = len(temp) - period
    while (index != len(temp)):
        n = temp[index] - temp[index - 1]
        if (n < 0):
            n = 0
        average += n
        index += 1
    average /= period
    format = "{:.2f}".format(average)
    return format

def relativeTemperatureEvolution(temp, period):
    if (len(temp) <= period):
        return "nan"
    initial = temp[len(temp) - period - 1]
    last = temp[len(temp) - 1]
    result = (last - initial) / initial * 100
    format = round(result, 0)
    format = int(format)
    return format

def standardDeviation(temp, period):
    if (len(temp) < period):
        return "nan"
    period_temp = temp[len(temp) - period:]
    average = sum(period_temp) / len(period_temp)
    variance = 0
    for i in period_temp:
        variance += (i - average) ** 2
    variance /= len(period_temp)
    sd = math.sqrt(variance)
    format = "{:.2f}".format(sd)
    return format

def same_sign(x, y):
    return (x >= 0) == (y >= 0)

def groundhog_loop(period):
    temperatures = []
    i = 0
    old_rte = 0
    nbSwitch = 0
    weirdestValues = []
    while (True):
        line = input()
        if line == "STOP":
            break
        try:
            number = float(line)
            temperatures.append(number)
            tia = temperatureIncreaseAverage(temperatures, period)
            rte = relativeTemperatureEvolution(temperatures, period)
            sd = standardDeviation(temperatures, period)
            output = "g=" + str(tia) + "\t\tr=" + str(rte) + "%\t\ts=" + str(sd)
            if (i > period and same_sign(old_rte, rte) == False and old_rte != 0):
                output += "\t\ta switch occurs"
                nbSwitch += 1
            print(output)
            old_rte = rte
            i += 1
        except ValueError:
            print("Error: invalid input")
            continue
    print("Global tendency switched " + str(nbSwitch) + " times")
    print("5 weirdest values are " + str(weirdestValues))

def main():
    if len(sys.argv) != 2:
        return helper(84)
    if sys.argv[1] == "-h":
        return helper(0)
    try:
        period = int(sys.argv[1])
        if period <= 0:
            return helper(84)
        groundhog_loop(period)
    except ValueError:
        return helper(84)

main()