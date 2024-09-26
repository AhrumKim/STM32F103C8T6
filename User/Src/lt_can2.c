/*
 * lt_can2.c
 *
 *  Created on: Sep 15, 2024
 *      Author: user
 */

#include "stdint.h"
#include "stdio.h"
#include "lt_global_defs.h"
#include "lt_systick.h"
#include "lt_timer.h"
#include "lt_led.h"

#if defined CAN_ENABLE
#include "can.h"
#include "lt_can2.h"


void can_txrx_process_demo(void)
{
	static uint32_t can_systick = 0;

	if (get_systick() >= can_systick + 3000)
	{
		// CAN Tx
		if (can_rx_run_completed == 1)
		{
			can_rx_run_completed = 0;
			can_tx_process();
			printf("\r\ncan tx processed .. ");
			printf("\r\n");
		}
		can_systick = get_systick();
	}

	// CAN Rx
	if (can_rx_int_flag == 1)
	{
		can_rx_int_flag = 0;
		can_rx_process();
		printf("\r\ncan rx processed .. ");
		printf("\r\n>>==============================================END<<");
		printf("\r\n");
	}

	if (get_can_rx_led_duration_timer() == 0)
		pb12_led_off();
}

void can_tx_process_demo(void)
{
	static uint32_t can_systick = 0;

	if (get_systick() >= can_systick + 3000)
	{
		// CAN Tx
		//if (can_rx_run_completed == 1)
		{
			can_rx_run_completed = 0;
			can_tx_process();
			printf("\r\ncan tx processed .. ");
			printf("\r\n");
		}
		can_systick = get_systick();
	}

	if (get_can_tx_led_duration_timer() == 0)
		pb12_led_off();
}

uint8_t can_tx_run_completed = 0;
void can_tx_process(void)
{
	uint32_t i = 0;
	static uint8_t tx_change = 0;
	static uint32_t tx_pkt_cnt = 0;

	// 메인 초기화시에 1회 설정으로 끝내도 되는 것 같아 그리로 옮김
	//can_tx_packet_header_config();

	printf("\r\n");
	printf("\r\n>>BEGIN============================================<<");
	printf("\r\nCAN Op Mode : %s", _can_op_mode?"Normal":"Loopback");
	printf("\r\n>> CAN Tx Data[%d] : ", (int)++tx_pkt_cnt);
	for (i=0; i<CanTxHeader.DLC; i++)
	{
		CanTxData[i] = i + tx_change;
		printf("%d ", CanTxData[i]);
	}

	HAL_CAN_AddTxMessage(&hcanHandle, &CanTxHeader, &CanTxData[0], &TxMailBox);

	tx_change++;
	if (tx_change >= 100)
		tx_change = 0;

	can_tx_run_completed = 1;
}


void can_rx_process_demo(void)
{
	// CAN Rx
	if (can_rx_int_flag == 1)
	{
		can_rx_int_flag = 0;
		can_rx_process();
		printf("\r\ncan rx processed .. ");
		printf("\r\n>>==============================================END<<");
		printf("\r\n");
	}

	if (get_can_rx_led_duration_timer() == 0)
		pb12_led_off();
}



uint8_t can_rx_run_completed = 1;
void can_rx_process(void)
{
	uint32_t i=0;

	printf("\r\n");
	printf("\r\n>>----------------------------------------------<<");
	//printf("\r\nCAN Filtering Mode : %s", "16bit List");
	printf("\r\nCAN Op Mode : %s", _can_op_mode?"Normal":"Loopback");
	printf("\r\nCAN Filtering Mode : %s %s",
																_can_filter_bit?"32bit":"16bit",
																_can_filter_mode?"Mask":"List");
	printf("\r\n>>----------------------------------------------<<");
	printf("\r\nStdID : 0x%04lx, IDE : 0x%ld, DLC : %ld",
						CanRxHeader.StdId, CanRxHeader.IDE, CanRxHeader.DLC);

	printf("\r\n>> CAN Rx Data : ");
	for (i=0; i<CanRxHeader.DLC; i++)
	{
		printf("%d ", CanRxData[i]);
	}

	can_rx_run_completed = 1;
}

uint8_t _can_filter_mode = 0, _can_filter_bit = 0, _can_op_mode = 0;
void can_operation_mode_display(void)
{
#if defined	_CAN_FILTER_LIST_MODE
	_can_filter_mode = 0;
#elif defined _CAN_FILTER_MASK_MODE
	_can_filter_mode = 1;
#endif

#if defined _CAN_16BIT_MODE
	_can_filter_bit = 0;
#elif defined _CAN_32BIT_MODE
	_can_filter_bit = 1;
#endif

	if (hcan.Init.Mode == CAN_MODE_NORMAL)
		_can_op_mode = 1;
	else if (hcan.Init.Mode == CAN_MODE_LOOPBACK)
		_can_op_mode = 0;
}

