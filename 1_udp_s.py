# importing socket files and from socket 2 const
# AF_INET - the IP version will be IPv4
# SOCK_DGRAM - protocal of network this case UDP protocol
from socket import socket, AF_INET, SOCK_DGRAM

# Creating new socket that using IPv4 and UDP protocol
s = socket(AF_INET, SOCK_DGRAM)

# source ip - empty string mean the socket will bind to all availables
src_ip = ''
# port number - the socket will receive and send data only to this unique number
# change to new port
src_port = 1245
# bind the socket to IP and port we provied. this makes the server ready to receive data
s.bind((src_ip, src_port))

print("waiting for a data")

# forever-loop to keep server running always looking for data
while True:

    # socket recieve from means get data that waiting up to 2048 bits
    # this function returns the data that have been sent
    # also returns tuple of sender_info with ip of sender and port 
    # i changed the maxsimum bit that can recieved
    data, sender_info = s.recvfrom(1024)
    print("oh i got something!")
    #return the message to sender but using upper method to convert message to upper case
    s.sendto(data.lower(), sender_info)
    print("i sent something !")

