import socket

HOST = ''
PORT = 5009
s    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(1)
conn, addr = s.accept()
print( "Connected by " + repr(addr))
while(conn):
    data = conn.recv(1024)
    if not data:break
    print(str(data.decode()))

