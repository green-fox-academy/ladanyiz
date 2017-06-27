#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#define PORT 777

// Create Server and Client Applications that send and receive messages.
// Client

int main()
{
    WSADATA wsa_data;

    // Initialize Winsock version 2.2
    printf("\nInitializing Winsock... ");
    if (WSAStartup(MAKEWORD(2,2), &wsa_data) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Initialized. ");

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        printf("Can't create a socket, error %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket created.\n");

    // Create sockaddr_in structure
    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    //Connect to remote server
    if (connect(listening, (SOCKADDR*)&server, sizeof(server)) < 0)
    {
        puts("Connect error");
        return 1;
    }
    puts("Connected");

    //Send some data
    char message[100];
    while(1) {
        gets(message);
        if (send(listening, message, strlen(message), 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        char server_reply[100];
        int recv_size = recv(listening, server_reply, 100, 0);
        if (recv_size == SOCKET_ERROR) {
            puts("Receive failed");
            return 1;
        }
        //Add a NULL terminating character to make it a proper string before printing
        server_reply[recv_size] = '\0';
        puts("\nReply:");
        printf("%s\n\n", server_reply);
    }

    closesocket(listening);

    // When your application is finished call WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

    return 0;
}

