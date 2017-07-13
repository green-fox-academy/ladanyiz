/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "stm32746g_discovery_ts.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	GPIO_TypeDef* GPIOx;
	uint16_t pin_no;
}cell_t;					// A structure that stores one LED (actually a pin)
TS_StateTypeDef ts_state;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef_a;
GPIO_InitTypeDef GPIO_InitDef_b;
GPIO_InitTypeDef GPIO_InitDef_c;
GPIO_InitTypeDef GPIO_InitDef_g;
GPIO_InitTypeDef GPIO_InitDef_h;
GPIO_InitTypeDef GPIO_InitDef_i;		// Structures for the six GPIO modules that control our pins

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS];

cell_t led_matrix_row[LED_MATRIX_ROWS] = {		// One row of LEDs (pins)
		{GPIOA, GPIO_PIN_15},
		{GPIOB, GPIO_PIN_9},
		{GPIOI, GPIO_PIN_2},
		{GPIOI, GPIO_PIN_0},
		{GPIOC, GPIO_PIN_6},
		{GPIOI, GPIO_PIN_3},
		{GPIOG, GPIO_PIN_6}
};

cell_t led_matrix_col[LED_MATRIX_COLS] = {		// One column of LEDs (pins)
		{GPIOI, GPIO_PIN_1},
		{GPIOB, GPIO_PIN_4},
		{GPIOG, GPIO_PIN_7},
		{GPIOA, GPIO_PIN_8},
		{GPIOH, GPIO_PIN_6}
};

// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);

// Mutex global variable
osMutexId led_matrix_mutex_id;

osMessageQDef(message_q, 1, uint16_t); // Declare a message queue
osMessageQId (message_q_id);           // Declare an ID for the message queue

/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
void led_matrix_clear();

/* Private functions ---------------------------------------------------------*/

// TODO:
// Write this function!
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state) {
	// TODO:
	// Wait for the mutex
	osMutexWait(led_matrix_mutex_id, osWaitForever);

	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state[row][col] = state;

	// TODO:
	// Release the mutex
	osMutexRelease(led_matrix_mutex_id);
}

void led_matrix_clear() {
	memset(led_matrix_state, 0, sizeof(led_matrix_state[0][0]) * 7 * 5);
}

// TODO:
// Write this function!
void led_matrix_update_thread(void const *argument)
{
	// TODO:
	// Initialize the pins as outputs and the led_matrix_state 2D array

	// Enable the clocks of the GPIO modules
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

	// Initialize the GPIO modules
	GPIO_InitDef_a.Pin = GPIO_PIN_8 | GPIO_PIN_15;
	GPIO_InitDef_a.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_a.Pull = GPIO_NOPULL;
	GPIO_InitDef_a.Speed = GPIO_SPEED_MEDIUM;

	GPIO_InitDef_b.Pin = GPIO_PIN_4 | GPIO_PIN_9;
	GPIO_InitDef_b.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_b.Pull = GPIO_NOPULL;
	GPIO_InitDef_b.Speed = GPIO_SPEED_MEDIUM;

	GPIO_InitDef_c.Pin = GPIO_PIN_6;
	GPIO_InitDef_c.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_c.Pull = GPIO_NOPULL;
	GPIO_InitDef_c.Speed = GPIO_SPEED_MEDIUM;

	GPIO_InitDef_g.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitDef_g.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_g.Pull = GPIO_NOPULL;
	GPIO_InitDef_g.Speed = GPIO_SPEED_MEDIUM;

	GPIO_InitDef_h.Pin = GPIO_PIN_6;
	GPIO_InitDef_h.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_h.Pull = GPIO_NOPULL;
	GPIO_InitDef_h.Speed = GPIO_SPEED_MEDIUM;

	GPIO_InitDef_i.Pin = GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3;
	GPIO_InitDef_i.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef_i.Pull = GPIO_NOPULL;
	GPIO_InitDef_i.Speed = GPIO_SPEED_MEDIUM;

	HAL_GPIO_Init(GPIOA, &GPIO_InitDef_a);
	HAL_GPIO_Init(GPIOB, &GPIO_InitDef_b);
	HAL_GPIO_Init(GPIOC, &GPIO_InitDef_c);
	HAL_GPIO_Init(GPIOG, &GPIO_InitDef_g);
	HAL_GPIO_Init(GPIOH, &GPIO_InitDef_h);
	HAL_GPIO_Init(GPIOI, &GPIO_InitDef_i);

	// Initialize the LED matrix state table
/*	for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
		for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
			led_matrix_state[r][c] = 0;
		}
	}
*/
	led_matrix_clear();

	// TODO:
	// Create a mutex
	// Use the LED_MATRIX_MUTEX_DEF
	led_matrix_mutex_id = osMutexCreate(osMutex(LED_MATRIX_MUTEX_DEF));

	LCD_UsrLog("led_matrix - initialized\n");

	// Infinite loop
	while (1) {
		// TODO:
		// Implement the led matrix updater functionality

		// Step 1:
		// Iterate through every column or row
		for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
			// Step 2:
			// Wait for the mutex
			osMutexWait(led_matrix_mutex_id, osWaitForever);

			// Step 3:
			// Turn on the column or row
			HAL_GPIO_WritePin(led_matrix_col[c].GPIOx, led_matrix_col[c].pin_no, 1);

			// Step 4:
			// Turn on the leds in that column or row
			for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
				HAL_GPIO_WritePin(led_matrix_row[r].GPIOx, led_matrix_row[r].pin_no, !led_matrix_state[r][c]);
			}

			// Step 5:
			// Release the mutex
			osMutexRelease(led_matrix_mutex_id);

			// Step 6:
			// Delay
			osDelay(5);

			// Step 7:
			// Turn off the column or row
			HAL_GPIO_WritePin(led_matrix_col[c].GPIOx, led_matrix_col[c].pin_no, 0);
		}
	}

	// Terminating thread
	while (1) {
		LCD_ErrLog("led_matrix - terminating...\n");
		osThreadTerminate(NULL);
	}
}

