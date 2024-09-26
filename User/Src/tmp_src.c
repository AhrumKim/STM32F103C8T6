/*
 * tmp_src.c
 *
 *  Created on: Sep 16, 2024
 *      Author: user
 */


#if 0//1//0//-0

int main(void)
{
  /* Initialize all configured peripherals */
  MX_CAN_Init();

  /* USER CODE BEGIN 2 */
  // Config for Can Tx
  can_tx_packet_header_config();
  // can filter init for can rx
  can_rx_filter_config();
  can_rx_packet_filter_config(&hcanHandle, &CanRxFilterConfig);
  HAL_CAN_Start(&hcanHandle);
  /* Activate CAN RX notification */
  HAL_CAN_ActivateNotification(&hcanHandle, CAN_IT_RX_FIFO0_MSG_PENDING);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  	// 2. CAN Tranceiver
  	can_txrx_process_demo();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


int main(void)
{
  MX_USART1_UART_Init();
  MX_CAN_Init();

  /* USER CODE BEGIN 2 */
  can_tx_packet_header_config();
  can_rx_packet_filter_config();
  HAL_CAN_ConfigFilter(&hcanHandle, &CanRxFilterConfig);
  HAL_CAN_Start(&hcanHandle);
  /* Activate CAN RX notification */
  HAL_CAN_ActivateNotification(&hcanHandle, CAN_IT_RX_FIFO0_MSG_PENDING);
  can_operation_mode_display();
  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {
  	// 1. systick
  	static int print_cnt = 0;
  	if (get_systick() >= (prev_systick+500))
  	{
  		printf("\r\nHello : 2024-09.20-3 : %d", ++print_cnt);
  		prev_systick = get_systick();
  	}
  	// 2. CAN Tranceiver
  	can_rx_process_demo();
  }
}

#endif//-0

#if 0//1//0//1//-1
CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
void can_rx_packet_filter_config(void)
{
	/* CAN Filter 설정 */
	CanRxFilterConfig.FilterBank = 0;

	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0543<<5;								// OK
	CanRxFilterConfig.FilterIdLow = 0x0543<<5;								// OK
	CanRxFilterConfig.FilterMaskIdHigh = 0x0000;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = 0x0000;

	CanRxFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;		// choose whether RxFiFo0 or RxFiFo1
	CanRxFilterConfig.FilterActivation = ENABLE;							// choose whether use Filter or Not
	CanRxFilterConfig.SlaveStartFilterBank = 14;              // CAN2의 FilterBank시작 위치, CAN2를 사용한다면 FilterBank를 SlaveStartFilterBank보다 크게 설정해야 함.
}

CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
void can_rx_packet_filter_config(void)
{
	/* CAN Filter 설정 */
	CanRxFilterConfig.FilterBank = 0;

	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;							// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x0543<<5;												//
	CanRxFilterConfig.FilterIdLow = 0;																	//
	CanRxFilterConfig.FilterMaskIdHigh = (0x210<<3)>>16;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = (0x210<<3) | CAN_ID_EXT;

	CanRxFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;						// choose whether RxFiFo0 or RxFiFo1
	CanRxFilterConfig.FilterActivation = ENABLE;											// choose whether use Filter or Not
	CanRxFilterConfig.SlaveStartFilterBank = 14;              				// CAN2의 FilterBank시작 위치, CAN2를 사용한다면 FilterBank를 SlaveStartFilterBank보다 크게 설정해야 함.
}


CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
void can_rx_packet_filter_config(void)
{
	/* CAN Filter 설정 */
	CanRxFilterConfig.FilterBank = 0;

	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x543 << 5;
	CanRxFilterConfig.FilterMaskIdHigh = 0x7FC << 5;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterIdLow = 0x543 << 5;
	CanRxFilterConfig.FilterMaskIdLow = 0x7fC << 5;

	CanRxFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;		// choose whether RxFiFo0 or RxFiFo1
	CanRxFilterConfig.FilterActivation = ENABLE;							// choose whether use Filter or Not
	CanRxFilterConfig.SlaveStartFilterBank = 14;              // CAN2의 FilterBank시작 위치, CAN2를 사용한다면 FilterBank를 SlaveStartFilterBank보다 크게 설정해야 함.
}


//4
CAN_FilterTypeDef  CanRxFilterConfig;   // 필터 설정 구조체 변수
void can_rx_packet_filter_config(void)
{
	/* CAN Filter 설정 */
	CanRxFilterConfig.FilterBank = 0;

	CanRxFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	CanRxFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;								// CAN_FILTERMODE_IDMASK or CAN_FILTERMODE_IDLIST
	CanRxFilterConfig.FilterIdHigh = 0x7FC << 5;
	CanRxFilterConfig.FilterIdLow = 0;
	CanRxFilterConfig.FilterMaskIdHigh = (0x3FFFF<<3)>>16;              // 0x00000000 = 모든 ID를 받아들이겠다
	CanRxFilterConfig.FilterMaskIdLow = (0x3FFFF<<3) | CAN_ID_EXT;

	CanRxFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;							// choose whether RxFiFo0 or RxFiFo1
	CanRxFilterConfig.FilterActivation = ENABLE;												// choose whether use Filter or Not
	CanRxFilterConfig.SlaveStartFilterBank = 14;              					// CAN2의 FilterBank시작 위치, CAN2를 사용한다면 FilterBank를 SlaveStartFilterBank보다 크게 설정해야 함.
}

#endif//-1
