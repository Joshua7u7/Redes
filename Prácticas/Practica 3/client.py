from client_socket import ClientSocket
from watcher import FSHandler

host = "192.168.0.11"
port = 8081

client = ClientSocket(host, port)
client.make_configuration()
client.make_connection()
observer = FSHandler(client.client_socket, host, port)
observer.start_observer()