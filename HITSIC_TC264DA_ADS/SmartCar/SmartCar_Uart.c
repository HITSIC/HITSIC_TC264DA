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



#include "SmartCar_Uart.h"
#include "SmartCar_Upload.h"
/*����uart��һϵ�к������ȫ�ֱ���*/
IfxAsclin_Asc uart[4];
IfxAsclin_Asc_Config uartConfig;

/*tx*/
#define ASC_TX_BUFFER_SIZE 16
static uint8 ascTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
/*rx*/
#define ASC_RX_BUFFER_SIZE 16
static uint8 ascRxBuffer[4][ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


void Get_Uart_Priority(uint8 uart_num)
{
    switch(uart_num)
    {
    case 0:
    {
        uartConfig.interrupt.txPriority = IFX_INTPRIO_ASCLIN0_TX;
        uartConfig.interrupt.rxPriority = IFX_INTPRIO_ASCLIN0_RX;
        uartConfig.interrupt.erPriority = IFX_INTPRIO_ASCLIN0_ER;
    }
    break;
    case 1:
    {
        uartConfig.interrupt.txPriority = IFX_INTPRIO_ASCLIN1_TX;
        uartConfig.interrupt.rxPriority = IFX_INTPRIO_ASCLIN1_RX;
        uartConfig.interrupt.erPriority = IFX_INTPRIO_ASCLIN1_ER;
    }
    break;
    case 2:
    {
        uartConfig.interrupt.txPriority = IFX_INTPRIO_ASCLIN2_TX;
        uartConfig.interrupt.rxPriority = IFX_INTPRIO_ASCLIN2_RX;
        uartConfig.interrupt.erPriority = IFX_INTPRIO_ASCLIN2_ER;
    }
    break;
    case 3:
    {
        uartConfig.interrupt.txPriority = IFX_INTPRIO_ASCLIN3_TX;
        uartConfig.interrupt.rxPriority = IFX_INTPRIO_ASCLIN3_RX;
        uartConfig.interrupt.erPriority = IFX_INTPRIO_ASCLIN3_ER;
    }
    break;
    }
}



void SmartCar_Uart_Init(IfxAsclin_Tx_Out tx_pin,IfxAsclin_Rx_In rx_pin,float baudrate,uint8 uart_num)
{
    IfxCpu_disableInterrupts();//��ʼ��ʱ�ص��ж�
    /*��ʼ��asc��������*/
    volatile Ifx_ASCLIN *moudle = IfxAsclin_getAddress((IfxAsclin_Index)uart_num);
    IfxAsclin_Asc_initModuleConfig(&uartConfig, moudle);
    uartConfig.baudrate.prescaler = 4;
    uartConfig.baudrate.baudrate = baudrate;
    uartConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    Get_Uart_Priority(uart_num);
    uartConfig.interrupt.typeOfService =   IfxSrc_Tos_cpu0;//�ж���˭��Ӧ            !!!�Ƿ���Ҫ��Ϊֱ��ȷ��������˭��Ӧ�ж�
    /*���tx,rx�����С*/
    uartConfig.txBuffer = &ascTxBuffer[uart_num][0];
    uartConfig.txBufferSize = ASC_TX_BUFFER_SIZE;

    uartConfig.rxBuffer = &ascRxBuffer[uart_num][0];
    uartConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;
    /*��ʼ��asc�������*/
    const IfxAsclin_Asc_Pins pins = {
          NULL,                           IfxPort_InputMode_pullUp,    // CTS pin not used
          &rx_pin,   IfxPort_InputMode_pullUp,    // Rx pin
          NULL,                           IfxPort_OutputMode_pushPull, // RTS pin not used
          &tx_pin,   IfxPort_OutputMode_pushPull, // Tx pin
          IfxPort_PadDriver_cmosAutomotiveSpeed1
             };
    uartConfig.pins = &pins;
    IfxAsclin_Asc_initModule(&uart[uart_num], &uartConfig);
    IfxCpu_enableInterrupts();//�жϿ���
}

/*sample SmartCar_Uart_Transfer(send_buffer,9,0)      ʹ��asclin0����9����send_buffer[0]��ʼ������*/
void SmartCar_Uart_Transfer(uint8* txData, Ifx_SizeT count, uint8 uart_num)
{
    //IfxAsclin_Asc_blockingWrite(&uart[uart_num], 0x01);
    IfxAsclin_Asc_write(&uart[uart_num], txData, &count, TIME_INFINITE);
}

uint8 SmartCar_Uart_Queue(uint8* rxData, uint8 uart_num)
{
    if(IfxAsclin_Asc_getReadCount(&uart[uart_num]) > 0)
    {
        *rxData = IfxAsclin_Asc_blockingRead(&uart[uart_num]);
        //PRINFT("Data received %d",rxData[0]);
        return 1;
    }
    return 0;
}
