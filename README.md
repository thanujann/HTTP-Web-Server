# HTTP Web Server
*The HTTP server must be started before the client can send a request*

## Server Side
File: http-server.c

Creates the TCP transport layer by setting up appropriate sockets.
The server will create a socket, identify it with an address, wait for an
incoming connection from the client, send/receive messages to/from the client, 
and finally close each connection.

## Client Side
A simple TCP client was created to show the difference between a TCP request (no header) and HTTP request (header).
The TCP client gets run through the terminal (by running tcp-client.c) while the HTTP client gets run through a web browser.

### TCP Connection
File: tcp-client.c

Creates a TCP connection between the HTTP server and a TCP client. It then sends 
a message from the TCP client to the server and receives an HTTP response from the server.

### HTTP Connection
Enter *localhost:8080* into a web browser.

This will construct a request header and send it to the server. The 
server will then construct a response header, and include a message to be sent
back to the client. The web browser will then display this message.
