/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Encoder
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note：UART/ASCLIN_ASC

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#include "SmartCar_Uart.h"
#include "SmartCar_Upload.h"
/*关于uart的一系列宏变量及全局变量*/
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
    IfxCpu_disableInterrupts();//初始化时关掉中断
    /*初始化asc基础配置*/
    volatile Ifx_ASCLIN *moudle = IfxAsclin_getAddress((IfxAsclin_Index)uart_num);
    IfxAsclin_Asc_initModuleConfig(&uartConfig, moudle);
    uartConfig.baudrate.prescaler = 4;
    uartConfig.baudrate.baudrate = baudrate;
    uartConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    Get_Uart_Priority(uart_num);
    uartConfig.interrupt.typeOfService =   IfxSrc_Tos_cpu0;//中断由谁相应            !!!是否需要改为直接确定到底由谁相应中断
    /*相关tx,rx缓存大小*/
    uartConfig.txBuffer = &ascTxBuffer[uart_num][0];
    uartConfig.txBufferSize = ASC_TX_BUFFER_SIZE;

    uartConfig.rxBuffer = &ascRxBuffer[uart_num][0];
    uartConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;
    /*初始化asc引脚相关*/
    const IfxAsclin_Asc_Pins pins = {
          NULL,                           IfxPort_InputMode_pullUp,    // CTS pin not used
          &rx_pin,   IfxPort_InputMode_pullUp,    // Rx pin
          NULL,                           IfxPort_OutputMode_pushPull, // RTS pin not used
          &tx_pin,   IfxPort_OutputMode_pushPull, // Tx pin
          IfxPort_PadDriver_cmosAutomotiveSpeed1
             };
    uartConfig.pins = &pins;
    IfxAsclin_Asc_initModule(&uart[uart_num], &uartConfig);
    IfxCpu_enableInterrupts();//中断开启
}

/*sample SmartCar_Uart_Transfer(send_buffer,9,0)      使用asclin0发送9个从send_buffer[0]开始的数据*/
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
