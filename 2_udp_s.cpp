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
    //changed port
    const int server_port = 1255;
    // create udp socket using IPv4
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // checking if socket creating succeed
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    // clearing all memory to get rid of junk data
    memset(&sin, 0, sizeof(sin));
    // defining server properties
    sin.sin_family = AF_INET; //ipv4
    sin.sin_addr.s_addr = INADDR_ANY; //bind to any ip
    sin.sin_port = htons(server_port); //converting port number to network bytes
    // bind the socket in check if socket bind succeed
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    //change size of the message
    char buffer[2048];
    // Receive data from the client
    // write data to buffer array and save sender info using sturct sockadd_in
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The client sent: " << buffer << endl;

    // Convert the message to uppercase
    for (int i = 0; i < bytes; i++) {
        buffer[i] = toupper(buffer[i]); // Convert each character to uppercase
    }
    // send echo of the data back to client
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    // Close the socket
    close(sock);

    return 0;
}