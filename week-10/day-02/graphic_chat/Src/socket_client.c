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

void prepare_screen() {
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(441, 0, 39, 46);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(441, 46, 39, 45);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(441, 91, 39, 45);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_FillRect(441, 136, 39, 45);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(441, 181, 39, 45);
	BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
	BSP_LCD_FillRect(441, 226, 39, 46);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
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
    int8_t connect_result = -1;
	LCD_UsrLog("Waiting for server...\n");
    do {
    	connect_result = connect(client_socket, (struct sockaddr*)&server, sizeof(server));
    	osDelay(500);
    } while (connect_result < 0);
	LCD_UsrLog("Connected to server\n");

	// Clear the screen for drawing
//	prepare_screen();

    //Check touch screen and send data
	TS_StateTypeDef ts_state;
	uint8_t radius = 3;
	uint32_t buffer[4] = {0, 0, 0, 0};		// Array elements: {X coordinate, Y coordinate, clear, color}

    while(1) {
    	BSP_TS_GetState(&ts_state);
    	// If color panel is touched
		if (ts_state.touchDetected && ts_state.touchX[0] > 440) {
			if (ts_state.touchY[0] < 47) {
				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
				buffer[3] = LCD_COLOR_BLACK;
			} else if (ts_state.touchY[0] < 92) {
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
				buffer[3] = LCD_COLOR_RED;
			} else if (ts_state.touchY[0] < 137) {
				BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
				buffer[3] = LCD_COLOR_GREEN;
			} else if (ts_state.touchY[0] < 182) {
				BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
				buffer[3] = LCD_COLOR_YELLOW;
			} else if (ts_state.touchY[0] < 227) {
				BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
				buffer[3] = LCD_COLOR_BLUE;
			} else {
				BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
				buffer[3] = LCD_COLOR_ORANGE;
			}
		// If drawing area is touched
		} else if (ts_state.touchDetected && ts_state.touchX[0] > 3 && ts_state.touchX[0] < 437 && ts_state.touchY[0] > 3 && ts_state.touchY[0] < 269) {
    		buffer[0] = ts_state.touchX[0];
    		buffer[1] = ts_state.touchY[0];
    		BSP_LCD_FillCircle(buffer[0], buffer[1], radius);
    		//Send data
			if (send(client_socket, buffer, sizeof(buffer), 0) < 0)
			{
				LCD_ErrLog("Send failed\n");
				terminate_thread();
			}

//			osDelay(3);
    	}
		// If button pushed, clear and send clear
		if (BSP_PB_GetState(BUTTON_KEY) == 1) {
			prepare_screen();
			buffer[2] = 1;
			if (send(client_socket, buffer, sizeof(buffer), 0) < 0)
				{
					LCD_ErrLog("Send failed\n");
					terminate_thread();
				}
			buffer[2] = 0;
		}

    	osDelay(1);
    }

    closesocket(client_socket);

    while (1) {
      osThreadTerminate(NULL);
    }

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
