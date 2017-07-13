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
GPIO_InitTypeDef GPIO_InitDef;		// Structure with initializing info for the GPIO ports

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
	// These three settings are commmon for all the six ports
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_MEDIUM;

	// Set the pins for the given port, then initialize it. Repeat for all six ports.
	GPIO_InitDef.Pin = GPIO_PIN_8 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOA, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_4 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOB, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOG, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOH, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3;
	HAL_GPIO_Init(GPIOI, &GPIO_InitDef);

	// Initialize the LED matrix state table
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

// This thread was a waterfall type animation originally, now it fills the led_matrix_state table based on where the screen is touched
void led_matrix_waterfall_thread(void const *argument)
{
	uint8_t x = 7;
	uint8_t y = 5;
	uint8_t d = 54;
	while (1) {
		BSP_TS_GetState(&ts_state);
		if (ts_state.touchDetected) {
			if (ts_state.touchX[0] < 380) {
				led_matrix_set(x, y, 0);
				x = 6 - ts_state.touchX[0] / d;
				y = ts_state.touchY[0] / d;
				led_matrix_set(x, y, 1);
			}
		} else if (x != 7) {
			led_matrix_set(x, y, 0);
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
