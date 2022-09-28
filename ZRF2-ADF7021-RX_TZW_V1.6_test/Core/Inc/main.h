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
#define P14_Pin GPIO_PIN_0
#define P14_GPIO_Port GPIOC
#define P12_Pin GPIO_PIN_1
#define P12_GPIO_Port GPIOC
#define A_CTRL_Pin GPIO_PIN_2
#define A_CTRL_GPIO_Port GPIOC
#define A_CHK_Pin GPIO_PIN_3
#define A_CHK_GPIO_Port GPIOC
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
#define LEDR_Pin GPIO_PIN_11
#define LEDR_GPIO_Port GPIOA
#define LEDG_Pin GPIO_PIN_12
#define LEDG_GPIO_Port GPIOA
#define OUTS_CHK_Pin GPIO_PIN_15
#define OUTS_CHK_GPIO_Port GPIOA
#define P7_P_Pin GPIO_PIN_10
#define P7_P_GPIO_Port GPIOC
#define P18_Pin GPIO_PIN_11
#define P18_GPIO_Port GPIOC
#define M_CTRL_IN_Pin GPIO_PIN_12
#define M_CTRL_IN_GPIO_Port GPIOC
#define M_CTRL_OUT_Pin GPIO_PIN_5
#define M_CTRL_OUT_GPIO_Port GPIOB
#define MAIN_PK1_Pin GPIO_PIN_6
#define MAIN_PK1_GPIO_Port GPIOB
#define MAIN_PK2_Pin GPIO_PIN_7
#define MAIN_PK2_GPIO_Port GPIOB
#define SS_Pin GPIO_PIN_8
#define SS_GPIO_Port GPIOB
#define P20_Pin GPIO_PIN_9
#define P20_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
