from socket import *


class Bridge():
    """
    A class that manages all connections to server
    """
    def __init__(self, mode, port=37716):
        """
        An intializer method for class Bridge
        @params {int} Operation mode to send to server
        @params {int} Port number to send communications through. 37716 Default
        """
        self.operation_mode = mode
        self.port = port
        self.client_sock = socket(AF_INET, SOCK_STREAM)

        self.connect_server()
        self.send_operation_mode()

    def connect_server(self):
        """
        A method that connects to server for the first time.
        @params {void}
        @returns {void}
        """
        print("[Client] Connecting to port : " + str(self.port))

        try:
            self.client_sock.connect(('', self.port))

        except ConnectionRefusedError:  # the case when server is closed
            print("[ERROR] Cannot connect to server.")
            print("[ERROR] Please check if server engine is running")
            exit(0)

    def send_operation_mode(self):
        """
        A method that sends server which operation mode would be used.
        @params {void}
        @returns {void}
        """
        print("[Client] Sent operation mode : " + str(self.operation_mode))

        operation_mode = bytearray()
        operation_mode.append(self.operation_mode)
        self.client_sock.send(operation_mode)

    def send_rgb_value(self, r, g, b):
        """
        A method that sends server RGB value.
        @params {int} Red value, 0 ~ 255
        @params {int} Green value, 0 ~ 255
        @params {int} Blue value, 0 ~ 255
        @returns {void}
        """
        send_byte = bytearray()
        send_byte.append(r)
        send_byte.append(g)
        send_byte.append(b)

        try:
            self.client_sock.send(send_byte)

        except BrokenPipeError:  # the case when server is closed.
            print("[Server] The Server is closed!")
            exit(0)
