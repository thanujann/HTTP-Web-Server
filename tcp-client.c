// Thanujan Nandakumar
// TCP Client Side

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	int PORT = 8080;
    struct sockaddr_in serverAddress;
    int addressLength = sizeof(serverAddress);

    // Create TCP socket
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0)
    {
        printf("Socket creation failure.");
        return 0;
    }
    
    // Set up socket address to bind with socket (same as server)
    memset((char *)&serverAddress, 0, addressLength);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    
    // Convert address from text to binary
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        printf("Invalid address failure.");
        return 0;
    }
    
    // Connect to tcp socket with address
    if (connect(tcpSocket, (struct sockaddr *)&serverAddress, addressLength) < 0)
    {
        printf("Connection failure.");
        return 0;
    }

    // Send client message
    char *clientMessage = "Hello from client\n";
    send(tcpSocket, clientMessage, strlen(clientMessage), 0);
    printf("Hello sent from client.\n");

    // Read from socket
    char buffer[1024] = {0};
    int valread = read(tcpSocket, buffer, 1024);
    printf("%s\n", buffer);

    return 0;
}