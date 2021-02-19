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
 * @note�����б�������ֵʹ������Ҫ�Լ�ѡ�񣬾���������

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
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
 * brief ��ʼ���������������
 * para gptn ����ʹ�õ�PGT12��������
 * para count_pin ��������
 * para dir_pin �жϷ�������
 * sample SmartCar_Encoder_Init(GPT12_T2, IfxGpt120_T2INA_P00_7_IN, IfxGpt120_T2EUDA_P00_8_IN)
 * */
void SmartCar_Encoder_Init(GPTn_enum gptn, IfxGpt12_TxIn_In count_pin,IfxGpt12_TxEud_In dir_pin);

/*
 * brief ��ñ���������ֵ
 * para gptn ����ʹ�õ�PGT12��������
 * sample SmartCar_Encoder_Get(PGT12_T2);
 * */
int16 SmartCar_Encoder_Get(GPTn_enum gptn);

/*
 * brief �������������ֵ
 * para gtpn ����ʹ�õ�PGT12��������
 * sample SmartCar_Encoder_Clear(GPT12_T2);
 * */
void SmartCar_Encoder_Clear(GPTn_enum gptn);

#endif
