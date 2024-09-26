/*
 * lt_uart.c
 *
 *  Created on: Sep 14, 2024
 *      Author: user
 */


#include "stdint.h"
#include "stdio.h"
#include "usart.h"
#include "lt_global_defs.h"
#include "lt_uart.h"

#include "usart.h"
#include "lt_uart.h"

int __io_putchar(int ch)
{
	(void)HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 100);

	return 1;
}


uint8_t rx_data1 = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		printf("\r\nrx_data1 : %c", (char)rx_data1);
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data1, 1);
	}
}
