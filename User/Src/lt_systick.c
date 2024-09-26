/*
 * lt_systick.c
 *
 *  Created on: Sep 14, 2024
 *      Author: user
 */


#include "stdint.h"
#include "lt_global_defs.h"
#include "lt_timer.h"
#include "lt_systick.h"


static uint32_t lt_systick = 0;

void inc_systick(void)
{
	lt_systick++;

	timer_value_decrease_function();

	//if (can_rx_led_duration_timer_value > 0) can_rx_led_duration_timer_value--;
}

uint32_t get_systick(void)
{
	return lt_systick;
}
