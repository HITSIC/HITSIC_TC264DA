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



#include "SmartCar_Pwm.h"


/* check in file Libraries/iLLD/TC26B/Tricore/_PinMap/IfxGtm_PinMap.c
 *  ATOM0:
 *  Channel0:IfxGtm_ATOM0_0_TOUT0_P02_0_OUT IfxGtm_ATOM0_0_TOUT109_P10_7_OUT IfxGtm_ATOM0_0_TOUT48_P22_1_OUT IfxGtm_ATOM0_0_TOUT53_P21_2_OUT IfxGtm_ATOM0_0_TOUT85_P14_5_OUT IfxGtm_ATOM0_0_TOUT8_P02_8_OUT IfxGtm_ATOM0_0_TOUT9_P00_0_OUT
 *  Channel1:IfxGtm_ATOM0_1_TOUT103_P10_1_OUT IfxGtm_ATOM0_1_TOUT10_P00_1_OUT IfxGtm_ATOM0_1_TOUT11_P00_2_OUT IfxGtm_ATOM0_1_TOUT1_P02_1_OUT IfxGtm_ATOM0_1_TOUT31_P33_9_OUT IfxGtm_ATOM0_1_TOUT47_P22_0_OUT IfxGtm_ATOM0_1_TOUT54_P21_3_OUT IfxGtm_ATOM0_1_TOUT84_P14_4_OUT
 *  Channel2:IfxGtm_ATOM0_2_TOUT104_P10_2_OUT IfxGtm_ATOM0_2_TOUT107_P10_5_OUT IfxGtm_ATOM0_2_TOUT12_P00_3_OUT IfxGtm_ATOM0_2_TOUT2_P02_2_OUT IfxGtm_ATOM0_2_TOUT33_P33_11_OUT IfxGtm_ATOM0_2_TOUT46_P23_5_OUT IfxGtm_ATOM0_2_TOUT55_P21_4_OUT IfxGtm_ATOM0_2_TOUT83_P14_3_OUT
 *  Channel3:IfxGtm_ATOM0_3_TOUT105_P10_3_OUT IfxGtm_ATOM0_3_TOUT108_P10_6_OUT IfxGtm_ATOM0_3_TOUT13_P00_4_OUT IfxGtm_ATOM0_3_TOUT38_P32_2_OUT IfxGtm_ATOM0_3_TOUT3_P02_3_OUT IfxGtm_ATOM0_3_TOUT49_P22_2_OUT IfxGtm_ATOM0_3_TOUT56_P21_5_OUT IfxGtm_ATOM0_3_TOUT60_P20_1_OUT IfxGtm_ATOM0_3_TOUT82_P14_2_OUT
 *  Channel4:IfxGtm_ATOM0_3_TOUT82_P14_2_OUT IfxGtm_ATOM0_4_TOUT14_P00_5_OUT IfxGtm_ATOM0_4_TOUT39_P32_3_OUT IfxGtm_ATOM0_4_TOUT4_P02_4_OUT IfxGtm_ATOM0_4_TOUT50_P22_3_OUT IfxGtm_ATOM0_4_TOUT57_P21_6_OUT IfxGtm_ATOM0_4_TOUT61_P20_3_OUT IfxGtm_ATOM0_4_TOUT81_P14_1_OUT
 *  Channel5:IfxGtm_ATOM0_5_TOUT110_P10_8_OUT IfxGtm_ATOM0_5_TOUT15_P00_6_OUT IfxGtm_ATOM0_5_TOUT23_P33_1_OUT IfxGtm_ATOM0_5_TOUT40_P32_4_OUT IfxGtm_ATOM0_5_TOUT41_P23_0_OUT IfxGtm_ATOM0_5_TOUT58_P21_7_OUT IfxGtm_ATOM0_5_TOUT5_P02_5_OUT
 *  Channel6:IfxGtm_ATOM0_6_TOUT106_P10_4_OUT IfxGtm_ATOM0_6_TOUT16_P00_7_OUT IfxGtm_ATOM0_6_TOUT24_P33_2_OUT IfxGtm_ATOM0_6_TOUT42_P23_1_OUT IfxGtm_ATOM0_6_TOUT59_P20_0_OUT IfxGtm_ATOM0_6_TOUT6_P02_6_OUT
 *  Channel7:IfxGtm_ATOM0_7_TOUT17_P00_8_OUT IfxGtm_ATOM0_7_TOUT25_P33_3_OUT IfxGtm_ATOM0_7_TOUT45_P23_4_OUT IfxGtm_ATOM0_7_TOUT64_P20_8_OUT IfxGtm_ATOM0_7_TOUT7_P02_7_OUT
 *  ATOM1:
 *  Channel0:IfxGtm_ATOM1_0_TOUT0_P02_0_OUT IfxGtm_ATOM1_0_TOUT109_P10_7_OUT IfxGtm_ATOM1_0_TOUT48_P22_1_OUT IfxGtm_ATOM1_0_TOUT53_P21_2_OUT IfxGtm_ATOM1_0_TOUT68_P20_12_OUT IfxGtm_ATOM1_0_TOUT76_P15_5_OUT IfxGtm_ATOM1_0_TOUT77_P15_6_OUT IfxGtm_ATOM1_0_TOUT87_P14_7_OUT IfxGtm_ATOM1_0_TOUT8_P02_8_OUT IfxGtm_ATOM1_0_TOUT9_P00_0_OUT
 *  Channel1:...
 *  Channel2:...
 *  Channel3:...
 *  Channel4:...
 *  Channel5:...
 *  Channel6:...
 *  Channel7:...
 *  ATOM2:
 *  Channel0:...
 *  Channel1:...
 *  Channel2:...
 *  Channel3:...
 *  Channel4:...
 *  Channel5:...
 *  Channel6:...
 *  Channel7:...
 *  ATOM3:
 *  Channel0:...
 *  Channel1:...
 *  Channel2:...
 *  Channel3:...
 *  Channel4:...
 *  Channel5:...
 *  Channel6:...
 *  Channel7:...
 *
 *  pwm通道选用原则：不可重复使用同一atom模组同一通道，不可复用引脚
 * */