CAN_RxHeaderTypeDef CanRxHeader;
CAN_TxHeaderTypeDef CanTxHeader;
uint8_t CanRxData[8] = {0,};
uint8_t CanTxData[8] = {0,};
uint32_t TxMailBox = 0;
uint8_t can_rx_int_flag = 0;
#define	CAN_RX_LED_DURATION	100

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	// 여기서는 printf 가 안먹는 것 같다.
	// printf 사용시 메모리 할당체계와 관계가 있을 것 같다는 게 있는데 여기서는 어디서 손을 대야하는 지
	// 잘 모르것다.

	//printf("\r\nCan Rx0 int");
	// Get Rx message
	if (hcan->Instance == CAN1)
	{
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanRxHeader, &CanRxData[0]);
		pb12_led_toggle();
		set_can_rx_led_duration_timer(CAN_RX_LED_DURATION);
		can_rx_int_flag = 1;
	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	printf("\r\nCan Rx1 int");
	// Get Rx message
	if (hcan->Instance == CAN1)
	{
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CanRxHeader, &CanRxData[0]);
		set_can_rx_led_duration_timer(200);
		can_rx_int_flag = 1;
	}
}



void can_tx_packet_header_config(void)
{
#if defined _CAN_FILTER_LIST_MODE
	CanTxHeader.StdId = 0x543;                 // Standard Identifier, 0 ~ 0x7FF, 오리지날 0x543
#elif defined _CAN_FILTER_MASK_MODE
#if defined _CAN_16BIT_MODE
	CanTxHeader.StdId = 0x541;//0x543;                 // Standard Identifier, 0 ~ 0x7FF, 오리지날 0x543
#elif defined _CAN_32BIT_MODE
	CanTxHeader.StdId = 0x542;
#endif
#endif
	CanTxHeader.ExtId = 0x210;                 // Extended Identifier, 0 ~ 0x1FFFFFFF
	CanTxHeader.RTR = CAN_RTR_DATA;            // 전송하는 메세지의 프레임 타입, DATA or REMOTE
	CanTxHeader.IDE = CAN_ID_STD;              // 전송하는 메세지의 식별자 타입, STD or EXT
	CanTxHeader.DLC = 8;                       // 송신 프레임 길이, 0 ~ 8 byte
	CanTxHeader.TransmitGlobalTime = DISABLE;  // 프레임 전송 시작될 때 timestamp counter 값을 capture.
}

CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
void can_rx_packet_filter_config(void)
{
	/* CAN Filter 설정 */
	CanRxFilterConfig.FilterBank = 0;
#if defined	_CAN_FILTER_MASK_MODE//Original
#if 0//1// original with all zero
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0000;
	CanRxFilterConfig.FilterIdLow = 0x0000;
	CanRxFilterConfig.FilterMaskIdHigh = 0x0000;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = 0x0000;
#else// modify
#if defined _CAN_16BIT_MODE//0//--1, 16bit
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x543 << 5;
	CanRxFilterConfig.FilterMaskIdHigh = 0x7FC << 5;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterIdLow = 0x543 << 5;
	CanRxFilterConfig.FilterMaskIdLow = 0x7fC << 5;
#elif defined _CAN_32BIT_MODE//--1, 32bit
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x7FC << 5;
	CanRxFilterConfig.FilterIdLow = 0;
	CanRxFilterConfig.FilterMaskIdHigh = (0x3FFFF<<3)>>16;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = (0x3FFFF<<3) | CAN_ID_EXT;
/*
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0543<<5;							//
	CanRxFilterConfig.FilterIdLow = 0;						//
	CanRxFilterConfig.FilterMaskIdHigh = (0x210<<3)>>16;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = (0x210<<3) | CAN_ID_EXT;
*/
#endif//--1
#endif
#elif defined	_CAN_FILTER_LIST_MODE
#if defined _CAN_16BIT_MODE//1// 16bit list mode ok
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0543<<5;							// OK
	CanRxFilterConfig.FilterIdLow = 0x0543<<5;							// OK
	CanRxFilterConfig.FilterMaskIdHigh = 0x0000;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = 0x0000;
#elif defined _CAN_32BIT_MODE// 32bit list modify
	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0543<<5;							//
	CanRxFilterConfig.FilterIdLow = 0;						//
	CanRxFilterConfig.FilterMaskIdHigh = (0x210<<3)>>16;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = (0x210<<3) | CAN_ID_EXT;
#endif//
#endif
	CanRxFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;		// choose whether RxFiFo0 or RxFiFo1
	CanRxFilterConfig.FilterActivation = ENABLE;							// choose whether use Filter or Not
	CanRxFilterConfig.SlaveStartFilterBank = 14;              // CAN2의 FilterBank시작 위치, CAN2를 사용한다면 FilterBank를 SlaveStartFilterBank보다 크게 설정해야 함.
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Can_Error_Handler(void)
{
  /* Turn LED2 on */
  printf("\r\nCAN Error_Handler !!!");
  while(1)
  {
  }
}

#endif//CAN_ENABLE


