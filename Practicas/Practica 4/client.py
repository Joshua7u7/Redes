from client_socket import ClientSocket
from watcher import FSHandler
import threading
import os
from dotenv import load_dotenv
load_dotenv()

class Main:

    host = os.getenv("HOST")
    port = int(os.getenv("PORT"))
    observer = ''
    client = ''
    def __init__(self):
        self.client = ClientSocket(self.host, self.port)
        self.port , addr = self.client.make_configuration()
        self.client.make_connection()
        self.observer = FSHandler(self.client.client_socket, self.host, self.port, addr)

    def process(self):
        threading.Thread(target=self.observer.start_observer).start()
        threading.Thread(target=self.client.listen_to_server).start()

client = Main()
client.process()
        