/*
 * SmartCar_eru.c
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */
#include <SmartCar_Eru.h>
#include "SmartCar_GPIO.h"
#include "SmartCar_Assert.h"

IfxScu_Req_In* eru_mux(ERU_PIN_enum eru_pin)
{
    switch(eru_pin)
    {
        case CH0_P10_7:   return &IfxScu_REQ4_P10_7_IN;
        case CH0_P15_4:   return &IfxScu_REQ0_P15_4_IN;

        case CH1_P10_8:   return &IfxScu_REQ5_P10_8_IN;
        case CH1_P14_3:   return &IfxScu_REQ10_P14_3_IN;

        case CH2_P00_4:   return &IfxScu_REQ7_P00_4_IN;
        case CH2_P02_1:   return &IfxScu_REQ14_P02_1_IN;
        case CH2_P10_2:   return &IfxScu_REQ2_P10_2_IN;

        case CH3_P02_0:   return &IfxScu_REQ6_P02_0_IN;
        case CH3_P10_3:   return &IfxScu_REQ3_P10_3_IN;
        case CH3_P14_1:   return &IfxScu_REQ15_P14_1_IN;

        case CH4_P15_5:   return &IfxScu_REQ13_P15_5_IN;
        case CH4_P33_7:   return &IfxScu_REQ8_P33_7_IN;

        case CH5_P15_8:   return &IfxScu_REQ1_P15_8_IN;

        case CH6_P11_10:  return &IfxScu_REQ12_P11_10_IN;
        case CH6_P20_0:   return &IfxScu_REQ9_P20_0_IN;

        case CH7_P15_1:   return &IfxScu_REQ16_P15_1_IN;
        case CH7_P20_9:   return &IfxScu_REQ11_P20_9_IN;

        default:SMARTCAR_ASSERT(FALSE);          return NULL;
    }
}


void Eru_Init(ERU_PIN_enum eru_pin, TRIGGER_enum trigger)
{
    boolean interrupt_state = disableInterrupts();

    IfxScu_Req_In *reqPin;

    reqPin = eru_mux(eru_pin);

    IfxScuEru_initReqPin(reqPin, IfxPort_InputMode_pullUp);

    IfxScuEru_InputChannel inputChannel = (IfxScuEru_InputChannel)reqPin->channelId;

    IfxScuEru_InputNodePointer triggerSelect = (IfxScuEru_InputNodePointer)(eru_pin/3);
    IfxScuEru_OutputChannel    outputChannel = (IfxScuEru_OutputChannel)(eru_pin/3);

    switch(trigger)
    {
        case RISING:
        {
            IfxScuEru_disableFallingEdgeDetection(inputChannel);
            IfxScuEru_enableRisingEdgeDetection(inputChannel);
        }break;

        case FALLING:
        {
            IfxScuEru_enableFallingEdgeDetection(inputChannel);
            IfxScuEru_disableRisingEdgeDetection(inputChannel);
        }break;

        case BOTH:
        {
            IfxScuEru_enableFallingEdgeDetection(inputChannel);
            IfxScuEru_enableRisingEdgeDetection(inputChannel);
        }break;


    }

    IfxScuEru_enableTriggerPulse(inputChannel);
    IfxScuEru_connectTrigger(inputChannel, triggerSelect);

    IfxScuEru_setFlagPatternDetection(outputChannel, inputChannel, TRUE);
    IfxScuEru_enablePatternDetectionTrigger(outputChannel);
    IfxScuEru_setInterruptGatingPattern(outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);


    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)outputChannel % 4];
    IfxSrc_Tos eru_service;
    uint8 eru_priority;
    switch((eru_pin/3)%4)
    {
        case 0:
        {
            eru_service  = ERU_CH0_CH4_INT_SERVICE;
            eru_priority = ERU_CH0_CH4_INT_PRIO;
        }break;

        case 1:
        {
            eru_service  = ERU_CH1_CH5_INT_SERVICE;
            eru_priority = ERU_CH1_CH5_INT_PRIO;
        }break;

        case 2:
        {
            eru_service  = ERU_CH2_CH6_INT_SERVICE;
            eru_priority = ERU_CH2_CH6_INT_PRIO;
        }break;

        case 3:
        {
            eru_service  = ERU_CH3_CH7_INT_SERVICE;
            eru_priority = ERU_CH3_CH7_INT_PRIO;
        }break;

    }
#pragma warning 507
    IfxSrc_init(src, eru_service, eru_priority);
#pragma warning default
    IfxSrc_enable(src);

    restoreInterrupts(interrupt_state);
}


void Eru_Enable(ERU_PIN_enum eru_pin)
{
    IfxScuEru_OutputChannel    outputChannel = (IfxScuEru_OutputChannel)(eru_pin/3);

    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)outputChannel % 4];
    IfxSrc_enable(src);
}


void Eru_Disable(ERU_PIN_enum eru_pin)
{
    IfxScuEru_OutputChannel    outputChannel = (IfxScuEru_OutputChannel)(eru_pin/3);

    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)outputChannel % 4];
    IfxSrc_disable(src);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO外部中断服务函数示例
//  @note       一个通道只能选择其中一个引脚作为 外部中断的输入
//-------------------------------------------------------------------------------------------------------------------
IFX_INTERRUPT(eru_ch0_ch4_isr, 0, ERU_CH0_CH4_INT_PRIO)
{
    enableInterrupts();//开启中断嵌套
    if(GET_GPIO_FLAG(CH0_P15_4))//通道0中断
    {
        CLEAR_GPIO_FLAG(CH0_P15_4);
    }
    if(GET_GPIO_FLAG(CH4_P15_5))//通道4中断
    {
        CLEAR_GPIO_FLAG(CH4_P15_5);
    }
}

IFX_INTERRUPT(eru_ch1_ch5_isr, 0, ERU_CH1_CH5_INT_PRIO)
{
    enableInterrupts();//开启中断嵌套
    if(GET_GPIO_FLAG(CH1_P10_8))//通道1中断
    {
        CLEAR_GPIO_FLAG(CH1_P10_8);
    }
    if(GET_GPIO_FLAG(CH5_P15_8))//通道5中断
    {
        CLEAR_GPIO_FLAG(CH5_P15_8);
    }
}
