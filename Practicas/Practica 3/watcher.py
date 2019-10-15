import time
import socket   
from watchdog.observers import Observer  
from watchdog.events import PatternMatchingEventHandler 
import traceback
from dotenv import load_dotenv
import os
load_dotenv()

class FSHandler:
    path = os.getenv("CLIENT_ROUTE")
    patterns = "*"
    ignore_patterns = ""
    ignore_directories = False
    case_sensitive = True
    option = ''
    current_file = ''
    file_information = ''
    def __init__(self, socket, host, port):
        self.socket = socket
        self.host = host
        self.port = port
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
            client_message = f"created, {event.src_path}"
            if self.option == 'created' and self.current_file == event.src_path:
                print()
            else:
                self.option = 'created'
                self.current_file = event.src_path
                self.socket.send(client_message.encode("latin1"))
                time.sleep(1)
        except:
            print("Error de permisos")

    def on_deleted(self, event):
        client_message = f"deleted, {event.src_path}"
        if self.option == 'deleted' and self.current_file == event.src_path:
            print()
        else:
            self.option = 'deleted'
            self.current_file = event.src_path
            self.socket.send(bytes(client_message, 'latin1'))
            time.sleep(1)

    def send_info_data(self, filename):
         if os.path.isfile(filename) == True:
            file = open(filename, 'rb')
            content = file.read(1024)
            while True:
                while content:
                    self.socket.send(content)
                    content = file.read(1024)
                break
            try:
                time.sleep(1)
                self.socket.send(bytes("Finish", "latin1"))
            except Exception:
                time.sleep(1)
                self.socket.send(bytes("Finish", "latin1"))
            file.close()


    def on_modified(self, event):
        client_message = f"modified, {event.src_path}"
        if self.option == 'modified' and self.current_file == event.src_path:
            print()
        else:
            if os.path.isfile(event.src_path) == True:
                self.option = 'modified'
                self.current_file  = event.src_path
                self.socket.send(bytes(client_message, 'latin1'))
                time.sleep(1)
                self.send_info_data(event.src_path)
               
        
    def on_moved(self, event):
        client_message = f"moved, {event.src_path}, {event.dest_path}"
        if self.option == 'moved' and self.current_file == event.src_path:
            print()
        else:
            if os.path.isfile(event.dest_path) == True:
                self.option = 'moved'
                self.current_file = event.dest_path
                self.socket.send(bytes(client_message, 'latin1'))
                time.sleep(1)
                self.send_info_data(event.dest_path)
