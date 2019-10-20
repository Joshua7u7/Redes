import socket 
import traceback
from dotenv import load_dotenv
import os
import time
load_dotenv()

class ClientSocket:
    path = os.getenv("CLIENT_ROUTE")

    def __init__(self, host, port):
        self.host = host
        self.port = port
    
    def make_configuration(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_address = (self.host, self.port)
        print("published in host "+ str(self.host) + " : " +str(self.port))
        self.client_socket.sendto(bytes("Hey!", "latin1"), self.server_address)
        data, addr = self.client_socket.recvfrom(1024)
        print("My new port is: " + str(data.decode("latin1")))
        return int(data.decode("latin1")), addr

    def make_connection(self):
        self.client_socket.connect((self.host, self.port))

    
    def listen_to_server(self):
        print("Listening to changes")
        self.filename = ''
        self.info = ''
        while True:
            try:
                server_message, addr = self.client_socket.recvfrom(1024)
                server_message = server_message.decode("latin1")
                split_message = server_message.split("__##")
                if len(split_message) == 1:
                    self.make_action(split_message[0])
                elif len(split_message[0]) == 0:
                    self.make_action("Finish")
                    self.make_action(split_message[2])
                elif len(split_message[2]) == 0:
                    self.make_action(split_message[0])
                    self.make_action("Finish")
                elif len(split_message[0]) == 0 and len(split_message[2]) == 0:
                    self.make_action("Finish")
                print(server_message)
            except Exception:
                traceback.print_exc()
                break
    
    def make_action(self, server_message):
        args = server_message.split(',')
        args = [arg.strip() for arg in args]
        if args[0] == 'action':
            if args[1] == 'created':
                if os.path.isfile(self.path + args[2]) == False:
                    file = open(self.path+args[2], 'wb')
                    file.close()
            elif args[1] == 'moved':
                if os.path.isfile(self.path + args[2]) == True:
                    os.rename(self.path+args[2], self.path+args[3])
                    self.filename = self.path + args[3]
                else:
                    file = open(self.path + args[3], "wb")
                    file.close()
                    self.filename = self.path + args[3]
            elif args[1] == 'deleted':
                if os.path.isfile(self.path + args[2]) == True:
                    os.remove(self.path + args[2])
            elif args[1] == 'modified':
                self.filename = self.path + args[2]
        else:
            self.add_info(server_message)

    def add_info(self, message):
        if message != 'Finish':
            self.info += message
        else:
            if self.filename != '':
                print("Imm gonna write")
                file = open(self.filename , "wb")
                print(len(self.info))
                file.write(self.info.encode("latin1"))
                file.close()
                self.info = ''
                self.filename = ''
