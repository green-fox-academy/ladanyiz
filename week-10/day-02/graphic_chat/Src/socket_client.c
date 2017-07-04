/* Includes ------------------------------------------------------------------*/
#include "socket_client.h"
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SERVER_PORT		54545
#define SERVER_IP		"10.27.6.129"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void terminate_thread()
{
	while (1)
		osThreadTerminate(NULL);
}

// TODO:
// Implement this function!
void socket_client_thread(void const *argument)
{
	LCD_UsrLog("Socket server - startup...\n");
	LCD_UsrLog("Socket server - waiting for IP address...\n");

	// Wait for an IP address
	while (!is_ip_ok())
		osDelay(10);
	LCD_UsrLog("Socket server - IP address is ok\n");

    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
		LCD_ErrLog("Can't create client socket\n");
		terminate_thread();
    }
	LCD_UsrLog("Client socket created\n");

    // Create server address structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    //Connect to remote server
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
		LCD_ErrLog("Can't connect to server\n");
		terminate_thread();
    }
	LCD_UsrLog("Connected to server\n");

	// Clear the screen for drawing
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	TS_StateTypeDef ts_state;
	uint8_t radius = 3;

    //Send some data
    char x[10];
    char y[10];
    char data[30];
    while(1) {
    	BSP_TS_GetState(&ts_state);
    	if (ts_state.touchDetected && ts_state.touchX[0] > 3 && ts_state.touchX[0] < 477 && ts_state.touchY[0] > 3 && ts_state.touchY[0] < 269) {
    		BSP_LCD_FillCircle(ts_state.touchX[0], ts_state.touchY[0], radius);
    		sprintf(x, "%d", ts_state.touchX[0]);
    		sprintf(y, "%d", ts_state.touchY[0]);
    		strcpy(data, x);
    		strcat(data, " ");
    		strcat(data, y);
    		strcat(data, " ");
			if (send(client_socket, data, strlen(data), 0) < 0)
			{
				LCD_ErrLog("Send failed\n");
				terminate_thread();
			}
/*			if (send(client_socket, y, strlen(y), 0) < 0)
			{
				LCD_ErrLog("Send failed\n");
				terminate_thread();
			} */
			osDelay(5);
			if (BSP_PB_GetState(BUTTON_KEY) == 1)
				BSP_LCD_Clear(LCD_COLOR_WHITE);
    	}
    	osDelay(5);
 /*
        //Receive a reply from the server
        char server_reply[100];
        int recv_size = recv(client_socket, server_reply, 100, 0);
        if (recv_size < 0) {
    		LCD_ErrLog("Receive failed\n");
    		terminate_thread();
        }
        //Add a NULL terminating character to make it a proper string before printing
        server_reply[recv_size] = '\0';
        LCD_UsrLog("Reply:\n");
        LCD_UsrLog("%s\n\n", server_reply);
*/
    }

    closesocket(client_socket);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
