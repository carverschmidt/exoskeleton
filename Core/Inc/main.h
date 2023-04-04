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
#include "motorTimer.h"
#include "motor_encoder.h"
#include <stdio.h>

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define M1PWM_Pin GPIO_PIN_7
#define M1PWM_GPIO_Port GPIOA
#define M4PWM_Pin GPIO_PIN_10
#define M4PWM_GPIO_Port GPIOB
#define M3PWM_Pin GPIO_PIN_7
#define M3PWM_GPIO_Port GPIOC
#define M2DIR_Pin GPIO_PIN_8
#define M2DIR_GPIO_Port GPIOA
#define M1DIR_Pin GPIO_PIN_9
#define M1DIR_GPIO_Port GPIOA
#define M4DIR_Pin GPIO_PIN_10
#define M4DIR_GPIO_Port GPIOA
#define M6PWM_Pin GPIO_PIN_3
#define M6PWM_GPIO_Port GPIOB
#define M5PWM_Pin GPIO_PIN_4
#define M5PWM_GPIO_Port GPIOB
#define M3DIR_Pin GPIO_PIN_5
#define M3DIR_GPIO_Port GPIOB
#define M2PWM_Pin GPIO_PIN_6
#define M2PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
