import time
import socket   
from watchdog.observers import Observer  
from watchdog.events import PatternMatchingEventHandler 
import traceback
from dotenv import load_dotenv
import os
import threading
load_dotenv()

class FSHandler:
    path = os.getenv("SERVER_ROUTE")
    patterns = "*"
    ignore_patterns = ""
    ignore_directories = False
    case_sensitive = True
    option = ''
    current_file = ''
    file_information = ''
    def __init__(self, socket, host, port, active_connections):
        self.socket = socket
        self.host = host
        self.port = port
        self.active_connections = active_connections
        self.my_event_handler = PatternMatchingEventHandler(self.patterns, self.ignore_patterns, self.ignore_directories, self.case_sensitive)
        self.configure()
        self.create_observer()

    def configure(self):
        self.my_event_handler.on_created = self.on_created
        self.my_event_handler.on_deleted = self.on_deleted
        self.my_event_handler.on_modified = self.on_modified
        self.my_event_handler.on_moved = self.on_moved

    def create_observer(self):
        try:
            go_recursively = True
            self.my_observer = Observer()
            self.my_observer.schedule(self.my_event_handler, self.path, recursive=go_recursively)
        except:
            print("Error")

    def start_observer(self):
        self.my_observer.start()
        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            self.my_observer.stop()
            self.my_observer.join()

    def on_created(self, event):
        try:
            client_message = "action,created," +event.src_path.split("\\")[-1]
            if self.option == 'created' and self.current_file == event.src_path:
                print()
            else:
                time.sleep(2)
                self.option = 'created'
                self.current_file = event.src_path
                for connection in self.active_connections:
                    connection.send(bytes(client_message, 'utf-8'))
                time.sleep(2)
        except:
            print("Error de permisos")

    def on_deleted(self, event):
        client_message = "action,deleted," +event.src_path.split("\\")[-1]
        if self.option == 'deleted' and self.current_file == event.src_path:
            print()
        else:
            time.sleep(2)
            self.option = 'deleted'
            self.current_file = event.src_path
            for connection in self.active_connections:
                connection.send(bytes(client_message, 'utf-8'))
            time.sleep(2)

    def on_modified(self, event):
        client_message = f"modified, {event.src_path}"
        if self.option == 'modified' and self.current_file == event.src_path:
            print()
        else:
            if os.path.isfile(event.src_path) == True:
                time.sleep(2)
                self.option = 'modified'
                self.current_file  = event.src_path
                for connection in self.active_connections:
                    connection.send(bytes(client_message, 'utf-8'))
                time.sleep(2)
                while True:
                    file = open(event.src_path, 'rb')
                    content = file.read(1024)
                    while content:
                        for connection in self.active_connections:
                            connection.send(content)
                        content = file.read(1024)
                        time.sleep(2)
                    break
                try:
                    for connection in self.active_connections:
                        connection.send(bytes("Finish", "utf-8"))
                except Exception:
                    for connection in self.active_connections:
                        connection.send(bytes("Finish", "utf-8"))
                    traceback.print_exc()
                file.close()
        
    def on_moved(self, event):
        client_message = "action,moved,"+event.src_path.split("\\")[-1]+","+ event.dest_path.split("\\")[-1]
        if self.option == 'moved' and self.current_file == event.src_path:
            print()
        else:
            time.sleep(2)
            self.option = 'moved'
            self.current_file = event.dest_path
            for connection in self.active_connections:
                connection.send(bytes(client_message, 'utf-8'))
            time.sleep(2)

