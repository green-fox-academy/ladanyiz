/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	GPIO_TypeDef GPIOx;
	uint16_t pin_no;
	GPIO_PinState state;
}cell_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef_a;
GPIO_InitTypeDef GPIO_InitDef_b;
GPIO_InitTypeDef GPIO_InitDef_c;
GPIO_InitTypeDef GPIO_InitDef_g;
GPIO_InitTypeDef GPIO_InitDef_h;
GPIO_InitTypeDef GPIO_InitDef_i;

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS];

cell_t led_matrix_row[LED_MATRIX_ROWS] = {
		{GPIOA, GPIO_PIN_15, GPIO_PIN_RESET},
		{GPIOB, GPIO_PIN_9, GPIO_PIN_RESET},
		{GPIOI, GPIO_PIN_2, GPIO_PIN_RESET},
		{GPIOI, GPIO_PIN_0, GPIO_PIN_RESET},
		{GPIOC, GPIO_PIN_6, GPIO_PIN_RESET},
		{GPIOI, GPIO_PIN_3, GPIO_PIN_RESET},
		{GPIOG, GPIO_PIN_6, GPIO_PIN_RESET},
};

cell_t led_matrix_col[LED_MATRIX_COLS] = {
		{GPIOI, GPIO_PIN_1, GPIO_PIN_RESET},
		{GPIOB, GPIO_PIN_4, GPIO_PIN_RESET},
		{GPIOG, GPIO_PIN_7, GPIO_PIN_RESET},
		{GPIOA, GPIO_PIN_8, GPIO_PIN_RESET},
		{GPIOH, GPIO_PIN_6, GPIO_PIN_RESET},
};

// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);

// Mutex global variable
osMutexId led_matrix_mutex_id;

/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
/* Private functions ---------------------------------------------------------*/

// TODO:
// Write this function!
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state) {
	// TODO:
	// Wait for the mutex

	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state[row][col] = state;

	// TODO:
	// Release the mutex
}

// TODO:
// Write this function!
void led_matrix_update_thread(void const *argument)
{
	// TODO:
	// Initialize the pins as outputs and the led_matrix_state 2D array

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

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

	for (uint8_t i = 0; i < LED_MATRIX_ROWS; i++) {
		for (uint8_t j = 0; j < LED_MATRIX_COLS; j++) {
			led_matrix_state[i, j] = GPIO_PIN_RESET;
		}
	}

	// TODO:
	// Create a mutex
	// Use the LED_MATRIX_MUTEX_DEF

	LCD_UsrLog("led_matrix - initialized\n");

	// Infinite loop
	while (1) {
		// TODO:
		// Implement the led matrix updater functionality
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		led_matrix_state[0][0] = GPIO_PIN_SET;
		HAL_GPIO_WritePin(&led_matrix_col[0].GPIOx, led_matrix_col[0].pin_no, led_matrix_state[0][0]);
		for (uint8_t i = 1; i < LED_MATRIX_ROWS; i++) {
			HAL_GPIO_WritePin(&led_matrix_row[i].GPIOx, led_matrix_row[i].pin_no, !led_matrix_state[0][0]);
		}
		// Step 1:
		// Iterate through every column or row

			// Step 2:
			// Wait for the mutex


			// Step 3:
			// Turn on the column or row


			// Step 4:
			// Turn on the leds in that column or row


			// Step 5:
			// Release the mutex


			// Step 6:
			// Delay


			// Step 7:
			// Turn off the column or row
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
	while (1) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
				led_matrix_set(r, c, 1);
				osDelay(50);
				led_matrix_set(r, c, 0);
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
