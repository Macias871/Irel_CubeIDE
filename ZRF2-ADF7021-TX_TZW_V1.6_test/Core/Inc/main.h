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
#define POFF_Pin GPIO_PIN_14
#define POFF_GPIO_Port GPIOC
#define P14_Pin GPIO_PIN_0
#define P14_GPIO_Port GPIOC
#define P12_Pin GPIO_PIN_1
#define P12_GPIO_Port GPIOC
#define P11_Pin GPIO_PIN_2
#define P11_GPIO_Port GPIOC
#define P9_Pin GPIO_PIN_3
#define P9_GPIO_Port GPIOC
#define P10_Pin GPIO_PIN_0
#define P10_GPIO_Port GPIOA
#define P8_Pin GPIO_PIN_1
#define P8_GPIO_Port GPIOA
#define P2_Pin GPIO_PIN_2
#define P2_GPIO_Port GPIOA
#define P6_Pin GPIO_PIN_3
#define P6_GPIO_Port GPIOA
#define P4_Pin GPIO_PIN_4
#define P4_GPIO_Port GPIOA
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOA
#define SREAD_Pin GPIO_PIN_6
#define SREAD_GPIO_Port GPIOA
#define SDATA_Pin GPIO_PIN_7
#define SDATA_GPIO_Port GPIOA
#define VBAT_Pin GPIO_PIN_4
#define VBAT_GPIO_Port GPIOC
#define P16_Pin GPIO_PIN_5
#define P16_GPIO_Port GPIOC
#define SWD_Pin GPIO_PIN_0
#define SWD_GPIO_Port GPIOB
#define SWD_EXTI_IRQn EXTI0_IRQn
#define MUXOUT_Pin GPIO_PIN_1
#define MUXOUT_GPIO_Port GPIOB
#define MUXOUT_EXTI_IRQn EXTI1_IRQn
#define RXTX_Pin GPIO_PIN_12
#define RXTX_GPIO_Port GPIOB
#define CE_Pin GPIO_PIN_6
#define CE_GPIO_Port GPIOC
#define SLE_Pin GPIO_PIN_7
#define SLE_GPIO_Port GPIOC
#define P23_Pin GPIO_PIN_11
#define P23_GPIO_Port GPIOA
#define P21_Pin GPIO_PIN_12
#define P21_GPIO_Port GPIOA
#define P24_Pin GPIO_PIN_15
#define P24_GPIO_Port GPIOA
#define P7_Pin GPIO_PIN_10
#define P7_GPIO_Port GPIOC
#define BEEP_Pin GPIO_PIN_11
#define BEEP_GPIO_Port GPIOC
#define LEDR_Pin GPIO_PIN_12
#define LEDR_GPIO_Port GPIOC
#define P17_Pin GPIO_PIN_5
#define P17_GPIO_Port GPIOB
#define PON_Pin GPIO_PIN_6
#define PON_GPIO_Port GPIOB
#define P15_Pin GPIO_PIN_7
#define P15_GPIO_Port GPIOB
#define P22_Pin GPIO_PIN_8
#define P22_GPIO_Port GPIOB
#define LEDG_Pin GPIO_PIN_9
#define LEDG_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define SS1_Pin GPIO_PIN_11
#define SS1_GPIO_Port GPIOA
#define SS2_Pin GPIO_PIN_8
#define SS2_GPIO_Port GPIOB
#define SS3_Pin GPIO_PIN_15
#define SS3_GPIO_Port GPIOA
#define SS4_Pin GPIO_PIN_12
#define SS4_GPIO_Port GPIOA
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
