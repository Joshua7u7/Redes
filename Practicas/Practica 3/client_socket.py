import socket 
import traceback
from dotenv import load_dotenv
import os
load_dotenv()

class ClientSocket:
    path = os.getenv("CLIENT_ROUTE")

    def __init__(self, host, port):
        self.host = host
        self.port = port
    
    def make_configuration(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def make_connection(self):
        self.client_socket.connect((self.host, self.port))

    
    def listen_to_server(self):
        print("Listening to changes")
        while True:
            try:
                server_message = self.client_socket.recv(1024)
                server_message = server_message.decode("utf-8")
                if server_message.split(",")[0] == 'action':
                    self.make_action(server_message)
                    print(server_message)
            except Exception:
                traceback.print_exc()
                break
    
    def make_action(self, server_message):
        args = server_message.split(',')
        args = [arg.strip() for arg in args]
        if args[1] == 'created':
            print(os.path.isfile(self.path + args[2]))
            if os.path.isfile(self.path + args[2]) == False:
                file = open(self.path+args[2], 'wb')
                file.close()
        elif args[1] == 'moved':
            if os.path.isfile(self.path + args[2]) == True:
                os.rename(self.path+args[2], self.path+args[3])
        elif args[1] == 'deleted':
            if os.path.isfile(self.path + args[2]) == True:
                os.remove(self.path + args[2])
        elif args[1] == 'modified':
            try:
                if len(args[2]) != 0:
                    file = open(self.path + args[2], 'wb')
                    file.write(bytes(args[3], 'utf-8'))
                    file.close()
            except:
                print("The file is already in use")
