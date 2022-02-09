/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l1xx_hal.h"

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
#define MUL_4_Pin GPIO_PIN_13
#define MUL_4_GPIO_Port GPIOC
#define DIVIDER_4_Pin GPIO_PIN_14
#define DIVIDER_4_GPIO_Port GPIOC
#define SET_OUT_4_Pin GPIO_PIN_15
#define SET_OUT_4_GPIO_Port GPIOC
#define MUL_6_Pin GPIO_PIN_0
#define MUL_6_GPIO_Port GPIOH
#define DIVIDER_6_Pin GPIO_PIN_1
#define DIVIDER_6_GPIO_Port GPIOH
#define SET_OUT_6_Pin GPIO_PIN_0
#define SET_OUT_6_GPIO_Port GPIOC
#define MUL_8_Pin GPIO_PIN_1
#define MUL_8_GPIO_Port GPIOC
#define DIVIDER_8_Pin GPIO_PIN_2
#define DIVIDER_8_GPIO_Port GPIOC
#define SET_OUT_8_Pin GPIO_PIN_3
#define SET_OUT_8_GPIO_Port GPIOC
#define CH1_Pin GPIO_PIN_4
#define CH1_GPIO_Port GPIOC
#define CH2_Pin GPIO_PIN_5
#define CH2_GPIO_Port GPIOC
#define CH3_Pin GPIO_PIN_0
#define CH3_GPIO_Port GPIOB
#define CH4_Pin GPIO_PIN_1
#define CH4_GPIO_Port GPIOB
#define WORK_Pin GPIO_PIN_10
#define WORK_GPIO_Port GPIOB
#define SET_OUT_7_Pin GPIO_PIN_11
#define SET_OUT_7_GPIO_Port GPIOB
#define DIVIDER_7_Pin GPIO_PIN_12
#define DIVIDER_7_GPIO_Port GPIOB
#define MUL_7_Pin GPIO_PIN_13
#define MUL_7_GPIO_Port GPIOB
#define SET_OUT_5_Pin GPIO_PIN_14
#define SET_OUT_5_GPIO_Port GPIOB
#define DIVIDER_5_Pin GPIO_PIN_15
#define DIVIDER_5_GPIO_Port GPIOB
#define MUL_5_Pin GPIO_PIN_6
#define MUL_5_GPIO_Port GPIOC
#define SET_OUT_3_Pin GPIO_PIN_7
#define SET_OUT_3_GPIO_Port GPIOC
#define DIVIDER_3_Pin GPIO_PIN_8
#define DIVIDER_3_GPIO_Port GPIOC
#define MUL_3_Pin GPIO_PIN_9
#define MUL_3_GPIO_Port GPIOC
#define UDEN_Pin GPIO_PIN_11
#define UDEN_GPIO_Port GPIOA
#define SET_OUT_1_Pin GPIO_PIN_10
#define SET_OUT_1_GPIO_Port GPIOC
#define DIVIDER_1_Pin GPIO_PIN_11
#define DIVIDER_1_GPIO_Port GPIOC
#define MUL_1_Pin GPIO_PIN_12
#define MUL_1_GPIO_Port GPIOC
#define MUL_2_Pin GPIO_PIN_3
#define MUL_2_GPIO_Port GPIOB
#define DIVIDER_2_Pin GPIO_PIN_4
#define DIVIDER_2_GPIO_Port GPIOB
#define SET_OUT_2_Pin GPIO_PIN_5
#define SET_OUT_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
