// importing all neccercy socket libaries
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const char* ip_address = "127.0.0.1";
    //changed port
    const int port_no = 1255;
    // create udp socket using IPv4 
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // checking if socket creating succeed
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
      // clearing all memory to get rid of junk data
      memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET; //ipv4
    sin.sin_addr.s_addr = inet_addr(ip_address); //bind to server ip
    sin.sin_port = htons(port_no); //converting port number to network bytes
    //change size of the message
    char data[] = "hello";
    int data_len = sizeof(data);
    // try to send message to server
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    //check if socket send succeed
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    // Receive data from the server
    // write data to buffer array and save sender info using sturct sockadd_in
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The server sent: " << buffer << endl;
    //close socker
    close(sock);

    return 0;
}