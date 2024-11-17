/*
 * led.c
 *
 *  Created on: Sep 18, 2024
 *      Author: Admin
 */
#include "led.h"

void led_config(led_t *led,
				uint8_t led_type,
				GPIO_TypeDef* led_port,
				uint16_t led_pin)
{
	led->led_mode = OFF;
	led->led_port = led_port;
	led->led_pin = led_pin;
	led->led_type = led_type;
}

void led_set_mode(led_t *led, uint8_t mode)
{
	led->led_mode = mode;
	if (led->led_type == ACTIVE_HIGH)
	{
		if (led->led_mode == ON)
		{
			HAL_GPIO_WritePin(led->led_port, led->led_pin, SET);
		}
		else if (led->led_mode == OFF)
		{
			HAL_GPIO_WritePin(led->led_port, led->led_pin, RESET);
		}
	}
	else if (led->led_type == ACTIVE_LOW)
	{
		if (led->led_mode == ON)
		{
			HAL_GPIO_WritePin(led->led_port, led->led_pin, RESET);
		}
		else if (led->led_mode == OFF)
		{
			HAL_GPIO_WritePin(led->led_port, led->led_pin, SET);
		}
	}
}
void led_clear()
{

}
