from server_socket import SocketServer

port = 8081
host = "192.168.0.11"

server = SocketServer(port, host)
server.configurate_socket()
server.make_listen()
server.accept_clients()
