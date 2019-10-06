import socket 

class ClientSocket:

    def __init__(self, host, port):
        self.host = host
        self.port = port
    
    def make_configuration(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def make_connection(self):
        self.client_socket.connect((self.host, self.port))