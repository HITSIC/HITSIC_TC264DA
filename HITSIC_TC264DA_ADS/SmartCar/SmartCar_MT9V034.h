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
 * @note：摄像头相关
 *          摄像头数据相关脚默认使用从P00_0开始的八个引脚，使用DMA通道5作为摄像头DMA通道，场中断触发外部中断2

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_MT9V034_H
#define SMARTCAR_MT9V034_H

#include "SmartCar_Uart.h"
#include "SmartCar_Eru.h"
#include "SmartCar_EruDma.h"
#include "common.h"

#define MT9V034_W               188                 //图像宽度  范围1-188
#define MT9V034_H               120                 //图像高度  范围1-120

//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define MT9V034_COF_UART        1              //配置摄像头所使用到的串口
#define MT9V034_COF_UART_TX     IfxAsclin1_TX_P02_2_OUT
#define MT9V034_COF_UART_RX     IfxAsclin1_RXG_P02_3_IN

#define MT9V034_VSYNC_PIN       CH3_P02_0  //场中断引脚 可选范围参考ERU_PIN_enum枚举 不可与像素引脚选择为同一个通道，或者是共用中断的通道
                                                    //例如场中断选择ERU_CH3 那么像素引脚就不能选择ERU_CH7，因为3和7的中断是共用的。

#define MT9V034_DATA_PIN_MODULE        MODULE_P00               //定义D0数据引脚  假设D0定义为P00_0 那么D1所使用的引脚则为P00_1，依次类推
                                                    //可设置参数P00_0、P02_0、P15_0，不能设置为其他参数

#define MT9V034_PCLK_PIN        CH2_P02_1 //定义像素时钟引脚 可选范围参考ERU_PIN_enum枚举 不可与场中断引脚选择为同一个通道，或者是共用中断的通道
                                                    //例如场中断选择ERU_CH3 那么像素引脚就不能选择ERU_CH7，因为3和7的中断是共用的。

#define MT9V034_DMA_CH          IfxDma_ChannelId_5  //定义使用的DMA通道 0-47可选  通道号越大优先级越低

//摄像头命令枚举
typedef enum
{
    INIT = 0,               //摄像头初始化命令
    AUTO_EXP,               //自动曝光命令
    EXP_TIME,               //曝光时间命令
    FPS,                    //摄像头帧率命令
    SET_COL,                //图像列命令
    SET_ROW,                //图像行命令
    LR_OFFSET,              //图像左右偏移命令
    UD_OFFSET,              //图像上下偏移命令
    GAIN,                   //图像偏移命令
    CONFIG_FINISH,          //非命令位，主要用来占位计数

    COLOR_GET_WHO_AM_I = 0xEF,
    SET_EXP_TIME = 0XF0,    //单独设置曝光时间命令
    GET_STATUS,             //获取摄像头配置命令
    GET_VERSION,            //固件版本号命令

    SET_ADDR = 0XFE,        //寄存器地址命令
    SET_DATA                //寄存器数据命令
}CMD;

typedef enum //枚举端口电平
{
    CAMERA_BIN=1,       //小钻风
    CAMERA_BIN_UART,    //小钻风串口版本
    CAMERA_GRAYSCALE,   //总钻风
    CAMERA_COLOR       //凌瞳
}CAMERA_TYPE_enum;


extern uint8  uart_receive[3];         //仅用于接收配置信息时所用  禁止用户使用该变量
extern uint8  uart_receive_num;        //仅用于接收配置信息时所用  禁止用户使用该变量
extern vuint8 uart_receive_flag;  //仅用于接收配置信息时所用  禁止用户使用该变量
extern CAMERA_TYPE_enum camera_type;
extern uint8* camera_buffer_addr;

extern uint8    mt9v034_finish_flag;//一场图像采集完成标志位
extern uint8    mt9v034_image[MT9V034_H][MT9V034_W];

void MT9V034_Uart_Callback(void);
void MT9V034_SetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2]);
void MT9V034_GetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2]);
uint16 MT9V034_GetVersion(uint8 uart_num);
uint16 MT9V034_SetExptime(uint8 uart_num, uint16 light);
unsigned short MT9V034_Setreg(uint8 uart_num, uint8 addr, uint16 data);
void SmartCar_MT9V034_Init(void);
void MT9V034_VSYNC(void);
void MT9V034_DMA(void);
void SmartCar_Show_IMG(uint8* image, uint16 ro, uint16 co);

#endif
