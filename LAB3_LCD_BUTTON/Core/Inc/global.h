/*
 * global.h
 *
 *  Created on: Sep 28, 2023
 *      Author: KAI
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT 1
#define INIT_SETTING 2

#define AUTO_RED_GREEN 3
#define AUTO_RED_YELLOW 4
#define AUTO_GREEN_RED 5
#define AUTO_YELLOW_RED 6

#define SETTING_RED 10
#define SETTING_YELLOW 11
#define SETTING_GREEN 12

#define SETTING_ON 15
#define SETTING_OFF 16

#include"software_timer.h"
#include"fsm_automatic.h"
#include"fsm_setting.h"
#include"button.h"
#include"led_7seg.h"
#include"led.h"
#include"picture.h"
#include"lcd.h"

//#include"controller.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

extern TIM_HandleTypeDef htim2;
extern SPI_HandleTypeDef hspi1;

extern int lcd_status;
extern int setting_status;

extern int traffic_counter;
extern int temp;

extern int counter_red;
extern int counter_green;
extern int counter_yellow;



#endif /* INC_GLOBAL_H_ */
