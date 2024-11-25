import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_ip = ''
server_port = 12345
server.bind((server_ip, server_port))
server.listen(5)

while True:
    client_socket, client_address = server.accept()
    print('Connection from: ', client_address)
    data = client_socket.recv(1024)
    while not data.decode('utf-8') == '':
        print('Received: ', data.decode('utf-8'))
        client_socket.send(data.upper())
        data = client_socket.recv(1024)

    print('Client disconnected')
    client_socket.close()