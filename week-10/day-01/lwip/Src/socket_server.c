/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE_PORT		17777
#define BROADCAST_PORT		12345
#define TCP_QUEUE_SIZE      100

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	// Creating the socket
	int board_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	// Check if socket is ok
	if (board_socket < 0)
		LCD_ErrLog("Create socket error");

	// Creating the server address structure
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(MESSAGE_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the set address
	int8_t result = bind(board_socket, (struct sockaddr*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		LCD_ErrLog("Bind socket error");

	// Start listening on the set socket with a predefined queue size
	result = listen(board_socket, TCP_QUEUE_SIZE);
	// Check if listening is ok
	if (result < 0)
		LCD_ErrLog("Listen error");
	else
		LCD_UsrLog("The server is listening...");

	// Create variables which will be used in the while loop
	struct sockaddr_in client;          // Client address structure
	int client_size = sizeof(client);
	int client_socket;                  // Client socket definition, this will be used to store the incoming socket
	char message[100];           		// Buffer for incoming and outgoing data

    while (1) {
		// Accept the connection and save the incoming socket
		client_socket = accept(board_socket, &client, &client_size);
		// Check if the socket is valid
		if (client_socket < 0)
			LCD_ErrLog("Accept error");
		else
			LCD_UsrLog("Client connected");

		// Receive the data sent by the client
		uint8_t received_bytes;
		do {
			received_bytes = recv(client_socket, message, 100, 0);
			if (received_bytes == 0) {
				LCD_ErrLog("Connection closed, waiting for an other connection!");
			} else if (received_bytes < 0) {
				LCD_ErrLog("Something went wrong with the client socket, trying to close it...");
				break;
			} else {
				// Terminate the string with zero
				message[received_bytes] = '\0';
				LCD_UsrLog(message);
				send(client_socket , message , received_bytes , 0 );
			}
		} while (received_bytes > 0);

        closesocket(client_socket);
    }
    closesocket(board_socket);
}


int tcp_send(char *server_ip, int server_port, char *msg)
{
	// Creating client socket
	int cli_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (cli_sock < 0)
		LCD_ErrLog("Client socket error");

	// Creating server address
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = inet_addr(server_ip);

	// Connecting the client socket to the server
	int result = connect(cli_sock, (struct sockaddr*)&server, sizeof(server));
	if (result < 0) {
//		handle_error("tcp_send connect() ");
//      printf("\nThere was a TCP connect error, code %u"), WSAGetLastError();
        closesocket(cli_sock);
        return 1;
	}

    // Sending message
	result = send(cli_sock, msg, strlen(msg), 0);
	if (result < 0)
		LCD_ErrLog("CLient send error");
//    printf("Message \"%s\" sent\n", msg);
    closesocket(cli_sock);
    return 0;
}


void broadcast_listener_thread(void const *argument)
{
	char so_broadcast = '1';
	char message[30];

	// Creating the UDP socket
	int brdcst_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// Check if socket is ok
	if (brdcst_sock < 0)
		LCD_ErrLog("Socket error");

	// Set UDP broadcast
	setsockopt(brdcst_sock, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));

	// Server address structure initialization
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(BROADCAST_PORT);
	server.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the previously set address
	int8_t result = bind(brdcst_sock, (struct sockaddr*)&server, sizeof(server));
	// Check if the binding is ok
	if (result < 0)
		LCD_ErrLog("Bind error");

	// Create address structure for client
	struct sockaddr_in client;
	int client_size = sizeof(client);

	// Handle incoming messages
	while(1) {
		recvfrom(brdcst_sock, message, sizeof(message), 0, (struct sockaddr*)&client, &client_size);

		char *begin = strtok(message, " ");
		char *end = strtok(NULL, "\"");
		if ((strstr(begin, "TOTORO") != NULL)) {
			//Generate return message
			uint16_t disco_port = atoi(end);
			char *sender_ip = inet_ntoa(client.sin_addr);
			char msg[20] = "";
			strcpy(msg, "ST_Zoli");
			strcat(msg, " ");
			char port[6];
			itoa(MESSAGE_PORT, port, 10);
			strcat(msg, port);
			// Send message
			tcp_send(sender_ip, disco_port, msg);
		}
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
