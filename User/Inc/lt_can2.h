/*
 * lt_can2.h
 *
 *  Created on: Sep 15, 2024
 *      Author: user
 */

#ifndef INC_LT_CAN2_H_
#define INC_LT_CAN2_H_

#include "can.h"

//////////////////////////////////////////////////////////////////
// Choose Operation Modes
//
// 0. Tx, Rx Operation Mode
#define	CAN_TRX_DEMO_MODE
//#define	CAN_TX_DEMO_MODE
//#define	CAN_RX_DEMO_MODE

#if defined CAN_TRX_DEMO_MODE
#undef 	CAN_TX_DEMO_MODE
#undef	CAN_RX_DEMO_MODE
#elif defined	CAN_TX_DEMO_MODE
#undef 	CAN_TRX_DEMO_MODE
#undef	CAN_RX_DEMO_MODE
#elif defined	CAN_RX_DEMO_MODE
#undef	CAN_TRX_DEMO_MODE
#undef	CAN_TX_DEMO_MODE
#endif

// 1. CAN MASK or LIST Mode
#define	_CAN_FILTER_LIST_MODE
//#define	_CAN_FILTER_MASK_MODE
#if defined _CAN_FILTER_MASK_MODE
#undef	_CAN_FILTER_LIST_MODE
#elif defined _CAN_FILTER_LIST_MODE
#undef	_CAN_FILTER_MASK_MODE
#endif

// 2. 16Bit or 32Bit Filter
#define	_CAN_16BIT_MODE
//#define	_CAN_32BIT_MODE
#if defined _CAN_16BIT_MODE
#undef	_CAN_32BIT_MODE
#elif defined _CAN_32BIT_MODE
#undef	_CAN_16BIT_MODE
#endif
// End of Operation Mode
//////////////////////////////////////////////////////////////////

#define	hcanHandle	hcan

extern CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
extern CAN_RxHeaderTypeDef CanRxHeader;
extern CAN_TxHeaderTypeDef CanTxHeader;
extern uint8_t CanRxData[8];
extern uint8_t CanTxData[8];
extern uint32_t TxMailBox;

extern uint8_t can_rx_int_flag;

extern uint8_t can_tx_run_completed;
extern uint8_t can_rx_run_completed;

extern uint8_t _can_filter_mode, _can_filter_bit, _can_op_mode;

extern void can_operation_mode_display(void);
extern void can_txrx_process_demo(void);
extern void can_tx_process_demo(void);
extern void can_rx_process_demo(void);

extern void can_tx_process(void);
extern void can_rx_process(void);
extern void can_tx_packet_header_config(void);
extern void Can_Error_Handler(void);
extern void can_rx_packet_filter_config(void);

#endif /* INC_LT_CAN2_H_ */
