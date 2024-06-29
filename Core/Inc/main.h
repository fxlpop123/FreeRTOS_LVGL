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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define IPS_BK_Pin GPIO_PIN_13
#define IPS_BK_GPIO_Port GPIOC
#define CST816T_RST_Pin GPIO_PIN_4
#define CST816T_RST_GPIO_Port GPIOA
#define IPS_RST_Pin GPIO_PIN_5
#define IPS_RST_GPIO_Port GPIOA
#define IPS_CS_Pin GPIO_PIN_14
#define IPS_CS_GPIO_Port GPIOB
#define IPS_MOSI_Pin GPIO_PIN_15
#define IPS_MOSI_GPIO_Port GPIOB
#define CST816T_INT_Pin GPIO_PIN_10
#define CST816T_INT_GPIO_Port GPIOD
#define IPS_DC_Pin GPIO_PIN_15
#define IPS_DC_GPIO_Port GPIOD
#define IPS_SCK_Pin GPIO_PIN_3
#define IPS_SCK_GPIO_Port GPIOD
#define IIC1_SCL_Pin GPIO_PIN_6
#define IIC1_SCL_GPIO_Port GPIOB
#define IIC1_SDA_Pin GPIO_PIN_7
#define IIC1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
