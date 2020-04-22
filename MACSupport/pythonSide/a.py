

from socket import *
from time import *

if __name__ == "__main__":
    port = 37716
    print("Connecting to port : " + str(port))
    #port = 80
    client_sock = socket(AF_INET, SOCK_STREAM)
    client_sock.connect(('',port))
    init_mode = bytearray()
    init_mode.append(1)
    client_sock.send(init_mode)

    for i in range(255):
        r = 255
        g = 255
        b = 255

        send_byte = bytearray()
        send_byte.append(r)
        send_byte.append(g)
        send_byte.append(b)
        client_sock.send(send_byte)
        sleep(1);

    for i in range(255):
        r = 255
        g = 0
        b = 255

        send_byte = bytearray()
        send_byte.append(r)
        send_byte.append(g)
        send_byte.append(b)
        client_sock.send(send_byte)
