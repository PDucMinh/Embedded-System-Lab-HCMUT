/*
 * software_timer.h
 *
 *  Created on: Sep 18, 2024
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

void timer_init();
void set_timer(uint16_t duration);
uint8_t is_flag();

void set_timer1(uint16_t duration);
uint8_t is_flag1();
#endif /* INC_SOFTWARE_TIMER_H_ */
