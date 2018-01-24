import socket

HOST = ''
PORT = 5009
s    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
while(1):
    i = input()
    if i == "": break
    i = str.encode(i)
    s.send(i)

s.close()
