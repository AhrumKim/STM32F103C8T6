/*
 * lt_led.c
 *
 *  Created on: Sep 16, 2024
 *      Author: user
 */


#include "gpio.h"
#include "lt_global_defs.h"
#include "lt_led.h"

void pb12_led_on(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void pb12_led_off(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

void pb12_led_toggle(void)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
}
