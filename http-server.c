// Thanujan Nandakumar
// HTTP Server Side

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int PORT = 8080;
    struct sockaddr_in socketAddress;
    int addressLength = sizeof(socketAddress);
    
    // Create TCP socket
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket == 0)
    {
        perror("Socket creation failure.");
        return 0;
    }

    // Set up socket address to bind with socket
    memset((char *)&socketAddress, 0, addressLength);
    socketAddress.sin_family = AF_INET; // Domain used in socket
    socketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Accept any IP connection (0.0.0.0)
    socketAddress.sin_port = htons( PORT ); // Port of the socket to connect to
    
    // Bind the address to the socket
    if (bind(tcpSocket, (struct sockaddr *)&socketAddress, addressLength) < 0)
    {
        perror("Bind failure.");
        return 0;
    }

    // Listen and queue incoming connections (max 3)
    if (listen(tcpSocket, 3) < 0)
    {
        perror("Listening failure.");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("\n--------- Waiting for new connection ---------\n\n");
        // Get (or wait for) next connection request from queue set up by listen 
        // and make new socket for exchanging data between client and server
        int newTcpSocket = accept(tcpSocket, (struct sockaddr *)&socketAddress, (socklen_t*)&addressLength);
        if (newTcpSocket < 0)
        {
            perror("Accept failure.");
            return 0;
        }
        
        // Read from new socket
        char buffer[1024] = {0};
        int valread = read(newTcpSocket, buffer, 1024);
        printf("%s\n", buffer);

        // Send message to client (with header)
    	char *serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 18\n\nHello from server.";
        write(newTcpSocket, serverMessage, strlen(serverMessage));
        printf("Hello sent from server.\n");

        // Close socket
        close(newTcpSocket);
    }
}