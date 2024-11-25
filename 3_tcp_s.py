# importing socket files
import socket
# Creating new socket that using IPv4 (AF_INET) and TCP protocol (SOCK_STREAM)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# source ip - empty string mean the socket will bind to all availables
server_ip = ''
# port number of the server - changed
server_port = 12445
# bind the socket to IP and port we provied. this makes the server ready to receive data
server.bind((server_ip, server_port))
# listen up to 5 clients at time
server.listen(5)

while True:
    # Accept a new connection from a client
    client_socket, client_address = server.accept()
    print('Connection from: ', client_address)
    # Receive data from the client (up to 1024 bytes at a time) - changed to 2048
    data = client_socket.recv(2048)
    # Loop to process and respond to the client's messages
    while not data == ' ':
        # Print the recived data
        print('Received: ', data.decode('utf-8'))
        # Convert the data to uppercase and send it back to the client
        client_socket.send(data.lower())
        # Receive the next message from the client - changed to 2048
        data = client_socket.recv(2048)
     # If the client sends an empty message (indicating a disconnect), break the loop
    print('Client disconnected')
     # Close the connection to the client
    client_socket.close()