#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
#include <stdint.h>
#include "header.h"


void broadcast_listen()
{
	char so_broadcast = '1';
	char message[30];

	// Creating the UDP socket
	SOCKET brdcst_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// Check if socket is ok
	if (brdcst_sock < 0)
		handle_error("socket() ");
    fprintf(file, "%s\tbroadcast listener socket no. u% created", timestamp(), brdcst_sock);

    // Set UDP broadcast
    setsockopt(brdcst_sock, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));

	// Server address structure initialization
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(BRDCST_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the previously set address
	int8_t result = bind(brdcst_sock, (SOCKADDR*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		handle_error("bind() ");

    // Create address structure for client
    SOCKADDR_IN client;
    int client_size = sizeof(client);

    // Handle incoming messages
    while(1) {
        recvfrom(brdcst_sock, message, sizeof(message), 0, (SOCKADDR*)&client, &client_size);

        char *begin = strtok(message, " ");
        char *end = strtok(NULL, "\"");
        if ((strstr(begin, "TOTORO") != NULL)) {
            //Generate return message
            uint16_t disco_port = atoi(end);
            char *sender_ip = inet_ntoa(client.sin_addr);
            char msg[20] = "";
            strcpy(msg, my_name);
            strcat(msg, " ");
            char port[6];
            itoa(MESSAGE_PORT, port, 10);
            strcat(msg, port);
            // Send message
            tcp_send(sender_ip, disco_port, msg);
        }
    }
}


void disco_listen()
{
	// Creating the socket
	SOCKET dis_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	// Check if socket is ok
	if (dis_sock < 0)
		handle_error("socket() ");

	// Creating the server address structure
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(DISCO_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the set address
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
	SOCKADDR_IN client;                 // Client address structure
	int client_size = sizeof(client);
	SOCKET cli_sock;                    // Client socket definition, this will be used to store the incoming socket
	char message[30];                   // Buffer for incoming and outgoing data

    while (1) {
		// Accept the connection and save the incoming socket
		cli_sock = accept(dis_sock, &client, &client_size);
		// Check if the socket is valid
		if (cli_sock < 0)
			handle_error("accept()");

		// Receive the data sent by the client
        uint16_t received_bytes = recv(cli_sock, message, 30, 0);
        if (received_bytes == 0) {
            printf("\nConnection closed, waiting for an other connection!");
        } else if (received_bytes == SOCKET_ERROR) {
            printf("\nSomething went wrong with the client socket, trying to close it...");
            break;
        } else {
            // Terminate the string with zero
            message[received_bytes] = '\0';

            // Checking if user is already stored, based on IP address
            uint8_t found = 0;
            if (list_size > 0) {
                char ip[20];
                strcpy(ip, inet_ntoa(client.sin_addr));
                for (uint8_t i = 0; i < list_size; i++) {
                    if (strstr(ip, user_list[i].ip) != 0) {
                        found = 1;
                        break;
                    }
                }
            }

            // If the client IP is new, fill the user structure with the data
            if (found == 0) {
                strcpy(user_list[list_size].ip, inet_ntoa(client.sin_addr));
                strcpy(user_list[list_size].name, strtok(message, " "));
                user_list[list_size].port = atoi(strtok(NULL, "\n"));
                list_size++;
            }
        }
		closesocket(cli_sock);
    }
	closesocket(dis_sock);
}


void message_listen()
{
	// Creating the socket
	SOCKET msg_sock = socket(AF_INET, SOCK_STREAM, 0);
	// Check if socket is ok
	if (msg_sock < 0)
		handle_error("socket() ");

	// Creating the server address structure
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(MESSAGE_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the set address
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
	SOCKADDR_IN client;     // Client address structure
	int client_size = sizeof(client);
	SOCKET cli_sock;        // Client socket definition, this will be used to store the incoming socket
	char message[256];      // Buffer for incoming and outgoing data

    while (1) {
		// Accept the connection and save the incoming socket
		cli_sock = accept(msg_sock, &client, &client_size);
		// Check if the socket is valid
		if (cli_sock < 0)
			handle_error("accept()");

		// Receive the data sent by the client
		int received_bytes = recv(cli_sock, message, 256, 0);
        if (received_bytes == 0) {
            printf("\nConnection closed, waiting for an other connection!\n");
        } else if (received_bytes == SOCKET_ERROR) {
            printf("\nSomething went wrong with the client socket, trying to close it...\n");
            break;
        } else {
            // Terminate the string with zero
            message[received_bytes] = '\0';
            // Print out the received data
            char *ip = inet_ntoa(client.sin_addr);
            char name[15] = "Unknown user";
            int8_t index = -1;
            if (list_size > 0) {
                for (uint8_t i = 0; i < list_size; i++) {
                    if (strstr(ip, user_list[i].ip) != NULL) {
                        index = i;
                    }
                }
            }
            if (index > -1) {
                strcpy(name, user_list[index].name);
            }
            printf("\n%s: %s", name, message);
        }
		closesocket(cli_sock);
    }
	closesocket(msg_sock);
}
