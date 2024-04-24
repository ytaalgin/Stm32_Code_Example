#include "main.h"

RTC_HandleTypeDef hrtc;
UART_HandleTypeDef huart2;

// Define required variables
bool isRead = true;
int deger1, deger2 = 0;
int sayactop = 0;
int sayac1, sayac2, sayac3, sayac4, sayac5 = 0;
float mesafe1, mesafe2, mesafe3, mesafe4, mesafe5, eskiMesafe = 0;
float mesafetoplam, hiz, hizson = 0;
uint32_t elapsedSeconds, simdikiZaman, degertut, baslangicZamani = 0;
uint32_t sonUcHane, virgulsonrasi, mseconds;

GPIO_InitTypeDef GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	static RTC_TimeTypeDef sTime;

    // Get current time
    HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
    mseconds += (sTime.SubSeconds * 1000) / (sTime.SecondFraction + 1);

    elapsedSeconds++;

    sonUcHane = mseconds % 1000;
    baslangicZamani = elapsedSeconds * 1000 + (1000 - sonUcHane);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();

  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc); // Deactivate WakeUp Timer

  RTC_TimeTypeDef sTime;

  // Set initial time
  sTime.Hours = 18;
  sTime.Minutes = 50;
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 2048 - 1, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

	while (1) {

	  deger1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

	  if (mesafe1 < 82) {
		if (deger1 == 1 && isRead) {
		  simdikiZaman = baslangicZamani - degertut;
		  degertut = baslangicZamani;
		  sayac1++;
		  isRead = false;
		}
		else if (deger1 == 0 && mesafe1 != 82) {
		  isRead = true;
		}
		if (sayac1 >= 1) {
		  mesafe1 = 6 + ((sayac1 - 1) * 4);
		  eskiMesafe = 6 + ((sayac1 - 2) * 4);
		  hiz = (mesafe1 - eskiMesafe) / (simdikiZaman);
		}
	  }
/**************************************************************************************************************************/
	  if (mesafe1 >= 82 && mesafe2 < 5.95) {
		mesafe1 = 82;
		if (deger1 == 1 && isRead) {
		  simdikiZaman = baslangicZamani - degertut;
		  degertut = baslangicZamani;
		  sayac2++;
		  isRead = false;
		}
		else if (deger1 == 0 && mesafe2 != 5.95) {
		  isRead = true;
		}
		if (sayac2 >= 1) {
		  mesafe2 = (0.05 * (2 * sayac2 - 1) + 4) ;
		  eskiMesafe = (0.05 * (2 * sayac2 - 2) + 4);
		  hiz = ((mesafe2 - eskiMesafe) / (simdikiZaman))*100;
		}
	  }
/**************************************************************************************************************************/
	  if (mesafe2 >= 5.95 && mesafe3 < 46.05) {
		  mesafe2 = 5.95;
		  if (deger1 == 1 && isRead) {
			  simdikiZaman = baslangicZamani - degertut;
			  degertut = baslangicZamani;
			  sayac3++;
			  isRead = false;
		  }
		  else if (deger1 == 0 && mesafe3 != 46.05) {
			  isRead = true;
		  }
		  if (sayac3 >= 1) {
			  mesafe3 =(2.05 + (sayac3 - 1) * 4) ;
			  eskiMesafe =(2.05 + (sayac3 - 2) * 4) ;
			  hiz = (mesafe3 - eskiMesafe) / (simdikiZaman);
		  }
		}
/*************************************************************************************************************************/
		if (mesafe3 >= 46.05 && mesafe4 < 4.95) {
		  mesafe3 = 46.05;
		  if (deger1 == 1 && isRead) {
			  simdikiZaman = baslangicZamani - degertut;
			  degertut = baslangicZamani;
			  sayac4++;
			  isRead = false;
		  }
		  else if (deger1 == 0 && mesafe4 != 4.95) {
			  isRead = true;
		  }
		  if (sayac4 >= 1) {
			  mesafe4 = (0.05 * (2 * sayac4 - 1)) + 4 ;
			  eskiMesafe = (0.05 * (2 * sayac4 - 2)) + 4 ;
			  hiz = ((mesafe4 - eskiMesafe) / (simdikiZaman))*100;
		  }
		}
/**************************************************************************************************************************/
		if (mesafe4 >= 4.95 && mesafe5 < 47.05) {
		  mesafe4 = 4.95;
		  if (deger1 == 1 && isRead) {
			  simdikiZaman = baslangicZamani - degertut;
			  degertut = baslangicZamani;
			  sayac5++;
			  isRead = false;
		  }
		  else if (deger1 == 0 && mesafe5 != 47.05) {
			  isRead = true;
		  }
		  if (sayac5 >= 1) {
			  mesafe5 =((sayac5 - 1) * 4) + 3.05;
			  eskiMesafe =((sayac5 - 2) * 4) + 3.05;
			  hiz = (mesafe5 - eskiMesafe) / (simdikiZaman);
		  }
		}

		if (mesafe5 >= 47.05) {
		  mesafe5 = 47.05;
		  isRead = false;
		}
/**************************************************************************************************************************/
		mesafetoplam = mesafe1 + mesafe2 + mesafe3 + mesafe4 + mesafe5;
		sayactop = sayac1 + sayac2 + sayac3 + sayac4 + sayac5;
		hizson = hiz * 1000;

		char buffer[100];
		sprintf(buffer, "%.2f\t %.2f\t %lu\n\r", mesafetoplam, hizson, baslangicZamani);
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

		HAL_Delay(10); // Adjust delay as needed
		baslangicZamani += 10;
	  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
        char error_message[] = "hata\n";
        HAL_UART_Transmit(&huart2, (uint8_t *)error_message, strlen(error_message), HAL_MAX_DELAY);
        HAL_Delay(1000); // Adjust delay as needed
      }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
