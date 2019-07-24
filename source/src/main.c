/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "comm_buffer.h"
#include "debug_trace.h"
#include "stm32f7_helper_func.h"
#include "timer_sched.h"
// #include "mnist_schema_generated.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CODE_VERSION 100
#define UART_BUFFER_SIZE 256
#define FB_UART_BUFFER_SIZE 4096

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Uncomment to overclock to 295 MHz */
// #define OVERCLOCK

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

UART_HandleTypeDef huart7;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
DECLARE_COMM_BUFFER(dbg_uart, UART_BUFFER_SIZE, UART_BUFFER_SIZE);
DECLARE_COMM_BUFFER(fb_uart, UART_BUFFER_SIZE, FB_UART_BUFFER_SIZE);

__IO uint32_t glb_tmr_1ms = 0;
__IO uint32_t glb_perf_tmr, glb_tmr_1sec = 0;
__IO uint8_t tmp_rx, tmp_rx2 = 0;
__IO uint32_t rx_timeout, rx_timeout_uart7 = 0;
uint32_t trace_levels;

/* Create the list head for the timer */
static LIST_HEAD(obj_timer_list);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
void MX_USART6_UART_Init(void);
static void MX_UART7_Init(void);
/* USER CODE BEGIN PFP */

void dbg_uart_parser(uint8_t *buffer, size_t bufferlen, uint8_t sender);
void fb_uart_parser(uint8_t *buffer, size_t bufferlen, uint8_t sender);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void main_loop()
{
    if (glb_tmr_1ms) {
        glb_tmr_1ms = 0;

        mod_timer_polling(&obj_timer_list);
        /* Debug port */
        if (dbg_uart.rx_ready_tmr)
            dbg_uart.rx_ready_tmr--;
        if (dbg_uart.rx_ready_tmr == 1) {
            dbg_uart.rx_ready_tmr = 0;
            dbg_uart.rx_buffer[dbg_uart.rx_ptr_in] = 0; // terminate string
            TRACE(("Received: %s\n", dbg_uart.rx_buffer));
            dbg_uart_parser(dbg_uart.rx_buffer, dbg_uart.rx_ptr_in, 0);
            dbg_uart.rx_ptr_in = 0;
        }
        /* Flatbuffer UART port */
        if (fb_uart.rx_ready_tmr)
            fb_uart.rx_ready_tmr--;
        if (fb_uart.rx_ready_tmr == 1) {
            fb_uart.rx_ready_tmr = 0;
            // fb_uart.rx_buffer[fb_uart.rx_ptr_in] = 0; // terminate string
            // TRACE(("FB received: %s\n", fb_uart.rx_buffer));
            fb_uart_parser(fb_uart.rx_buffer, fb_uart.rx_ptr_in, 0);
            fb_uart.rx_ptr_in = 0;
        }
        glb_tmr_1sec++;
    }

    if (glb_tmr_1sec >= 1000) {
        glb_tmr_1sec = 0;
        // TRACE(("1 sec\n"));
    }
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    trace_levels_set(0 | TRACE_LEVEL_DEFAULT, 1);
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_CRC_Init();
    MX_X_CUBE_AI_Init();
    MX_USART6_UART_Init();
    MX_UART7_Init();
    /* USER CODE BEGIN 2 */

    /* Receive interrupt for UART6 */
    HAL_UART_Receive_IT(&huart6, (uint8_t *)&dbg_uart.rx_tmp, 1);
    /* Receive interrupt for UART7 */
    HAL_UART_Receive_IT(&huart7, (uint8_t *)&fb_uart.rx_tmp, 1);

    TRACE(("Program started @ %lu...\n", SystemCoreClock));
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */
        main_loop();
        // MX_X_CUBE_AI_Process();
        /* USER CODE BEGIN 3 */
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
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Activate the Over-Drive mode
     */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART6 | RCC_PERIPHCLK_UART7;
    PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
    PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void)
{

    /* USER CODE BEGIN CRC_Init 0 */

    /* USER CODE END CRC_Init 0 */

    /* USER CODE BEGIN CRC_Init 1 */

    /* USER CODE END CRC_Init 1 */
    hcrc.Instance = CRC;
    hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
    hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
    hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
    hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
    hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
    if (HAL_CRC_Init(&hcrc) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN CRC_Init 2 */

    /* USER CODE END CRC_Init 2 */
}

/**
 * @brief UART7 Initialization Function
 * @param None
 * @retval None
 */
static void MX_UART7_Init(void)
{

    /* USER CODE BEGIN UART7_Init 0 */

    /* USER CODE END UART7_Init 0 */

    /* USER CODE BEGIN UART7_Init 1 */

    /* USER CODE END UART7_Init 1 */
    huart7.Instance = UART7;
    huart7.Init.BaudRate = 115200;
    huart7.Init.WordLength = UART_WORDLENGTH_8B;
    huart7.Init.StopBits = UART_STOPBITS_1;
    huart7.Init.Parity = UART_PARITY_NONE;
    huart7.Init.Mode = UART_MODE_TX_RX;
    huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart7.Init.OverSampling = UART_OVERSAMPLING_16;
    huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart7) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN UART7_Init 2 */

    /* USER CODE END UART7_Init 2 */
}