Ifx_GTM *gtm = &MODULE_GTM;


//直接路由引脚作为输出
void GTM_Pwm_Init()
{
    float32 frequency = IfxGtm_Cmu_getModuleFrequency(gtm);
    // Enables the GTM
    IfxGtm_enable(gtm);
    // Set the global clock frequency to the max
    IfxGtm_Cmu_setGclkFrequency(gtm, frequency);
    // Set the CMU CLK0
    IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, frequency);
    // FXCLK: used by TOM and CLK0: used by ATOM
    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_CLK0);

    // initialise ATOM
    IfxGtm_Atom_Pwm_Config atomConfig;   //configuration structure
    IfxGtm_Atom_Pwm_Driver atomHandle;   // handle

    IfxGtm_Atom_Pwm_initConfig(&atomConfig, gtm);
    atomConfig.atom = IfxGtm_Atom_0;
    atomConfig.atomChannel  = IfxGtm_Tom_Ch_0;
    atomConfig.period                   = 20;
    atomConfig.dutyCycle              = 5;
//    atomConfig.interrupt.ccu0Enabled = TRUE;
//    atomConfig.interrupt.isrPriority = ATOM0_CH0_PRIO;
    atomConfig.pin.outputPin = &IfxGtm_ATOM0_0_TOUT0_P02_0_OUT;
    atomConfig.synchronousUpdateEnabled = TRUE;

    IfxGtm_Atom_Pwm_init(&atomHandle, &atomConfig);
    //IfxGtm_Atom_Pwm_start(&atomHandle, TRUE);
}


void SmartCar_Gtm_Pwm_Init(IfxGtm_Atom_ToutMap* pwm_channel, uint32 freq, uint32 duty)
{
    IfxGtm_Atom_Pwm_Config atomConfig;
    IfxGtm_Atom_Pwm_Driver atomDriver;
    switch(pwm_channel->atom)
    {
        case 0:
            IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <=GTM ATOM0_DUTY_MAX);
            break;
        case 1:
            IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <=GTM ATOM1_DUTY_MAX);
            break;
        case 2:
            IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <=GTM ATOM2_DUTY_MAX);
            break;
        case 3:
            IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <=GTM ATOM3_DUTY_MAX);
            break;
    }
    IfxGtm_enable(&MODULE_GTM);
    if(!(MODULE_GTM.CMU.CLK_EN.U & 0X2))
    {
        IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CMU_CLK_FREQ);//set clock frequency
        IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);
    }
    IfxGtm_Atom_Pwm_initConfig(&atomConfig, &MODULE_GTM);
    atomConfig.atom = pwm_channel->atom;
    atomConfig.atomChannel = pwm_channel->channel;
    atomConfig.period = CMU_CLK_FREQ/freq;
    atomConfig.pin.outputPin = pwm_channel;//output pin routed
    atomConfig.synchronousUpdateEnabled = TRUE;

    switch(pwm_channel->atom)
    {
        case 0:
            atomConfig.dutyCycle = (uint32)((uint64)duty * atomConfig.period / ATOM0_DUTY_MAX);
            break;
        case 1:
            atomConfig.dutyCycle = (uint32)((uint64)duty * atomConfig.period / ATOM1_DUTY_MAX);
            break;
        case 2:
            atomConfig.dutyCycle = (uint32)((uint64)duty * atomConfig.period / ATOM2_DUTY_MAX);
            break;
        case 3:
            atomConfig.dutyCycle = (uint32)((uint64)duty * atomConfig.period / ATOM3_DUTY_MAX);
            break;
    }
    IfxGtm_Atom_Pwm_init(&atomDriver, &atomConfig);
    IfxGtm_Atom_Pwm_start(&atomDriver, TRUE);
}



void SmartCar_Gtm_Pwm_Setduty(IfxGtm_Atom_ToutMap* pwm_channel, uint32 duty)
{
    uint32 period;
    period = IfxGtm_Atom_Ch_getCompareZero(&MODULE_GTM.ATOM[pwm_channel->atom], pwm_channel->channel);
    switch(pwm_channel->atom)
    {
        case 0:
            duty = (uint32)((uint64)duty * period / ATOM0_DUTY_MAX);
            break;
        case 1:
            duty = (uint32)((uint64)duty * period / ATOM1_DUTY_MAX);
            break;
        case 2:
            duty = (uint32)((uint64)duty * period / ATOM2_DUTY_MAX);
            break;
        case 3:
            duty = (uint32)((uint64)duty * period / ATOM3_DUTY_MAX);
            break;
    }
    IfxGtm_Atom_Ch_setCompareOneShadow(&MODULE_GTM.ATOM[pwm_channel->atom], pwm_channel->channel, duty);
}
