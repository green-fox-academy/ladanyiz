/**
 ******************************************************************************
 * @file    USB_Device/HID_Standalone/Src/main.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    30-December-2016
 * @brief   USB device HID demo main file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint32_t addr[2];
	uint32_t width;
	uint32_t height;
	uint32_t front;
} Screen;

/* Private define ------------------------------------------------------------*/
#define ABS(X)  ((X) > 0 ? (X) : -(X))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t radius = 3;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
static void MPU_Config(void);
static void LCD_Config(void);
void BSP_LCD_ZDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

Screen* ct_screen_init();
void ct_screen_flip_buffers(Screen *screen);
uint32_t* ct_screen_backbuffer_ptr(Screen *screen);
uint32_t ct_screen_backbuffer_id(Screen *screen);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {

	/* This project template calls firstly two functions in order to configure MPU feature
	 and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
	 These functions are provided as template implementation that User may integrate
	 in his application, to enhance the performance in case of use of AXI interface
	 with several masters. */

	/* Configure the MPU attributes as Write Through */
	MPU_Config();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	 - Configure the Flash ART accelerator on ITCM interface
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();

	static Screen *screen;
	screen = ct_screen_init();

	LCD_Config();
	
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	TS_StateTypeDef ts_state;

	uint16_t px = 1000;
	uint16_t py = 1000;
	uint16_t x, y;

	while (1) {
		BSP_TS_GetState(&ts_state);
		if (ts_state.touchDetected) {
			// tools screen
			if (screen->front == 1) {
				// first row of colors
				BSP_LCD_SelectLayer(0);
				if (ts_state.touchY[0] > 112 && ts_state.touchY[0] < 165) {
					if (ts_state.touchX[0] < 55) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);
					} else if (ts_state.touchX[0] < 108) {
						BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
					} else if (ts_state.touchX[0] < 161) {
						BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
					} else if (ts_state.touchX[0] < 214) {
						BSP_LCD_SetTextColor(LCD_COLOR_RED);
					} else if (ts_state.touchX[0] < 267) {
						BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					} else if (ts_state.touchX[0] < 320) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTRED);
					} else if (ts_state.touchX[0] < 373) {
						BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
					} else if (ts_state.touchX[0] < 426) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);
					}
				// second row of colors
				} else if (ts_state.touchY[0] > 165 && ts_state.touchY[0] < 218) {
					if (ts_state.touchX[0] < 55) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKYELLOW);
					} else if (ts_state.touchX[0] < 108) {
						BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
					} else if (ts_state.touchX[0] < 161) {
						BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					} else if (ts_state.touchX[0] < 214) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
					} else if (ts_state.touchX[0] < 267) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTCYAN);
					} else if (ts_state.touchX[0] < 320) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
					} else if (ts_state.touchX[0] < 373) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
					} else if (ts_state.touchX[0] < 426) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTMAGENTA);
					}
				// third row of colors
				} else if (ts_state.touchY[0] > 218 && ts_state.touchY[0] < 271) {
					if (ts_state.touchX[0] < 55) {
						BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
					} else if (ts_state.touchX[0] < 108) {
						BSP_LCD_SetTextColor(LCD_COLOR_BROWN);
					} else if (ts_state.touchX[0] < 161) {
						BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
					} else if (ts_state.touchX[0] < 214) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
					} else if (ts_state.touchX[0] < 267) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKCYAN);
					} else if (ts_state.touchX[0] < 320) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
					} else if (ts_state.touchX[0] < 373) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);
					} else if (ts_state.touchX[0] < 426) {
						BSP_LCD_SetTextColor(LCD_COLOR_DARKMAGENTA);
					}
				// tools row
				} else if (ts_state.touchY[0] < 41) {
					if (ts_state.touchX[0] < 41) {
						BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
					} else if (ts_state.touchX[0] < 82) {
						radius = 2;
					} else if (ts_state.touchX[0] < 123) {
						radius = 5;
					} else if (ts_state.touchX[0] < 164) {
						radius = 8;
					} else if (ts_state.touchX[0] < 205) {
						radius = 11;
					} else if (ts_state.touchX[0] < 246) {
						radius = 14;
					}
				}
			// drawing screen
			} else if (ts_state.touchX[0] > 13 && ts_state.touchX[0] < 467 && ts_state.touchY[0] > 13 && ts_state.touchY[0] < 259) {
				if (px == 1000) {
					px = ts_state.touchX[0];
					py = ts_state.touchY[0];
				} else {
					x = ts_state.touchX[0];
					y = ts_state.touchY[0];
					BSP_LCD_ZDrawLine(px, py, x, y);
					px = x;
					py = y;
				}
			}
		} else {
			px = 1000;
			py = 1000;
		}
		if (BSP_PB_GetState(BUTTON_KEY) == 1) {
			ct_screen_flip_buffers(screen);
		}
	}
}


Screen* ct_screen_init() {
	BSP_LCD_Init();
	Screen *screen = (Screen*) malloc(sizeof(Screen));
	screen->width = BSP_LCD_GetXSize();
	screen->height = BSP_LCD_GetYSize();
	screen->addr[0] = LCD_FB_START_ADDRESS;
	screen->addr[1] = LCD_FB_START_ADDRESS + screen->width * screen->height * 4;
	screen->front = 1;
	BSP_LCD_LayerDefaultInit(0, screen->addr[0]);
	BSP_LCD_LayerDefaultInit(1, screen->addr[1]);
	BSP_LCD_SetLayerVisible(0, DISABLE);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	BSP_LCD_SelectLayer(0);
	return screen;
}


