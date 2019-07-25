/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : stm32f7xx_hal_msp.c
 * Description        : This file provides code for the MSP Initialization
 *                      and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
    /* USER CODE BEGIN MspInit 0 */

    /* USER CODE END MspInit 0 */

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    /* System interrupt init*/

    /* USER CODE BEGIN MspInit 1 */

    /* USER CODE END MspInit 1 */
}

/**
 * @brief CRC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
    if (hcrc->Instance == CRC) {
        /* USER CODE BEGIN CRC_MspInit 0 */

        /* USER CODE END CRC_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_CRC_CLK_ENABLE();
        /* USER CODE BEGIN CRC_MspInit 1 */

        /* USER CODE END CRC_MspInit 1 */
    }
}

/**
 * @brief CRC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
    if (hcrc->Instance == CRC) {
        /* USER CODE BEGIN CRC_MspDeInit 0 */

        /* USER CODE END CRC_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_CRC_CLK_DISABLE();
        /* USER CODE BEGIN CRC_MspDeInit 1 */

        /* USER CODE END CRC_MspDeInit 1 */
    }
}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (huart->Instance == UART7) {
        /* USER CODE BEGIN UART7_MspInit 0 */

        /* USER CODE END UART7_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_UART7_CLK_ENABLE();

        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**UART7 GPIO Configuration
        PF7     ------> UART7_TX
        PF6     ------> UART7_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        /* UART7 interrupt Init */
        HAL_NVIC_SetPriority(UART7_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART7_IRQn);
        /* USER CODE BEGIN UART7_MspInit 1 */

        /* USER CODE END UART7_MspInit 1 */
    } else if (huart->Instance == USART6) {
        /* USER CODE BEGIN USART6_MspInit 0 */

        /* USER CODE END USART6_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_USART6_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**USART6 GPIO Configuration
        PC7     ------> USART6_RX
        PC6     ------> USART6_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /* USART6 interrupt Init */
        HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART6_IRQn);
        /* USER CODE BEGIN USART6_MspInit 1 */

        /* USER CODE END USART6_MspInit 1 */
    }
}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART7) {
        /* USER CODE BEGIN UART7_MspDeInit 0 */

        /* USER CODE END UART7_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_UART7_CLK_DISABLE();

        /**UART7 GPIO Configuration
        PF7     ------> UART7_TX
        PE7     ------> UART7_RX
        */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7);

        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7);

        /* UART7 interrupt DeInit */
        HAL_NVIC_DisableIRQ(UART7_IRQn);
        /* USER CODE BEGIN UART7_MspDeInit 1 */

        /* USER CODE END UART7_MspDeInit 1 */
    } else if (huart->Instance == USART6) {
        /* USER CODE BEGIN USART6_MspDeInit 0 */

        /* USER CODE END USART6_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART6_CLK_DISABLE();

        /**USART6 GPIO Configuration
        PC7     ------> USART6_RX
        PC6     ------> USART6_TX
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_7 | GPIO_PIN_6);

        /* USART6 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART6_IRQn);
        /* USER CODE BEGIN USART6_MspDeInit 1 */

        /* USER CODE END USART6_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
