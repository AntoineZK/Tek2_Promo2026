##
## EPITECH PROJECT, 2023
## zappy_ia
## File description:
## client
##

# this is the client class
import socket
import sys

class NetworkAgent:
    def __init__(self, team_name, server_ip = "127.0.0.1", port = 4242):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server = server_ip
        self.port = port
        self.addr = (self.server, self.port)
        self.id = self.client.connect(self.addr)
        print(self.id)

    def __del__(self):
        self.client.close()

    def sendMessage(self, msg: str, by: str):
        copy = msg
        msg += "\n"
        msg = msg.replace(" ", "_")
        msg = msg.replace("_", " ", 1)
        message_send = self.client.send(msg.encode("utf-8"))
        if message_send == 0:
            print("Error: message not send")
            return
        # print("Message send: {} by {}".format(copy, by))

    def receiveMessage(self):
        msg = self.client.recv(2048).decode("utf-8")
        if msg <= "":
            print("Error: message not received")
            print("Deconexion")
            self.client.close()
            sys.exit(84)
        # print("Message received: ", msg)

        # print("Message received: ---{}---".format(msg))
        msg = msg.replace("_", " ")
        msg = msg.splitlines()
        return msg

    def message_handling(self, msg: str):
        print("Message handling: ", msg)