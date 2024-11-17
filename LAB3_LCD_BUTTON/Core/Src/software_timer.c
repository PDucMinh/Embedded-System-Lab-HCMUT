/*
 * software_timer.c
 *
 *  Created on: Sep 18, 2024
 *      Author: Admin
 */

#include"global.h"

#define TIMER_CYCLE 1

uint16_t timer_counter = 0;
uint8_t timer_flag = 0;

uint16_t timer_counter1 = 0;
uint8_t timer_flag1 = 0;

void timer_init()
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void set_timer(uint16_t duration)
{
	timer_counter = duration / TIMER_CYCLE;
	timer_flag = 0;
}

void set_timer1(uint16_t duration)
{
	timer_counter1 = duration / TIMER_CYCLE;
	timer_flag1 = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if (htim->Instance == TIM2)
	{
		button_Scan();
		if (timer_counter > 0)
		{
			timer_counter--;
			if (timer_counter == 0)
			{
				led7_Scan();
				timer_flag = 1;
			}
		}

		if (timer_counter1 > 0)
		{
			timer_counter1--;
			if (timer_counter1 == 0)
			{
				led7_Scan();
				timer_flag1 = 1;
			}
		}
	}


}

uint8_t is_flag()
{
	if (timer_flag == 1)
	{
		timer_flag = 0;
		return 1;
	}
	return 0;
}

uint8_t is_flag1()
{
	if (timer_flag1 == 1)
	{
		timer_flag1 = 0;
		return 1;
	}
	return 0;
}
