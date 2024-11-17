/*
 * fsm_manual.c
 *
 *  Created on: Oct 23, 2023
 *      Author: PC
 */
#include "global.h"

void fsm_setting_run(){
	switch(lcd_status){
	case INIT_SETTING:
		lcd_Clear(WHITE);
		if(is_flag()){
			lcd_blinky(RED, counter_red);
			lcd_status=SETTING_RED;
			temp = counter_red;
			set_timer(500);
		}
		break;
	case SETTING_RED:
		if(is_button_pressed(0)){
			counter_red=temp;
			temp=counter_green;
			lcd_status=SETTING_GREEN;
			setting_status=SETTING_OFF;
			lcd_blinky(GREEN, counter_green);
			set_timer(500);
		}
		if(is_button_pressed(1)){
			if(counter_red<=99){
				counter_red++;
			}else{
				counter_red=counter_yellow+1;
			}
		}
		if(is_button_pressed(2)){
			temp=counter_red;
			counter_green=counter_red-counter_yellow;
		}
		if(is_flag()){
			lcd_blinky(RED, counter_red);
			set_timer(500);
		}
		break;
	case SETTING_GREEN:
		if(is_button_pressed(0)){
			counter_green=temp;
			temp=counter_yellow;
			lcd_status=SETTING_YELLOW;
			setting_status=SETTING_OFF;
			lcd_blinky(YELLOW, counter_yellow);
			set_timer(500);
		}
		if(is_button_pressed(1)){
			if(counter_green+counter_yellow<=99){
				counter_green++;
			}else counter_green=1;
		}
		if(is_button_pressed(2)){
			temp=counter_green;
			counter_red=counter_green+counter_yellow;
		}
		if(is_flag()){
			lcd_blinky(GREEN, counter_green);
			set_timer(500);
		}
		break;
	case SETTING_YELLOW:
		if(is_button_pressed(0)){
			counter_yellow=temp;
			temp=0;
			lcd_status=INIT;
			set_timer(10);
		}
		if(is_button_pressed(1)){
			if(counter_green+counter_yellow<=99){
				counter_yellow++;
			}else counter_yellow=1;
		}
		if(is_button_pressed(2)){
			temp=counter_yellow;
			counter_red = counter_green+counter_yellow;
		}
		if(is_flag()){
			lcd_blinky(YELLOW, counter_yellow);
			set_timer(500);
		}
		break;
	default:
		break;
	}
}
