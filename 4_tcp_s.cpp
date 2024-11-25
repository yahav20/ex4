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
    // Decalring the server's port number
    const int server_port = 1255; //changed port
    // create tcp socket using IPv4
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // checking if socket creating succeed
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    // clearing all memory to get rid of junk data
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET; //ipv4
    sin.sin_addr.s_addr = INADDR_ANY;//bind to any client ip
    sin.sin_port = htons(server_port); //converting port number to network bytes
    // bind the socket in check if socket bind succeed
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    // Start listening up to 5 clients - changed to 4
    if (listen(sock, 4) < 0) {
        perror("error listening to a socket");
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin); // size of client address structure
    // accept a connection from a client
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    // checking if connection succeed
    if (client_sock < 0) {
        perror("error accepting client");
    }

    //change message size
    char buffer[2048];
    int expected_data_len = sizeof(buffer);
    // Receive data from the client
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }
     // Send the received data back to the client
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    // checking if sending succeed
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    // Close the client and server socket
    close(client_sock);
    close(sock);


    return 0;
}