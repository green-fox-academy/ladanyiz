#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "timestamp.h"

#define PORT 17777

// Create Server and Client Applications that send and receive messages.
// Server.

int main()
{
    WSADATA wsa_data;
    FILE *file = fopen("log.txt", "a");

    // Initialize Winsock version 2.2
    printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa_data) != 0)
    {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Initialized.\n");
    fprintf(file, "%s\tWinsock initialized\n", timestamp());

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        printf("Can't create a socket, error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");
    fprintf(file, "%s\tSocket created\n", timestamp());

    //Prepare the sockaddr_in structure
    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = INADDR_ANY;

    // Bind the IP address and port to the socket
    if( bind(listening ,(SOCKADDR*)&server , sizeof(server)) == SOCKET_ERROR)
        printf("Bind failed with error code %d", WSAGetLastError());
    puts("Bind done.");
    fprintf(file, "%s\tBind done\n", timestamp());

    // Tell WinSock the socket is for listening
    listen(listening, SOMAXCONN);

    // Wait for a connection
    puts("Waiting for incoming connections...");
    fprintf(file, "%s\tWaiting for incoming connections...\n", timestamp());

    SOCKADDR_IN client;
    int client_size = sizeof(client);

    SOCKET client_socket = accept(listening, (SOCKADDR*)&client, &client_size);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }
    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);
    printf("Connection accepted from %s on port %d\n", client_ip, client_port);
    fprintf(file, "%s\tConnection accepted from %s on port %d\n", timestamp(), client_ip, client_port);

    // Communicating with client
    char buffer[100];
    int received = 0;
    while (1) {
        received = recv(client_socket, buffer, 100, 0);
        if(received == SOCKET_ERROR) {
            puts("recv failed");
            return 1;
        }
        // Put a terminator at the and of the buffer to create a proper string
        buffer[received] = '\0';
        // Print out message just for the show ;)
        puts(buffer);
        fprintf(file, "%s\tReceived :%s\n", timestamp(), buffer);

        send(client_socket , buffer , received , 0 );
        fprintf(file, "%s\tSent :%s\n", timestamp(), buffer);
    }

    closesocket(listening);
    fprintf(file, "%s\tSocket closed\n", timestamp(), buffer);

    // When your application is finished call WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

    return 0;
}

