from server_socket import SocketServer
import asyncio

port = 8081
host = "192.168.0.11"

def run_server():
    server = SocketServer(port, host)
    server.configurate_socket()
    server.make_listen()
    server.accept_clients()

run_server()