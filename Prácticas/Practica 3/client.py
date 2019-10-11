from client_socket import ClientSocket
from watcher import FSHandler
import threading

class Main:

    host = "192.168.0.11"
    port = 8081
    observer = ''
    client = ''
    def __init__(self):
        self.client = ClientSocket(self.host, self.port)
        self.client.make_configuration()
        self.client.make_connection()
        self.observer = FSHandler(self.client.client_socket, self.host, self.port)

    def process(self):
        threading.Thread(target=self.observer.start_observer).start()
        threading.Thread(target=self.client.listen_to_server).start()

client = Main()
client.process()
        