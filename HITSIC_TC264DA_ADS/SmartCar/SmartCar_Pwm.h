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
 * @note：PWM信号输出

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_PWM_H
#define SMARTCAR_PWM_H


#include "IfxGtm_Atom_Pwm.h"

#define ATOM0_DUTY_MAX 10000//占空比最大值
#define ATOM1_DUTY_MAX 10000
#define ATOM2_DUTY_MAX 10000
#define ATOM3_DUTY_MAX 10000
#define CMU_CLK_FREQ           20000000.0f//最大频率为100000000

#define ATOM0_CH0_PRIO 20


/*
 * brief 初始化引脚作为pwm输出
 * */
void GTM_Pwm_Init();

/*
 * brief 初始化引脚作为pwm输出引脚，并设定其初始频率及占空比
 *sample SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_0_TOUT0_P02_0_OUT, 50, 760);//引脚P02_0上的输出pwm信号频率50，占空比760/10000
 * */
void SmartCar_Gtm_Pwm_Init(IfxGtm_Atom_ToutMap* pwm_channel, uint32 freq, uint32 duty);

/*brief 重新设置输出占空比
 * para pwm_channel 本次pwm输出使用引脚
 * para duty 更改后的pwm输出占空比
 * sample SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_0_TOUT0_P02_0_OUT, 760)//设置引脚P02_0上pwm占空比为760/10000
 * */
void SmartCar_Gtm_Pwm_Setduty(IfxGtm_Atom_ToutMap* pwm_channel, uint32 duty);


#endif
