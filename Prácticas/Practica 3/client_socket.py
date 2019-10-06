import socket 

class ClientSocket:

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
                print(server_message)
            except Exception:
                print("error")
                break
