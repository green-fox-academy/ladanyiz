#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
#include <stdint.h>
#include "tmp.h"

void handle_error(const char *error_string)
{
	printf("Error: %s\nError code: %d\n", error_string, WSAGetLastError());
	WSACleanup();
	printf("Press any key to exit from the program...");
	while (!kbhit());
	exit(EXIT_FAILURE);
}


void wsa_init()
{
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != NO_ERROR)
		handle_error("WSAStartup() ");
}


void start_screen()
{
	printf("\n");
	printf("                   Totoro chat\n");
	printf("==========================================================\n");
	printf("Commands:\n");
	printf("h\tDisplay this help info\n");
	printf("e\tExit\n");
	printf("n\tSet user name\n");
	printf("l\tList known users\n");
	printf("d\tSend discovery request\n");
	printf("m\tSend message\n");
	printf("==========================================================\n\n");
}


void broadcast()
{
	int so_broadcast = 1;

	// Server address structure initialization
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(BRDCST_PORT);
    server.sin_addr.S_un.S_addr = BRDCST_IP;

	// Creating the UDP socket
	SOCKET brdcst_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// Check if socket is ok
	if (brdcst_sock < 0)
		handle_error("socket() ");

    // Set UDP broadcast
    setsockopt(brdcst_sock, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));

	// Connecting the client socket to the server
	int8_t result = connect(brdcst_sock, (SOCKADDR*)&server, sizeof(server));
	if (result < 0)
		handle_error("connect() ");

    // Create and send message
    char msg[30] = "TOTORO ";
    char port[6];
    itoa(DISCO_PORT, port, 10);
    strcat(msg, port);
	result = send(brdcst_sock, msg, strlen(msg), 0);
	if (result < 0)
		handle_error("send() ");
    printf("Discovery request \"%s\" sent\n", msg);

    closesocket(brdcst_sock);
}


void tcp_send(char *server_ip, uint16_t server_port, char *msg)
{
	// Creating client socket
	SOCKET cli_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (cli_sock < 0)
		handle_error("socket() ");

	// Creating server address
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = inet_addr(server_ip);

	// Connecting the client socket to the server
	int result = connect(cli_sock, (SOCKADDR*)&server, sizeof(server));
	if (result < 0)
		handle_error("connect() ");

    // Sending message
	result = send(cli_sock, msg, strlen(msg), 0);
	if (result < 0)
		handle_error("send() ");
    printf("Message \"%s\" sent\n", msg);
    closesocket(cli_sock);
}


void list_users()
{
    if (list_size == 0) {
        printf("User list is empty\n");
    } else {
        puts("Users:");
        for (uint8_t i = 0; i < list_size; i++) {
            printf("%s\t%d\t%s\n", user_list[i].ip, user_list[i].port, user_list[i].name);
        }
        printf("\n");
    }
}


uint8_t send_message()
{
    // Check if there is anyone to send to
    if (list_size == 0) {
        puts("User list is empty");
        return 1;
    }
    char *buffer;
    char *message;
    printf("Enter <user name> <message>: ");
    // Get string
    gets(buffer);
    // Cut the name part
    char *name = strtok(buffer, " ");
    int8_t index = -1;
    for (uint8_t i = 0; i < list_size; i++) {
        // If name is found, save its index and exit the loop
        if (strstr(name, user_list[i].name) != NULL) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        puts("Name not found\n");
        return 1;
    } else {
        // Cut the message part
        message = strtok(NULL, "\n");
        // Send the message
        tcp_send(user_list[index].ip, user_list[index].port, message);
    }
    return 0;
}
