/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mpr.h"
#include "usbd_hid.h"
//extern uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
struct send_data my_data;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define ws2812_zero 0xC0
#define ws2812_one  0xF8

uint8_t ws_peach[48] ={ 0x98,0xFF,0xE4,//0 right
											  0x98,0xFF,0xE4,//1
												0x98,0xFF,0xE4,//2
												0x98,0xFF,0xE4,//3
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,
												0x98,0xFF,0xE4,//10
												0x98,0xFF,0xE4,//11
												0x98,0xFF,0xE4,//12
												0x98,0xFF,0xE4,//13
												0x98,0xFF,0xE4,//14
												0x98,0xFF,0xE4,//15
												};//G R B
 uint8_t WS_scan=0;
volatile uint8_t refresh_flag=0;												
void refresh_Color()
{
			for(uint16_t i=0;i<384.;i++)
			{
				while(!(SPI2->SR&(1<<1)))
				{			
				}
				if((ws_peach[i/8]&(1<<(i%8))))
				{
					SPI2->DR=ws2812_one;
				}
				else
				{
					SPI2->DR=ws2812_zero;
				}	
			}
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t times_1s;
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
 {
		if(htim == (&htim6))
		{
			times_1s++;
			if(times_1s==10)
			{
				times_1s=0;
				HAL_GPIO_TogglePin(RGB2_GPIO_Port,RGB2_Pin);
				HAL_GPIO_TogglePin(RGB1_GPIO_Port,RGB1_Pin);

			}
			Read_key_value();
			Key_Map();
			USBD_HID_SendReport(&hUsbDeviceFS,key_buffer,40);
		}
 }

 void Air_shoot()
 {
			HAL_GPIO_WritePin(GPIOB,AIRTX_6_Pin,1);
			HAL_GPIO_WritePin(GPIOB,AIRTX_5_Pin,1);
			HAL_GPIO_WritePin(GPIOB,AIRTX_4_Pin,1);
			HAL_GPIO_WritePin(GPIOB,AIRTX_3_Pin,1);
			HAL_GPIO_WritePin(GPIOC,AIRTX_2_Pin,1);
			HAL_GPIO_WritePin(GPIOC,AIRTX_1_Pin,1);
 
 }
 
uint16_t adc_value[6];
void ADC_Get_Value()
{
	int i = 0;
	for(i = 0;i < 6;i++)
	{
		HAL_ADC_Start(&hadc1);//ADC1
		HAL_ADC_PollForConversion(&hadc1,10);
		adc_value[i] = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
		uint8_t text=0xAA;
	
    my_data.tail[0]=0x00;
		my_data.tail[1]=0x00;
		my_data.tail[2]=0x80;
		my_data.tail[3]=0x7F;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  MX_USB_Device_Init();
  MX_TIM6_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	MPR121_Init(I2C1,0X5A);
	MPR121_Init(I2C1,0X5B);
	MPR121_Init(I2C1,0X5C);
	MPR121_Init(I2C1,0X5D);
  HAL_TIM_Base_Start_IT(&htim6);
	Air_shoot();

  /* USER CODE END 2 */
		SPI2->CR1|=1<<6;
		SPI2->CR1|=1<<14;
		
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
			//HAL_SPI_Transmit(&hspi2, &text, 1, 100);
		if(refresh_flag == 1)
		{
			refresh_Color();
			refresh_flag=0;
		
		}
    /* USER CODE BEGIN 3 */
			ADC_Get_Value();
			
		//	CDC_Transmit_FS((uint8_t*)&my_data,sizeof(my_data));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
