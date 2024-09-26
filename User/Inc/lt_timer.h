/*
 * lt_timer.h
 *
 *  Created on: Sep 16, 2024
 *      Author: user
 */

#ifndef INC_LT_TIMER_H_
#define INC_LT_TIMER_H_

#include "stdint.h"

extern void timer_value_decrease_function(void);

// led duration timer
extern uint32_t can_rx_led_duration_timer_value;
extern void set_can_rx_led_duration_timer(uint32_t TimerTick32);
extern uint32_t get_can_rx_led_duration_timer(void);

extern uint32_t can_tx_led_duration_timer_value;
extern void set_can_tx_led_duration_timer(uint32_t TimerTick32);
extern uint32_t get_can_tx_led_duration_timer(void);

#endif /* INC_LT_TIMER_H_ */