// This thread is a waterfall type animation
void led_matrix_waterfall_thread(void const *argument)
{
//	uint8_t x = 7;
//	uint8_t y = 5;
	uint8_t d = 54;
	while (1) {
/*		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
				led_matrix_set(r, c, 1);
				osEvent event = osMessageGet(message_q_id, osWaitForever);
				osDelay(event.value.v);
				led_matrix_set(r, c, 0);
			}
		}
*/
/*
		BSP_TS_GetState(&ts_state);
		if (ts_state.touchDetected) {
			if (ts_state.touchX[0] < 380) {
				if (ts_state.touchX[0] < d + 2) {
					led_matrix_set(x, y, 0);
					x = 6;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else if (ts_state.touchX[0] < 2 * d + 2) {
					led_matrix_set(x, y, 0);
					x = 5;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else if (ts_state.touchX[0] < 3 * d + 2) {
					led_matrix_set(x, y, 0);
					x = 4;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else if (ts_state.touchX[0] < 4 * d + 2) {
					led_matrix_set(x, y, 0);
					x = 3;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else if (ts_state.touchX[0] < 5 * d + 2) {
					led_matrix_set(x, y, 0);
					x = 2;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else if (ts_state.touchX[0] < 6 * d + 2) {
					led_matrix_set(x, y, 0);
					x = 1;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				} else {
					led_matrix_set(x, y, 0);
					x = 0;
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_set(x, y, 0);
						y = 0;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 1;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 2;
						led_matrix_set(x, y, 1);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_set(x, y, 0);
						y = 3;
						led_matrix_set(x, y, 1);
					} else {
						led_matrix_set(x, y, 0);
						y = 4;
						led_matrix_set(x, y, 1);
					}
				}
			}
		} else if (x != 500) {
			led_matrix_set(x, y, 0);
		}
*/
		BSP_TS_GetState(&ts_state);
		if (ts_state.touchDetected) {
			if (ts_state.touchX[0] < 8 * d + 2) {
				if (ts_state.touchX[0] < d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 0, 1, 0},
							{0, 1, 0, 1, 0},
							{0, 1, 0, 1, 0},
							{0, 0, 1, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{0, 0, 0, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 2 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 1, 0, 1},
							{1, 0, 1, 0, 1},
							{0, 1, 0, 1, 0},
							{0, 1, 0, 1, 0},
							{0, 1, 0, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 1, 1, 0},
							{0, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 3 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 1, 1},
							{0, 1, 1, 1, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 0, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 0, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 0, 0, 1, 0},
							{0, 0, 1, 1, 0},
							{0, 1, 0, 1, 0},
							{1, 1, 1, 1, 1},
							{0, 0, 0, 1, 0},
							{0, 0, 0, 1, 0},
							{0, 0, 0, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 4 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 1, 0},
							{1, 0, 1, 0, 0},
							{1, 1, 0, 0, 0},
							{1, 0, 1, 0, 0},
							{1, 0, 0, 1, 0},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0},
							{1, 0, 1, 0, 0},
							{1, 0, 0, 1, 0},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 0, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 0},
							{0, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 5 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 0},
							{0, 1, 1, 1, 0},
							{0, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 0, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 6 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 1, 0, 1, 1},
							{1, 0, 1, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 1, 0, 0, 1},
							{1, 0, 1, 0, 1},
							{1, 0, 0, 1, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 1, 1, 1, 1},
							{0, 0, 0, 0, 1},
							{0, 0, 0, 1, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 0, 0, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 7 * d + 2) {
					if (ts_state.touchY[0] < d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 0},
							{1, 0, 1, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 2 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 1, 0, 0, 1},
							{1, 0, 1, 0, 1},
							{1, 0, 0, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 3 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else if (ts_state.touchY[0] < 4 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 0, 1, 0, 0},
							{0, 1, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 0, 1, 0, 0},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					} else {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				} else if (ts_state.touchX[0] < 8 * d + 2) {
					if (ts_state.touchY[0] < 5 * d + 2) {
						led_matrix_clear();
						GPIO_PinState temp_matrix[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
							{0, 1, 1, 1, 0},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 1},
							{0, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{0, 1, 1, 1, 0}
						};
						memcpy(led_matrix_state, temp_matrix, sizeof(led_matrix_state[0][0]) * LED_MATRIX_ROWS * LED_MATRIX_COLS);
					}
				}
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}

// ADC thread, writing into the message queue
void adc_thread(void const *argument)
{
	message_q_id = osMessageCreate(osMessageQ(message_q), NULL);
	while (1) {
//		LCD_UsrLog("%u\n", adc_measure());
		osMessagePut(message_q_id, adc_measure(), osWaitForever);
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
