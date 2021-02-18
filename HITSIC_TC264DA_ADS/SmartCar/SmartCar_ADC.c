/*
 * SmartCar_ADC.c
 *
 *  Created on: 2021年1月22日
 *      Author: 孙唯
 */

#include "SmartCar_ADC.h"


#define ADC_SAMPLE_FREQUENCY    10000000//最大10Mhz


void ADC_Init(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn)
{
    static uint8 mudule_init_flag = 0;
    IfxVadc_Adc vadc;
    IfxVadc_Adc_Group adcGroup;
    IfxVadc_Adc_Config adcConfig;

    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    if(!mudule_init_flag)
    {
        mudule_init_flag = 1;
        IfxVadc_Adc_initModule(&vadc, &adcConfig);
    }
    else
    {
        vadc.vadc = adcConfig.vadc;
    }

    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &vadc);

    adcGroupConfig.groupId = (IfxVadc_GroupId)vadc_n;//IfxVadc_GroupId_0;
    adcGroupConfig.master  = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
    adcGroupConfig.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit;
    adcGroupConfig.inputClass[0].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;
    adcGroupConfig.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit;
    adcGroupConfig.inputClass[1].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;

    IfxVadc_Adc_initGroup(&adcGroup, &adcGroupConfig);

    IfxVadc_Adc_ChannelConfig adcChannelConfig;
    IfxVadc_Adc_Channel       adcChannel;
    IfxVadc_Adc_initChannelConfig(&adcChannelConfig, &adcGroup);

    adcChannelConfig.channelId         = (IfxVadc_ChannelId)(vadc_chn%16);
    adcChannelConfig.resultRegister    = (IfxVadc_ChannelResult)(vadc_chn%16);
    adcChannelConfig.backgroundChannel = TRUE;

    IfxVadc_Adc_initChannel(&adcChannel, &adcChannelConfig);

    unsigned channels = (1 << adcChannelConfig.channelId);
    unsigned mask     = channels;
    IfxVadc_Adc_setBackgroundScan(&vadc, &adcGroup, channels, mask);

    IfxVadc_Adc_startBackgroundScan(&vadc);
}


uint16 ADC_Get(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res)
{
    Ifx_VADC_RES result;
    uint8 temp;
    do
    {
        result = IfxVadc_getResult(&MODULE_VADC.G[vadc_n], vadc_chn%16);
    } while (!result.B.VF);

    temp = 4 - (vadc_res * 2);
    return((result.U&0x0fff)>>temp);
}






