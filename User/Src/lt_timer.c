/*
 * lt_timer.c
 *
 *  Created on: Sep 16, 2024
 *      Author: user
 */

#include "stdint.h"
#include "cmsis_gcc.h"
#include "lt_systick.h"
#include "lt_timer.h"


// 0. timer value decrement function
void timer_value_decrease_function(void)
{
	if (can_rx_led_duration_timer_value > 0) can_rx_led_duration_timer_value--;
	if (can_tx_led_duration_timer_value > 0) can_tx_led_duration_timer_value--;
}


// 1.
uint32_t can_rx_led_duration_timer_value = 0;

void set_can_rx_led_duration_timer(uint32_t TimerTick32)
{
	__disable_irq();

	can_rx_led_duration_timer_value = TimerTick32;

	__enable_irq();
}

uint32_t get_can_rx_led_duration_timer(void)
{
	uint32_t V32;

	__disable_irq();

	V32 = can_rx_led_duration_timer_value;

	__enable_irq();

	return	V32;
}


// 2.
uint32_t can_tx_led_duration_timer_value = 0;

void set_can_tx_led_duration_timer(uint32_t TimerTick32)
{
	__disable_irq();

	can_tx_led_duration_timer_value = TimerTick32;

	__enable_irq();
}

uint32_t get_can_tx_led_duration_timer(void)
{
	uint32_t V32;

	__disable_irq();

	V32 = can_tx_led_duration_timer_value;

	__enable_irq();

	return	V32;
}
