/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "sensor.h"
#include "buzzer.h"
#include "touch.h"
#include "uart.h"
#include "light_control.h"
#include "stdio.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void test_Buzzer();

void test_Adc(float sensor_power, char* light, float temperature, int humidity);

void updateTime();
void lcd_plot(float val);

void lab6_operation();
void lab6_alarm();
int buzzer_flag = 0;
int plot_buffer[10];
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_FSMC_Init();
  MX_I2C1_Init();
  MX_TIM13_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 lcd_Clear(BLACK);
 while (1)
  {
	  // 50ms task
	  // if(flag_timer2 == 1){
		//   flag_timer2 = 0;
		//   button_Scan();
		  // test_Esp();
		//   lightProcess();
		//   test_LedDebug();
	  // }
//    lcd_DrawCircle(237, 310, YELLOW, 2, 1);
	  while(!flag_timer2);
	  flag_timer2 = 0;
	  button_Scan();
	  test_LedDebug();
    lab6_operation();
//	  test_Adc();
	  test_Buzzer();
    lab6_alarm();
    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init(){
	  timer_init();
	  button_init();
	  lcd_init();
	  uart_init_esp();
	  setTimer2(50);

    ds3231_init();
    sensor_init();
	  buzzer_init();
    uart_init_rs232();
    setTimer1(10);
}

uint8_t count_led_debug = 0;

void test_LedDebug(){
	count_led_debug = (count_led_debug + 1)%20;
	if(count_led_debug == 0){
		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	}
}

uint8_t isButtonUp()
{
    if (button_count[3] == 1)
        return 1;
    else
        return 0;
}

uint8_t isButtonDown()
{
    if (button_count[7] == 1)
        return 1;
    else
        return 0;
}

uint8_t isButtonRight()
{
    if (button_count[11] == 1)
        return 1;
    else
        return 0;
}

void updateTime(){
	ds3231_Write(ADRESS_YEAR, 24);
	ds3231_Write(ADRESS_MONTH, 11);
	ds3231_Write(ADRESS_DATE, 13);
	ds3231_Write(ADRESS_DAY, 6);
	ds3231_Write(ADRESS_HOUR, 13);
	ds3231_Write(ADRESS_MIN, 16);
	ds3231_Write(ADRESS_SEC, 24);
}

uint8_t count_adc = 0;

void test_Adc(float sensor_power, char* light, float temperature, int humidity){
	// count_adc = (count_adc + 1)%20;
	// if(count_adc == 0){
	// 	sensor_Read();
		lcd_ShowStr(10, 10, "Power:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(130, 10,sensor_power, 4, RED, BLACK, 16);
		lcd_ShowStr(10, 30, "Light:", RED, BLACK, 16, 0);
		lcd_ShowStr(130, 30,light, RED, BLACK, 16, 0);
//		lcd_ShowIntNum(130, 120,(int)((sensor_GetLight()/4095)*100), 4, RED, BLACK, 16);
		lcd_ShowStr(10, 50, "Temperature:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(130, 50, temperature, 4, RED, BLACK, 16);
		lcd_ShowStr(10, 70, "Humidity:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(130, 70, humidity, 4, RED, BLACK, 16);
		// lcd_ShowStr(10, 180, "Temperature:", RED, BLACK, 16, 0);
		// lcd_ShowFloatNum(130, 180,sensor_GetTemperature(), 4, RED, BLACK, 16);
	// }
}

void test_Buzzer(){
	if(isButtonUp()){
		buzzer_SetVolume(50);
	}

	if(isButtonDown()){
		buzzer_SetVolume(0);
	}

	if(isButtonRight()){
		buzzer_SetVolume(25);
	}

}
int humidity;
int power_prev = 0;
int x=0;
void lab6_operation()
{
  count_adc = (count_adc + 1)%20;
  if(count_adc == 0)
  {  
  sensor_Read();
  float sensor_power = sensor_GetCurrent() * sensor_GetVoltage();
  char light[10] ;
  sprintf(light,"%s",(((sensor_GetLight() *100 / 4095) < 50) ? "Strong" : "Weak  "));
  // sprintf(light,"%s", "strong");
  float temperature = sensor_GetTemperature();
  humidity = sensor_GetPotentiometer() * 100 /4095;
  if (humidity > 70) {buzzer_flag = 1; flag_timer1 = 1;}
  else {buzzer_flag = 0;}
  test_Adc(sensor_power, light, temperature, humidity);
  lcd_plot(sensor_power);
  }
} 
void lab6_alarm()
{
  if (buzzer_flag == 1 && flag_timer1 == 1)
  {
    buzzer_SetVolume(50);
    uart_Rs232SendString("ALARM: Humidity is too high\n");
    flag_timer1 = 0;
    setTimer1(1000);
  }
  else
  {
    buzzer_SetVolume(0);
  }
}
int count = 0;
void lcd_plot(float val) {
  if (count == 10)
  {
    lcd_Fill(0,100,238,320,BLACK);
    count = 0;
  }
  float y = 320 - (val * 200) / 150;
  if (y < 120) y = 120;
  float x = count * 20;
  if (x < 2) x = 2;
  lcd_DrawCircle(x, y, YELLOW, 2, 1);
  count++;
}
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
  while (1)
  {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
