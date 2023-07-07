##
## EPITECH PROJECT, 2023
## new_ai
## File description:
## agent
##

import sys
import time
from king import King
from queen import Queen
from worker import Worker

def helper():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport is the port number")
    print("\tname is the name of the team")
    print("\tmachine is the name of the machine; localhost by default")

if __name__=='__main__':
    if len(sys.argv) == 2 and sys.argv[1] == "-help":
        helper()
        sys.exit(0)
    elif len(sys.argv) == 2 and sys.argv[1] == "-D":
        King("team1", "parent", "51.255.77.76", 6464)
        sys.exit(0)
    elif len(sys.argv) >= 5:
        port = 4242
        host = "127.0.0.1"
        team_name = "team1"
        ia = "king"
        i = 1
        name = "-1"

        while i < len(sys.argv):
            if sys.argv[i] == "-p":
                port = int(sys.argv[i + 1])
                i += 1
            elif sys.argv[i] == "-n":
                team_name = sys.argv[i + 1]
                i += 1
            elif sys.argv[i] == "-h":
                server_ip = sys.argv[i + 1]
                i += 1
            elif sys.argv[i] == "-ia":
                print("ia: ", sys.argv[i + 1])
                ia = sys.argv[i + 1]
                i += 1
            elif sys.argv[i] == "-name":
                name = sys.argv[i + 1]
                i += 1
            else:
                print("Error: invalid argument: ", sys.argv[i], "\n")
                helper()
                sys.exit(84)
            i += 1

        if ia == "king":
            King(team_name, name, server_ip, int(port))
        elif ia == "queen":
            Queen(team_name, name, server_ip, int(port))
        elif ia == "worker":
            Worker(team_name, name, server_ip, int(port))
    else:
        helper()
        sys.exit(84)