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
#define BCK_LIGHT_Pin GPIO_PIN_3
#define BCK_LIGHT_GPIO_Port GPIOE
#define CFG_Pin GPIO_PIN_4
#define CFG_GPIO_Port GPIOE
#define BEEP_Pin GPIO_PIN_5
#define BEEP_GPIO_Port GPIOE
#define F_RST_Pin GPIO_PIN_6
#define F_RST_GPIO_Port GPIOE
#define F_CS_Pin GPIO_PIN_13
#define F_CS_GPIO_Port GPIOC
#define S_CS_Pin GPIO_PIN_14
#define S_CS_GPIO_Port GPIOC
#define M_CE_Pin GPIO_PIN_15
#define M_CE_GPIO_Port GPIOC
#define TP_INT_Pin GPIO_PIN_0
#define TP_INT_GPIO_Port GPIOA
#define TP_RST_Pin GPIO_PIN_11
#define TP_RST_GPIO_Port GPIOD
#define ERXER_Pin GPIO_PIN_2
#define ERXER_GPIO_Port GPIOG
#define EXCLK_Pin GPIO_PIN_3
#define EXCLK_GPIO_Port GPIOG
#define DRVEN_Pin GPIO_PIN_4
#define DRVEN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