static void LCD_Config(void)
{
	/* LCD Initialization */
//	BSP_LCD_Init();

	/* LCD Initialization */
//	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
//	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS+(BSP_LCD_GetXSize()*BSP_LCD_GetYSize()*4));

	/* Enable the LCD */
//	BSP_LCD_DisplayOn();

	/* Select the LCD Background Layer  */
	BSP_LCD_SelectLayer(0);

	/* Clear the Background Layer */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Select the LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	/* Clear the Foreground Layer */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Configure the transparency for foreground and background :
	 Increase the transparency */
//	BSP_LCD_SetTransparency(0, 0);
//	BSP_LCD_SetTransparency(1, 255);

	BSP_LCD_SelectLayer(1);

	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(3, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_BROWN);
	BSP_LCD_FillRect(56, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
	BSP_LCD_FillRect(109, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_FillRect(162, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKCYAN);
	BSP_LCD_FillRect(215, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
	BSP_LCD_FillRect(268, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_FillRect(321, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKMAGENTA);
	BSP_LCD_FillRect(374, 219, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKYELLOW);
	BSP_LCD_FillRect(3, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(56, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(109, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_FillRect(162, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTCYAN);
	BSP_LCD_FillRect(215, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	BSP_LCD_FillRect(268, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
	BSP_LCD_FillRect(321, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTMAGENTA);
	BSP_LCD_FillRect(374, 166, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);
	BSP_LCD_FillRect(3, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
	BSP_LCD_FillRect(56, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
	BSP_LCD_FillRect(109, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(162, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(215, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTRED);
	BSP_LCD_FillRect(268, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_FillRect(321, 113, 50, 50);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);
	BSP_LCD_FillRect(374, 113, 50, 50);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	BSP_LCD_DrawCircle(20, 20, 12);

	BSP_LCD_DrawVLine(41, 0, 41);
	BSP_LCD_DrawVLine(82, 0, 41);
	BSP_LCD_DrawVLine(123, 0, 41);
	BSP_LCD_DrawVLine(164, 0, 41);
	BSP_LCD_DrawVLine(205, 0, 41);
	BSP_LCD_DrawVLine(246, 0, 41);

	BSP_LCD_DrawHLine(0, 41, 480);

	BSP_LCD_FillCircle(62, 20, 2);
	BSP_LCD_FillCircle(103, 20, 5);
	BSP_LCD_FillCircle(144, 20, 8);
	BSP_LCD_FillCircle(185, 20, 11);
	BSP_LCD_FillCircle(226, 20, 14);

	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
}


uint32_t ct_screen_backbuffer_id(Screen *screen) {
	return 1 - screen->front;
}


void BSP_LCD_ZDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0,
	curpixel = 0;

	deltax = ABS(x2 - x1);        /* The difference between the x's */
	deltay = ABS(y2 - y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1) {               /* The x-values are increasing */
		xinc1 = 1;
		xinc2 = 1;
	} else {                      /* The x-values are decreasing */
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {               /* The y-values are increasing */
		yinc1 = 1;
		yinc2 = 1;
	} else {                      /* The y-values are decreasing */
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay) {       /* There is at least one x-value for every y-value */
		xinc1 = 0;                /* Don't change the x when numerator >= denominator */
		yinc2 = 0;                /* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		num_add = deltay;
		num_pixels = deltax;	  /* There are more x-values than y-values */
	} else {                      /* There is at least one y-value for every x-value */
		xinc2 = 0;                /* Don't change the x for every iteration */
		yinc1 = 0;                /* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		num_add = deltax;
		num_pixels = deltay;      /* There are more y-values than x-values */
	}

	for (curpixel = 0; curpixel <= num_pixels; curpixel++) {
		BSP_LCD_FillCircle(x, y, radius);   	  /* Draw the current circle */
		num += num_add;                           /* Increase the numerator by the top of the fraction */
		if (num >= den) {                         /* Check if numerator >= denominator */
		  num -= den;                             /* Calculate the new numerator value */
		  x += xinc1;                             /* Change the x as appropriate */
		  y += yinc1;                             /* Change the y as appropriate */
		}
		x += xinc2;                               /* Change the x as appropriate */
		y += yinc2;                               /* Change the y as appropriate */
	}
}


void ct_screen_flip_buffers(Screen *screen) {
	// wait for VSYNC
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	BSP_LCD_SetLayerVisible(screen->front, DISABLE);
	screen->front ^= 1;
	BSP_LCD_SetLayerVisible(screen->front, ENABLE);
//	BSP_LCD_SelectLayer(ct_screen_backbuffer_id(screen));
	BSP_LCD_SelectLayer(screen->front);
}


uint32_t* ct_screen_backbuffer_ptr(Screen *screen) {
	return (uint32_t*)(screen->addr[ct_screen_backbuffer_id(screen)]);
}


/**
 * @brief This function provides accurate delay (in milliseconds) based
 *        on SysTick counter flag.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay: specifies the delay time length, in milliseconds.
 * @retval None
 */
void HAL_Delay(__IO uint32_t Delay) {
	while (Delay) {
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
			Delay--;
		}
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */

static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

static void CPU_CACHE_Enable(void) {
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
