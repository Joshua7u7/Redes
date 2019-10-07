import socket
import threading
import os
import traceback
import time
import asyncio
from dotenv import load_dotenv
load_dotenv()
class SocketServer:

    max_clients = 10
    active_connections = []
    threads = []
    server_files = os.getenv("SERVER_ROUTE")
    
    def __init__(self, port, host):
        self.port = port
        self.host = host

    def configurate_socket(self):
        self.server_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_descriptor.bind((self.host, self.port))

    def make_listen(self):
        self.server_descriptor.listen(self.max_clients)

    def accept_clients(self):
        while True:
            try:
                client_socket, (client_host, client_port) = self.server_descriptor.accept()
                print(str(client_host) + ":" + str(client_port))
                self.active_connections.append(client_socket)
                threading.Thread(target = self.handle_connections, args=(self.active_connections[-1], ) ).start()
            except:
                break
        self.server_descriptor.close()

    def handle_connections(self, connection):
        actions_maded = []
        valid_options = ['created','modified','moved','deleted']
        filename = ''
        info = ''
        while True:
            try:
                client_message =  connection.recv(1024)
                client_message = client_message.decode('utf-8')
                option = client_message.split(',')[0]
                if option in valid_options:
                    actions_maded.append(option)
                filename, info = self.make_actions(option, client_message, actions_maded, filename, info, connection)
            except Exception:
                traceback.print_exc()
                break
        connection.close()

    def make_actions(self, option, client_message, actions_maded, filename, info, connection):
        if  option == 'created':
            filename =  client_message.split(',')[1].split("\\")[-1]
            open(self.server_files+filename, "wb")
            print(option + " >>  " + filename)
            self.notify_clients(connection, option, filename, '', '','')
        elif  option == 'moved':
            src = client_message.split(',')[-2].split("\\")[-1]
            dest = client_message.split(',')[-1].split("\\")[-1]
            if os.path.isfile(self.server_files+src) == True:
                os.rename(self.server_files+src, self.server_files+dest)
            print(option + " >>  " + src + " to " + dest)
            self.notify_clients(connection, option, src, dest, '','')
        elif  option == 'deleted':
            filename = client_message.split(',')[-1].split("\\")[-1]
            if os.path.isfile(self.server_files+filename) == True:
                os.remove(self.server_files+filename)
            print(option + " >>  " + filename)
            self.notify_clients(connection, option, filename, '', '','')
        elif option == 'modified':
            filename = client_message.split(',')[-1].split("\\")[-1]
            print(option + " >>  " + filename)
        else:
            if client_message == 'Finish':
                file = open(self.server_files + filename, 'wb')
                file.write(bytes(info, 'utf-8'))
                file.close()
                self.notify_clients(connection, 'modified', filename, '', info, '')
                info = ''
            else :
                info += client_message
        if option == 'modified' or actions_maded[-1] == 'modified':
            return filename, info
        elif option == 'moved':
            return dest, info
        else:
             return "made", info

    def notify_clients(self, current_connection, option, src, dest, info, msg):
        if option == 'created':
            msg = 'action,' + option + "," +src
        elif option == 'modified':
            msg = 'action,' + option + "," + src + "," + info
        elif option == 'deleted':
            msg = 'action,' + option + "," + src
        elif option == 'moved':
            msg = 'action,' + option + "," + src + "," + dest
        for connection in self.active_connections:
            if connection != current_connection:
                connection.send(bytes(msg, 'utf-8')) 




            


