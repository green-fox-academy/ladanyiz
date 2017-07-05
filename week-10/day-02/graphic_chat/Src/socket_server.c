/* Includes ------------------------------------------------------------------*/
#include "socket_server.h"
#include "socket_client.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE_PORT		17777
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
	int buffer[4];           		// Buffer for incoming and outgoing data

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
			received_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
			if (received_bytes == 0) {
				LCD_ErrLog("Connection closed, waiting for an other connection!");
			} else if (received_bytes < 0) {
				LCD_ErrLog("Something went wrong with the client socket, trying to close it...");
				break;
			} else if (buffer[2] == 1) {
				prepare_screen();
			} else {
				BSP_LCD_SetTextColor(buffer[3]);
				BSP_LCD_FillCircle(buffer[0], buffer[1], 3);
			}
		} while (received_bytes > 0);

        closesocket(client_socket);
    }
    closesocket(board_socket);

    while (1) {
      osThreadTerminate(NULL);
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
