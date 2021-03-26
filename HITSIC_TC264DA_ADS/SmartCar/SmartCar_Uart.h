/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,���������ܳ����¾��ֲ�
 * All rights reserved.
 *
 * @file            SmartCar_Encoder
 * @company         ���������ܳ����¾��ֲ�
 * @author          ���� qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note��UART/ASCLIN_ASC

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_UART_H
#define SMARTCAR_UART_H

#include <ifxAsclin_Asc.h>

#define IFX_INTPRIO_ASCLIN0_TX  10
#define IFX_INTPRIO_ASCLIN0_RX  11
#define IFX_INTPRIO_ASCLIN0_ER  12

#define IFX_INTPRIO_ASCLIN1_TX  13
#define IFX_INTPRIO_ASCLIN1_RX  14
#define IFX_INTPRIO_ASCLIN1_ER  15

#define IFX_INTPRIO_ASCLIN2_TX  16
#define IFX_INTPRIO_ASCLIN2_RX  17
#define IFX_INTPRIO_ASCLIN2_ER  18

#define IFX_INTPRIO_ASCLIN3_TX  19
#define IFX_INTPRIO_ASCLIN3_RX  20
#define IFX_INTPRIO_ASCLIN3_ER  21

extern IfxAsclin_Asc uart[4];

/*
 * brief ��ö�Ӧuartģ����ж����ȼ�
 * */
void Get_Uart_Priority(uint8 uart_num);

/*
 * brief ��ʼ��uart
 * para tx_pin ���ͽ�
 * para rx_pin ���ս�
 * para baudrate ������
 * para uart_num uartģ��
 * sample         SmartCar_Uart_Init(IfxAsclin0_TX_P14_0_OUT,IfxAsclin0_RXA_P14_1_IN,115200,0)
 * */
void SmartCar_Uart_Init(IfxAsclin_Tx_Out tx_pin,IfxAsclin_Rx_In rx_pin,float baudrate,uint8 uart_num);

/*
 * brief uart��������
 * */
void SmartCar_Uart_Transfer(uint8* txData, Ifx_SizeT count ,uint8 uart_num);

/*
 * brief uart����һ�����ݣ�����ͷ�ص�������
 * */
uint8 SmartCar_Uart_Queue(uint8* rxData, uint8 uart_num);

#endif
