/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
struct send_data{
	float DATA[4];
	uint8_t tail[4];
};
extern struct send_data my_data;
extern uint16_t adc_value[6];
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED3_Pin GPIO_PIN_1
#define LED3_GPIO_Port GPIOF
#define RX1_Pin GPIO_PIN_0
#define RX1_GPIO_Port GPIOA
#define RX2_Pin GPIO_PIN_1
#define RX2_GPIO_Port GPIOA
#define RX3_Pin GPIO_PIN_2
#define RX3_GPIO_Port GPIOA
#define RX4_Pin GPIO_PIN_3
#define RX4_GPIO_Port GPIOA
#define RGB3_Pin GPIO_PIN_7
#define RGB3_GPIO_Port GPIOA
#define RGB1_Pin GPIO_PIN_4
#define RGB1_GPIO_Port GPIOC
#define RGB2_Pin GPIO_PIN_0
#define RGB2_GPIO_Port GPIOB
#define RX6_Pin GPIO_PIN_12
#define RX6_GPIO_Port GPIOB
#define RX5_Pin GPIO_PIN_14
#define RX5_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOA
#define MPR_SCL_Pin GPIO_PIN_15
#define MPR_SCL_GPIO_Port GPIOA
#define AIRTX_1_Pin GPIO_PIN_10
#define AIRTX_1_GPIO_Port GPIOC
#define AIRTX_2_Pin GPIO_PIN_11
#define AIRTX_2_GPIO_Port GPIOC
#define AIRTX_3_Pin GPIO_PIN_3
#define AIRTX_3_GPIO_Port GPIOB
#define AIRTX_4_Pin GPIO_PIN_4
#define AIRTX_4_GPIO_Port GPIOB
#define AIRTX_5_Pin GPIO_PIN_5
#define AIRTX_5_GPIO_Port GPIOB
#define AIRTX_6_Pin GPIO_PIN_6
#define AIRTX_6_GPIO_Port GPIOB
#define MPR_SDA_Pin GPIO_PIN_7
#define MPR_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
