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
    // Decalring the server's IP address and port number
    const char* ip_address = "127.0.0.1";
    const int port_no = 1255; //changed port
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
    sin.sin_addr.s_addr = inet_addr(ip_address); //bind to server ip
    sin.sin_port = htons(port_no); //converting port number to network bytes
    // trying to connect to the server
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    char data_addr[] = "Im a message";
    int data_len = strlen(data_addr);
    // Send the message to the server
    int sent_bytes = send(sock, data_addr, data_len, 0);
    // checking if message sending succeed
    if (sent_bytes < 0) {
    // error
    }
    //change message size
    char buffer[2048];
    int expected_data_len = sizeof(buffer);
    // Receive data from the server
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    // checking if retrive data from server succeed
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }
    // close client socket
    close(sock);
    return 0;
}