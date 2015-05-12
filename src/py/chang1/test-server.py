import socket   #for sockets
import sys  #for exit
import time


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = '127.0.0.1';
port = 1337;

while(1):
    print("sending message...")
    
    
    s.sendto(b'is fat', (host, port))
    
    d = s.recvfrom(1024)
    data = d[0]
    addr = d[1]
    
    print("got response = ", data)
    time.sleep(1)