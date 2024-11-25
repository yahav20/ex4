# importing socket files and from socket 2 const
# AF_INET - the IP version will be IPv4
# SOCK_DGRAM - protocal of network this case UDP protocol
from socket import socket, AF_INET, SOCK_DGRAM

# Creating new socket that using IPv4 and UDP protocol
s = socket(AF_INET, SOCK_DGRAM)

# decalring ip of message destenation 
dst_ip = '127.0.0.1'
# port number of the server
# change to same port in client
dst_port = 1245

#send message to ip and port we declared
s.sendto(b'Hello', (dst_ip,dst_port))
# waiting for data back from the server up to 2048 bits
# also returns tuple of sender_info with ip of sender and port 
# i changed the maxsimum bit that can recieved
data, sender_info = s.recvfrom(1024)
#print the returned mesaage
print ("The server have told: " , data)
# close socket
s.close()
