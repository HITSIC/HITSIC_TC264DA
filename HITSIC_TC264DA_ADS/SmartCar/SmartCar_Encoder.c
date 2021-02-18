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



#include "SmartCar_Encoder.h"


/*
 * check in file Libraries/iLLD/TC26B/Tricore/_PinMap/IfxI2c_PinMap.c
  * the possible pin select for Gpt12
 * T2:
 * count_pin:IfxGpt120_T2INA_P00_7_IN IfxGpt120_T2INB_P33_7_IN
 * dir_pin:IfxGpt120_T2EUDA_P00_8_IN IfxGpt120_T2EUDB_P33_6_IN
 * T3:
 * count_pin:IfxGpt120_T3INA_P02_6_IN IfxGpt120_T3INB_P10_4_IN
 * dir_pin:IfxGpt120_T3EUDA_P02_7_IN IfxGpt120_T3EUDB_P10_7_IN
 * T4:
 * count_pin:IfxGpt120_T4INA_P02_8_IN IfxGpt120_T4INB_P10_8_IN
 * dir_pin:IfxGpt120_T4EUDA_P00_9_IN IfxGpt120_T4EUDB_P33_5_IN
 * T5:
 * count_pin:IfxGpt120_T5INA_P21_7_IN IfxGpt120_T5INB_P10_3_IN
 * dir_pin:IfxGpt120_T5EUDA_P21_6_IN IfxGpt120_T5EUDB_P10_1_IN
 * T6:
 * count_pin:IfxGpt120_T6INA_P20_3_IN IfxGpt120_T6INB_P10_2_IN
 * dir_pin:IfxGpt120_T6EUDA_P20_0_IN IfxGpt120_T6EUDB_P10_0_IN
 */




void SmartCar_Encoder_Init(GPTn_enum gptn, IfxGpt12_TxIn_In count_pin,IfxGpt12_TxEud_In dir_pin)
{
    IfxGpt12_enableModule(&MODULE_GPT120);
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_4);//set the prescale for GPT1 and GPT2
    IfxGpt12_setGpt2BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt2BlockPrescaler_4);
    IfxGpt12_initTxInPinWithPadLevel(&count_pin, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);//inital count pin
    IfxGpt12_initTxEudInPinWithPadLevel(&dir_pin, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);//inital direction pin
    switch(gptn)
    {
        case GPT12_T2:
        {
            IfxGpt12_T2_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T2_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T2_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T2_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case GPT12_T3:
        {
            IfxGpt12_T3_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T3_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T3_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case GPT12_T4:
        {
            IfxGpt12_T4_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T4_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T4_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }break;

        case GPT12_T5:
        {
            IfxGpt12_T5_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T5_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T5_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T5_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case GPT12_T6:
        {
            IfxGpt12_T6_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T6_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T6_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T6_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
    }
}


int16 SmartCar_Encoder_Get(GPTn_enum gptn)
{
    switch(gptn)
    {
        case GPT12_T2: return (int16)IfxGpt12_T2_getTimerValue(&MODULE_GPT120);
        case GPT12_T3: return (int16)IfxGpt12_T3_getTimerValue(&MODULE_GPT120);
        case GPT12_T4: return (int16)IfxGpt12_T4_getTimerValue(&MODULE_GPT120);
        case GPT12_T5: return (int16)IfxGpt12_T5_getTimerValue(&MODULE_GPT120);
        case GPT12_T6: return (int16)IfxGpt12_T6_getTimerValue(&MODULE_GPT120);
        default: return 0;
    }
}


void SmartCar_Encoder_Clear(GPTn_enum gptn)
{
    switch(gptn)
    {
        case GPT12_T2: IfxGpt12_T2_setTimerValue(&MODULE_GPT120, 0); break;
        case GPT12_T3: IfxGpt12_T3_setTimerValue(&MODULE_GPT120, 0); break;
        case GPT12_T4: IfxGpt12_T4_setTimerValue(&MODULE_GPT120, 0); break;
        case GPT12_T5: IfxGpt12_T5_setTimerValue(&MODULE_GPT120, 0); break;
        case GPT12_T6: IfxGpt12_T6_setTimerValue(&MODULE_GPT120, 0); break;
    }
}
