/*
 * lt_uart.h
 *
 *  Created on: Sep 14, 2024
 *      Author: user
 */

#ifndef INC_LT_UART_H_
#define INC_LT_UART_H_

extern uint8_t rx_data1;
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
extern int __io_putchar(int ch);

#endif /* INC_LT_UART_H_ */
