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
 * @note：所有编码器采值使用引脚要自己选择，具体已罗列

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_ENCODER_H
#define SMARTCAR_ENCODER_H

#include "IfxGpt12_IncrEnc.h"

typedef short int16;
typedef enum
{
    GPT12_T2 = 0,
    GPT12_T3,
    GPT12_T4,
    GPT12_T5,
    GPT12_T6
}GPTn_enum;


/*
 * brief 初始化编码器相关引脚
 * para gptn 引脚使用的PGT12计数器号
 * para count_pin 计数引脚
 * para dir_pin 判断方向引脚
 * sample SmartCar_Encoder_Init(GPT12_T2, IfxGpt120_T2INA_P00_7_IN, IfxGpt120_T2EUDA_P00_8_IN)
 * */
void SmartCar_Encoder_Init(GPTn_enum gptn, IfxGpt12_TxIn_In count_pin,IfxGpt12_TxEud_In dir_pin);

/*
 * brief 获得编码器计数值
 * para gptn 引脚使用的PGT12计数器号
 * sample SmartCar_Encoder_Get(PGT12_T2);
 * */
int16 SmartCar_Encoder_Get(GPTn_enum gptn);

/*
 * brief 清除编码器计数值
 * para gtpn 引脚使用的PGT12计数器号
 * sample SmartCar_Encoder_Clear(GPT12_T2);
 * */
void SmartCar_Encoder_Clear(GPTn_enum gptn);

#endif
