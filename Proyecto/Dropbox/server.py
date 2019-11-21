from server_socket import SocketServer
import asyncio
from dotenv import load_dotenv
import os

load_dotenv()

port =  int(os.getenv("PORT"))
host = os.getenv("HOST")

def run_server():
    server = SocketServer(port, host)
    server.configurate_socket()
    server.make_listen()
    server.accept_clients()

run_server()