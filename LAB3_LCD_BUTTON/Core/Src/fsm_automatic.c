/*
 * fsm_mode.c
 *
 *  Created on: Oct 22, 2023
 *      Author: PC
 */
#include "global.h"


void fsm_automatic_run() {
	switch(lcd_status){
	case INIT:
		if(is_flag()){
			lcd_Clear(WHITE);
			lcd_status = AUTO_RED_GREEN;
			set_timer((counter_green)*1000);
			set_timer1(1000);
		}
		break;

	case AUTO_RED_GREEN:
		if(is_flag()) {
			lcd_status = AUTO_RED_YELLOW;
			lcd_set_traffic1(RED,counter_red-traffic_counter);
			lcd_set_traffic2(GREEN, counter_green-traffic_counter);
			traffic_counter=0;
			set_timer((counter_yellow)*1000);
			set_timer1(1000);
		}
		if(is_flag1()){
			lcd_set_traffic1(RED,counter_red-traffic_counter);
			lcd_set_traffic2(GREEN, counter_green-traffic_counter);
			traffic_counter++;
			set_timer1(1000);
		}
		if(is_button_pressed(0)) {
			lcd_status= INIT_SETTING;
			traffic_counter=0;
			set_timer(5);
		}
		break;

	case AUTO_RED_YELLOW:
		if(is_flag()) {
			lcd_status = AUTO_GREEN_RED;
			lcd_set_traffic1(RED,counter_yellow-traffic_counter);
			lcd_set_traffic2(YELLOW, counter_yellow-traffic_counter);
			traffic_counter=0;
			set_timer((counter_green)*1000);
			set_timer1(1000);
		}
		if(is_flag1()){
			lcd_set_traffic1(RED,counter_yellow-traffic_counter);
			lcd_set_traffic2(YELLOW, counter_yellow-traffic_counter);
			traffic_counter++;
			set_timer1(1000);
		}
		if(is_button_pressed(0)) {
			lcd_status= INIT_SETTING;
			traffic_counter=0;
			set_timer(5);
	    }
		break;

	case AUTO_GREEN_RED:
		if(is_flag()) {
			lcd_status = AUTO_YELLOW_RED;
			lcd_set_traffic1(GREEN,counter_green-traffic_counter);
			lcd_set_traffic2(RED, counter_red-traffic_counter);
			traffic_counter=0;
			set_timer((counter_yellow)*1000);
			set_timer1(1000);
		}
		if(is_flag1()){
			lcd_set_traffic1(GREEN,counter_green-traffic_counter);
			lcd_set_traffic2(RED, counter_red-traffic_counter);
			traffic_counter++;
			set_timer1(1000);
		}
		if(is_button_pressed(0)) {
			lcd_status= INIT_SETTING;
			traffic_counter=0;
			set_timer(5);
	    }
		break;

	case AUTO_YELLOW_RED:
		if(is_flag()) {
			lcd_status = AUTO_RED_GREEN;
			lcd_set_traffic1(YELLOW,counter_yellow-traffic_counter);
			lcd_set_traffic2(RED, counter_yellow-traffic_counter);
			traffic_counter=0;
			set_timer((counter_green)*1000);
			set_timer1(1000);

		}
		if(is_flag1()){
			lcd_set_traffic1(YELLOW,counter_yellow-traffic_counter);
			lcd_set_traffic2(RED, counter_yellow-traffic_counter);
			traffic_counter++;
			set_timer1(1000);
		}
		if(is_button_pressed(0)) {
			lcd_status= INIT_SETTING;
			traffic_counter=0;
			set_timer(5);
	    }
	default:
		break;
	}
}

