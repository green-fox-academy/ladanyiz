#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "file_IO.h"

#define PORT 777

// Create Server and Client Applications that send and receive messages.
// Server.

int main()
{
    WSADATA wsa_data;
    char *path = "log.txt";

    // Initialize Winsock version 2.2
    printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa_data) != 0)
    {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Initialized.\n");

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        printf("Can't create a socket, error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = INADDR_ANY;

    // Bind the IP address and port to the socket
    if( bind(listening ,(SOCKADDR*)&server , sizeof(server)) == SOCKET_ERROR)
        printf("Bind failed with error code %d", WSAGetLastError());
    puts("Bind done.");

    // Tell WinSock the socket is for listening
    listen(listening, SOMAXCONN);

    // Wait for a connection
    puts("Waiting for incoming connections...");

    SOCKADDR_IN client;
    int client_size = sizeof(client);

    SOCKET client_socket = accept(listening, (SOCKADDR*)&client, &client_size);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }

    puts("Connection accepted");
    file_write_line_logging_mode(path, "Connection accepted");

    // Communicating with client
    char buffer[100];
    int received = 0;
    while (1) {
        received = recv(client_socket, buffer, 100, 0);
        // Put a terminator at the and of the buffer to create a proper string
        buffer[received] = '\0';
        // Print out message just for the show ;)
        puts(buffer);
        send(client_socket , buffer , received , 0 );
    }

    closesocket(listening);

    // When your application is finished call WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

    return 0;
}

