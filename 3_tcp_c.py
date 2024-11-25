# importing socket files
import socket
# Creating new socket that using IPv4 (AF_INET) and TCP protocol (SOCK_STREAM)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# decalring ip of message destenation - server ip
dest_ip = '127.0.0.1'
# port number of the server - changed
dest_port = 12445
# connecting to server
s.connect((dest_ip, dest_port))
msg = input("Message to send: ")
# Forever loop to send and receive messages until the user types 'quit'
while not msg == ' ':
    # Send message to send 
    s.send(bytes(msg, 'utf-8'))
    # Receive the server's response (up to 4096 bytes) - changed to 2048
    data = s.recv(2048)
    # waiting to user next message
    print("Server sent: ", data.decode('utf-8'))
    msg = input("Message to send: ")
# Close the connection to the server
s.close()