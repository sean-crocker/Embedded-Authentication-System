/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define LCDTP_CS_Pin GPIO_PIN_4
#define LCDTP_CS_GPIO_Port GPIOC
#define LCDTP_IRQ_Pin GPIO_PIN_5
#define LCDTP_IRQ_GPIO_Port GPIOC
#define BL_PWM_Pin GPIO_PIN_0
#define BL_PWM_GPIO_Port GPIOB
#define I2C_SIOC_Pin GPIO_PIN_10
#define I2C_SIOC_GPIO_Port GPIOB
#define I2C_SIOD_Pin GPIO_PIN_11
#define I2C_SIOD_GPIO_Port GPIOB
#define LCDTP_CLK_Pin GPIO_PIN_13
#define LCDTP_CLK_GPIO_Port GPIOB
#define LCDTP_DOUT_Pin GPIO_PIN_14
#define LCDTP_DOUT_GPIO_Port GPIOB
#define LCDTP_DIN_Pin GPIO_PIN_15
#define LCDTP_DIN_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define SDIO_CD_Pin GPIO_PIN_3
#define SDIO_CD_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
