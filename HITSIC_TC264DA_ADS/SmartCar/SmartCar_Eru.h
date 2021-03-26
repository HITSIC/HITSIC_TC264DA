/*
 * SmartCar_eru.h
 *
 *  Created on: 2021年1月22日
 *      Author:孙唯
 */

#ifndef SMARTCAR_SMARTCAR_ERU_H_
#define SMARTCAR_SMARTCAR_ERU_H_

#include "Src/Std/IfxSrc.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxScuEru.h"

// 枚举触发方式
typedef enum
{
    RISING,
    FALLING,
    BOTH,
}TRIGGER_enum;

// 枚举ERU通道
typedef enum
{
    //一个通道只能选择其中一个引脚作为 外部中断的输入
    //例如通道0 可选引脚为P10_7 和 P15_4，
    CH0_P10_7   = 0*3,  CH0_P15_4,                        //通道0可选引脚
    CH1_P10_8   = 1*3,  CH1_P14_3,                        //通道1可选引脚
    CH2_P00_4   = 2*3,  CH2_P02_1,  CH2_P10_2,            //通道2可选引脚
    CH3_P02_0   = 3*3,  CH3_P10_3,  CH3_P14_1,            //通道3可选引脚

    //通道4与通道0 共用中断函数 在中断内通过判断标志位来识别是哪个通道触发的中断
    CH4_P15_5  = 4*3,   CH4_P33_7,                        //通道4可选引脚
    //通道5与通道1 共用中断函数
    CH5_P15_8  = 5*3,                                     //通道5可选引脚
    //通道6与通道2 共用中断函数
    CH6_P11_10 = 6*3,  CH6_P20_0,                         //通道6可选引脚
    //通道7与通道3 共用中断函数
    CH7_P15_1  = 7*3,  CH7_P20_9,                         //通道7可选引脚
}ERU_PIN_enum;

//特别注意通道2 与 通道3都被摄像头占用

//------------GPIO中断参数相关定义------------
//通道0与通道4是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define ERU_CH0_CH4_INT_SERVICE IfxSrc_Tos_cpu0 //定义ERU通道0和通道4中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA 不可设置为其他值
#define ERU_CH0_CH4_INT_PRIO    40              //定义ERU通道0和通道4中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define ERU_CH1_CH5_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH1_CH5_INT_PRIO    41

#define ERU_CH2_CH6_INT_SERVICE IfxSrc_Tos_dma
#define ERU_CH2_CH6_INT_PRIO    5

#define ERU_CH3_CH7_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH3_CH7_INT_PRIO    43



//中断标志位获取
#define GET_GPIO_FLAG(eru_pin)      IfxScuEru_getEventFlagStatus((IfxScuEru_InputChannel)(eru_pin/3))
//中断标志位清除
#define CLEAR_GPIO_FLAG(eru_pin)    IfxScuEru_clearEventFlag((IfxScuEru_InputChannel)(eru_pin/3))


//-------------------------------------------------------------------------------------------------------------------
//  @brief      eru初始化(gpio中断)
//  @param      eru_pin         设置eru通道及引脚
//  @param      trigger         设置触发方式
//  @return     void
//  Sample usage:               eru_init(ERU_CH0_REQ0_P15_4, RISING);//eru通道0 使用P10_7引脚，上升沿触发中断
//-------------------------------------------------------------------------------------------------------------------
void Eru_Init(ERU_PIN_enum eru_pin, TRIGGER_enum trigger);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启eru中断
//  @param      eru_pin         设置eru通道及引脚
//  @return     void
//  Sample usage:               eru_enable_interrupt(ERU_CH0_REQ0_P15_4);
//-------------------------------------------------------------------------------------------------------------------
void Eru_Enable(ERU_PIN_enum eru_pin);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      关闭eru中断
//  @param      eru_pin         设置eru通道及引脚
//  @return     void
//  Sample usage:               eru_disable_interrupt(ERU_CH0_REQ0_P15_4);
//-------------------------------------------------------------------------------------------------------------------
void Eru_Disable(ERU_PIN_enum eru_pin);




#endif /* SMARTCAR_SMARTCAR_ERU_H_ */