/**
 * @brief USART6 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART6_UART_Init(void)
{

    /* USER CODE BEGIN USART6_Init 0 */

    /* USER CODE END USART6_Init 0 */

    /* USER CODE BEGIN USART6_Init 1 */

    /* USER CODE END USART6_Init 1 */
    huart6.Instance = USART6;
    huart6.Init.BaudRate = 115200;
    huart6.Init.WordLength = UART_WORDLENGTH_8B;
    huart6.Init.StopBits = UART_STOPBITS_1;
    huart6.Init.Parity = UART_PARITY_NONE;
    huart6.Init.Mode = UART_MODE_TX_RX;
    huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling = UART_OVERSAMPLING_16;
    huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart6) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART6_Init 2 */

    /* USER CODE END USART6_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /*Configure GPIO pin : PF6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

void dbg_uart_parser(uint8_t *buffer, size_t bufferlen, uint8_t sender)
{
    buffer[bufferlen] = 0;
    if (!strncmp((char *)buffer, "CMD=", 4)) {
        /* Get mode */
        uint8_t mode = atoi((const char *)&buffer[4]);
        switch (mode) {
        case 1:
            // ViewModel(&tf);
            break;
        case 2:
            // RunInference(&tf, (float *)digit, 784, 1);
            break;
        }
        TRACE(("Testing mode: %d\n\n", mode));
    }
}

void fb_uart_parser(uint8_t *buffer, size_t bufferlen, uint8_t sender)
{
    // TRACE(("fb_uart_parser: %d\n", bufferlen));
    // auto req = MnistProt::GetCommands(buffer);

    // flatbuffers::Verifier verifier(reinterpret_cast<unsigned char*>(buffer),bufferlen);
    // bool isCommand = req->Verify(verifier);
    // if (!isCommand) {
    //     TRACE(("[FB] Invalid flatbuffer data received\n"));
    //     return;
    // }
    
    // TRACE(("[FB] Processing flatbuffer...\n"));
    // if (req->cmd() == MnistProt::Command_CMD_GET_STATS) {
    //     TRACE(("[FB] Sending stats\n"));
    //     CmdSendStats();
    // }
    // else if (req->cmd() == MnistProt::Command_CMD_INFERENCE_INPUT) {
    //     TRACE(("[FB] Running inference on image\n"));
    //     auto digit = req->input();
    //     TRACE(("digit size: %lu\n", digit->digit()->size()));
    //     float *p = (float*) digit->digit()->data();
        
    //     RunInference(&tf, p, digit->digit()->size(), 1);
    // }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if (UartHandle == &huart6) {
        /* Receive byte from uart */
        dbg_uart.rx_ready_tmr = 10;
        dbg_uart.rx_buffer[dbg_uart.rx_ptr_in] = dbg_uart.rx_tmp;
        dbg_uart.rx_ptr_in++;
        HAL_UART_Receive_IT(&huart6, (uint8_t *)&dbg_uart.rx_tmp, 1);
    }
    else if (UartHandle == &huart7) {
        /* Receive byte from uart */
        fb_uart.rx_ready_tmr = 10;
        fb_uart.rx_buffer[fb_uart.rx_ptr_in] = fb_uart.rx_tmp;
        fb_uart.rx_ptr_in++;
        HAL_UART_Receive_IT(&huart7, (uint8_t *)&fb_uart.rx_tmp, 1);
    }
}

#ifdef __cplusplus
extern "C" {
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, 10);
    return ch;
}
#ifdef __cplusplus
}
#endif

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
