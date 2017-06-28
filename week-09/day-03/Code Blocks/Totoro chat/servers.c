#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
#include <stdint.h>
#include "servers.h"
#include "functions.h"

void message_listen()
{
	// Server address structure initialization
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(MESSAGE_PORT);
    server.sin_addr.S_un.S_addr = INADDR_ANY;

	// Creating the socket
	SOCKET msg_sock = socket(AF_INET, SOCK_STREAM, 0);
	// Check if socket is ok
	if (msg_sock < 0)
		handle_error("socket() ");

	// Bind the socket to the previously set address
	int8_t result = bind(msg_sock, (SOCKADDR*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		handle_error("bind() ");

	// Start listening on the set socket with a predefined queue size
	result = listen(msg_sock, SOMAXCONN);
	// Check if listening is ok
	if (result < 0)
		handle_error("listen() ");

	// Create variables which will be used in the while loop
	SOCKADDR client;    // Client address structure
	SOCKET cli_sock;    // Slave socket definition, this will be used to store the incoming socket
	char buffer[256];   // Buffer for incoming and outgoing data
	int cntr = 1;       // Counter for incoming connections

    while (1) {
		// Accept the connection and save the incoming socket
		cli_sock = accept(msg_sock, &client, NULL);
		// Check if the socket is valid
		if (cli_sock < 0)
			handle_error("accept()");

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(cli_sock, buffer, 256, 0);
			if (received_bytes == 0) {
				printf("Connection closed, waiting for an other connection!\n");
			} else if (received_bytes == SOCKET_ERROR) {
				printf("Something went wrong with the client socket, trying to close it...\n");
				break;
			} else {
				// Terminate the string with zero
				buffer[received_bytes] = '\0';
				// Print out the received data
				printf("Received string: %s \n", buffer);
			}
		} while (received_bytes > 0);

		closesocket(cli_sock);
		printf("%d. client socket closed\n\n", cntr);
		cntr++;
    }

	closesocket(msg_sock);
	WSACleanup();
}


void disco_listen()
{
	// Server address structure initialization
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(DISCO_PORT);
    server.sin_addr.S_un.S_addr = INADDR_ANY;

	// Creating the socket
	SOCKET dis_sock = socket(AF_INET, SOCK_STREAM, 0);
	// Check if socket is ok
	if (dis_sock < 0)
		handle_error("socket() ");

	// Bind the socket to the previously set address
	int8_t result = bind(dis_sock, (SOCKADDR*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		handle_error("bind() ");

	// Start listening on the set socket with a predefined queue size
	result = listen(dis_sock, SOMAXCONN);
	// Check if listening is ok
	if (result < 0)
		handle_error("listen() ");

	// Create variables which will be used in the while loop
	SOCKADDR client;    // Client address structure
	SOCKET cli_sock;    // Slave socket definition, this will be used to store the incoming socket
	char buffer[256];   // Buffer for incoming and outgoing data
	int cntr = 1;       // Counter for incoming connections

    while (1) {
		// Accept the connection and save the incoming socket
		cli_sock = accept(dis_sock, &client, NULL);
		// Check if the socket is valid
		if (cli_sock < 0)
			handle_error("accept()");

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(cli_sock, buffer, 256, 0);
			if (received_bytes == 0) {
				printf("Connection closed, waiting for an other connection!\n");
			} else if (received_bytes == SOCKET_ERROR) {
				printf("Something went wrong with the client socket, trying to close it...\n");
				break;
			} else {
				// Terminate the string with zero
				buffer[received_bytes] = '\0';
				// Print out the received data
				printf("Received string: %s \n", buffer);
				// Send back the requested data
				send(cli_sock, buffer, received_bytes, 0);
			}
		} while (received_bytes > 0);

		closesocket(cli_sock);
		printf("%d. client socket closed\n\n", cntr);
		cntr++;
    }

	closesocket(dis_sock);
	WSACleanup();
}


void broadcast_listen()
{
	static int so_broadcast = 1;
	char message[30] = " ";

	// Creating the UDP socket
	SOCKET brdcst_sock = socket(AF_INET, SOCK_DGRAM, 0);
	// Check if socket is ok
	if (brdcst_sock < 0)
		handle_error("socket() ");

    // Set UDP broadcast
    setsockopt(brdcst_sock, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));

	// Server address structure initialization
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(BRDCST_PORT);
    server.sin_addr.S_un.S_addr = INADDR_ANY;

	// Bind the socket to the previously set address
	int8_t result = bind(brdcst_sock, (SOCKADDR*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		handle_error("bind() ");

    // Create address structure for client
    SOCKADDR_IN sender;
    int sender_size = sizeof(sender);

    // Handle incoming messages
    while(1) {
        recvfrom(brdcst_sock, message, sizeof(message), 0, (SOCKADDR*)&sender, &sender_size);

        char *begin = strtok(message, " ");
        char *end = strtok(NULL, "\"");
        if ((strstr(begin, "TOTORO") != NULL)) {
            uint16_t disco_port = atoi(end);
            char *sender_ip = inet_ntoa(sender.sin_addr);
            char msg[20] = "";
            strcpy(msg, my_name);
            strcat(msg, " ");
            char port[6];
            itoa(MESSAGE_PORT, port, 10);
            strcat(msg, port);
            tcp_send(sender_ip, disco_port, msg);
        }
    }
}
