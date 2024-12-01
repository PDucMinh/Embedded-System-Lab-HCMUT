/*
 * exercise.c
 *
 *  Created on: Sep 18, 2024
 *      Author: Admin
 */

#include "exercise.h"

int count = 0;
int first_time_e3_p1 = 0;

void e1_p1(led_t *led)
{
	led_set_mode(led, ON);
	HAL_Delay(2000);
	led_set_mode(led, OFF);
	HAL_Delay(4000);
}
void e2_p1(led_t *led)
{
	if (led->led_mode == ON && count == 2)
	{
		count = 0;
		led_set_mode(led, OFF);
	}
	else if (led->led_mode == OFF && count == 4)
	{
		count = 0;
		led_set_mode(led, ON);
	}
	else
	{
		count++;
	}
	HAL_Delay(1000);
}
void e3_p1(led_t *led1, led_t *led2, led_t *led3)
{
	count++;
	if (first_time_e3_p1 == 0)
	{
		first_time_e3_p1++;
		led_set_mode(led1, ON);
	}
	else if (led1->led_mode == ON && count == 5)
	{
		count = 0;
		led_set_mode(led1, OFF);
		led_set_mode(led2, ON);
	}
	else if (led2->led_mode == ON && count == 3)
	{
		count = 0;
		led_set_mode(led2, OFF);
		led_set_mode(led3, ON);
	}
	else if (led3->led_mode == ON && count == 3)
	{
		count = 0;
		led_set_mode(led3, OFF);
		led_set_mode(led1, ON);
	}
	HAL_Delay(1000);
}

void e1_p2(led_t *led1, led_t *led2, led_t *led3)
{
	if (first_time_e3_p1 == 0)
	{
		first_time_e3_p1++;
		led_set_mode(led1, ON);
		set_timer(5000);
	}
	else if (led1->led_mode == ON && is_flag())
	{
		set_timer(3000);
		led_set_mode(led1, OFF);
		led_set_mode(led2, ON);
	}
	else if (led2->led_mode == ON && is_flag())
	{
		set_timer(1000);
		led_set_mode(led2, OFF);
		led_set_mode(led3, ON);
	}
	else if (led3->led_mode == ON && is_flag())
	{
		set_timer(5000);
		led_set_mode(led3, OFF);
		led_set_mode(led1, ON);
	}
}
void e2_p2();
void e3_p2();
void e4_p2();
void e5_p2();

