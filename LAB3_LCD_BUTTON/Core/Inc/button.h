/*
 * button.h
 *
 *  Created on: Sep 25, 2023
 *      Author: HaHuyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include"stdbool.h"

extern uint16_t button_count[16];

void button_init();
void button_Scan();

bool is_button_pressed(int);

#endif /* INC_BUTTON_H_ */

