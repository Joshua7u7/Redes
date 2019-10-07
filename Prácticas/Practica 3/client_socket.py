import socket 
import traceback
import os

class ClientSocket:
    path = "C:\\Users\\josue.ruiz\\Documents\\ESCOM\\Redes\\Prácticas\\Practica 3\\client_files\\" 

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
                self.make_action(server_message)
            except Exception:
                traceback.print_exc()
                break
    
    def make_action(self, server_message):
        args = server_message.split(',')
        args = [arg.strip() for arg in args]
        if args[0] == 'created':
            file = open(self.path+args[1], 'wb')
            file.close()
        elif args[0] == 'moved':
            os.rename(self.path+args[1], self.path+args[2])
        elif args[0] == 'deleted':
            os.remove(self.path + args[1])
        elif args[0] == 'modified':
            file = open(self.path + args[1], 'wb')
            file.write(args[2])
            file.close()       
