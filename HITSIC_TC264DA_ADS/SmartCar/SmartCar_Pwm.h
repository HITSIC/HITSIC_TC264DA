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
 * @note��PWM�ź����

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_PWM_H
#define SMARTCAR_PWM_H


#include "IfxGtm_Atom_Pwm.h"

#define ATOM0_DUTY_MAX 10000//ռ�ձ����ֵ
#define ATOM1_DUTY_MAX 10000
#define ATOM2_DUTY_MAX 10000
#define ATOM3_DUTY_MAX 10000
#define CMU_CLK_FREQ           20000000.0f//���Ƶ��Ϊ100000000

#define ATOM0_CH0_PRIO 20


/*
 * brief ��ʼ��������Ϊpwm���
 * */
void GTM_Pwm_Init();

/*
 * brief ��ʼ��������Ϊpwm������ţ����趨���ʼƵ�ʼ�ռ�ձ�
 *sample SmartCar_Gtm_Pwm_Init(&IfxGtm_ATOM0_0_TOUT0_P02_0_OUT, 50, 760);//����P02_0�ϵ����pwm�ź�Ƶ��50��ռ�ձ�760/10000
 * */
void SmartCar_Gtm_Pwm_Init(IfxGtm_Atom_ToutMap* pwm_channel, uint32 freq, uint32 duty);

/*brief �����������ռ�ձ�
 * para pwm_channel ����pwm���ʹ������
 * para duty ���ĺ��pwm���ռ�ձ�
 * sample SmartCar_Gtm_Pwm_Setduty(&IfxGtm_ATOM0_0_TOUT0_P02_0_OUT, 760)//��������P02_0��pwmռ�ձ�Ϊ760/10000
 * */
void SmartCar_Gtm_Pwm_Setduty(IfxGtm_Atom_ToutMap* pwm_channel, uint32 duty);


#endif
