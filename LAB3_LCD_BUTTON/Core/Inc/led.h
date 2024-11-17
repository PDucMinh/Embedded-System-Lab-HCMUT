/*
 * led.h
 *
 *  Created on: Sep 18, 2024
 *      Author: Admin
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"

#define ACTIVE_HIGH (1)
#define ACTIVE_LOW (0)
#define ON (1)
#define OFF (0)

typedef struct
{
	uint8_t led_type; // active HIGH or active LOW
	uint8_t led_mode; // ON or OFF
	GPIO_TypeDef* led_port;
	uint8_t led_pin;
} led_t;

void led_config(led_t *led,
				uint8_t led_type,
				GPIO_TypeDef* led_port,
				uint16_t led_pin);
void led_set_mode(led_t *led, uint8_t mode);

#endif /* INC_LED_H_ */
