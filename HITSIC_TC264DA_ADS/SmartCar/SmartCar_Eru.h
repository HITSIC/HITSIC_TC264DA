/*
 * SmartCar_eru.h
 *
 *  Created on: 2021��1��22��
 *      Author:��Ψ
 */

#ifndef SMARTCAR_SMARTCAR_ERU_H_
#define SMARTCAR_SMARTCAR_ERU_H_

#include "Src/Std/IfxSrc.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxScuEru.h"

// ö�ٴ�����ʽ
typedef enum
{
    RISING,
    FALLING,
    BOTH,
}TRIGGER_enum;

// ö��ERUͨ��
typedef enum
{
    //һ��ͨ��ֻ��ѡ������һ��������Ϊ �ⲿ�жϵ�����
    //����ͨ��0 ��ѡ����ΪP10_7 �� P15_4��
    CH0_P10_7   = 0*3,  CH0_P15_4,                        //ͨ��0��ѡ����
    CH1_P10_8   = 1*3,  CH1_P14_3,                        //ͨ��1��ѡ����
    CH2_P00_4   = 2*3,  CH2_P02_1,  CH2_P10_2,            //ͨ��2��ѡ����
    CH3_P02_0   = 3*3,  CH3_P10_3,  CH3_P14_1,            //ͨ��3��ѡ����

    //ͨ��4��ͨ��0 �����жϺ��� ���ж���ͨ���жϱ�־λ��ʶ�����ĸ�ͨ���������ж�
    CH4_P15_5  = 4*3,   CH4_P33_7,                        //ͨ��4��ѡ����
    //ͨ��5��ͨ��1 �����жϺ���
    CH5_P15_8  = 5*3,                                     //ͨ��5��ѡ����
    //ͨ��6��ͨ��2 �����жϺ���
    CH6_P11_10 = 6*3,  CH6_P20_0,                         //ͨ��6��ѡ����
    //ͨ��7��ͨ��3 �����жϺ���
    CH7_P15_1  = 7*3,  CH7_P20_9,                         //ͨ��7��ѡ����
}ERU_PIN_enum;

//�ر�ע��ͨ��2 �� ͨ��3��������ͷռ��

//------------GPIO�жϲ�����ض���------------
//ͨ��0��ͨ��4�ǹ���һ���жϺ��� ���ж��ڲ�ͨ����־λ�ж���˭�������ж�
#define ERU_CH0_CH4_INT_SERVICE IfxSrc_Tos_cpu0 //����ERUͨ��0��ͨ��4�жϷ������ͣ����ж�����˭��Ӧ���� 0:CPU0 1:CPU1 3:DMA ��������Ϊ����ֵ
#define ERU_CH0_CH4_INT_PRIO    40              //����ERUͨ��0��ͨ��4�ж����ȼ� ���ȼ���Χ1-255 Խ�����ȼ�Խ�� ��ƽʱʹ�õĵ�Ƭ����һ��

#define ERU_CH1_CH5_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH1_CH5_INT_PRIO    41

#define ERU_CH2_CH6_INT_SERVICE IfxSrc_Tos_dma
#define ERU_CH2_CH6_INT_PRIO    5

#define ERU_CH3_CH7_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH3_CH7_INT_PRIO    43



//�жϱ�־λ��ȡ
#define GET_GPIO_FLAG(eru_pin)      IfxScuEru_getEventFlagStatus((IfxScuEru_InputChannel)(eru_pin/3))
//�жϱ�־λ���
#define CLEAR_GPIO_FLAG(eru_pin)    IfxScuEru_clearEventFlag((IfxScuEru_InputChannel)(eru_pin/3))


//-------------------------------------------------------------------------------------------------------------------
//  @brief      eru��ʼ��(gpio�ж�)
//  @param      eru_pin         ����eruͨ��������
//  @param      trigger         ���ô�����ʽ
//  @return     void
//  Sample usage:               eru_init(ERU_CH0_REQ0_P15_4, RISING);//eruͨ��0 ʹ��P10_7���ţ������ش����ж�
//-------------------------------------------------------------------------------------------------------------------
void Eru_Init(ERU_PIN_enum eru_pin, TRIGGER_enum trigger);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����eru�ж�
//  @param      eru_pin         ����eruͨ��������
//  @return     void
//  Sample usage:               eru_enable_interrupt(ERU_CH0_REQ0_P15_4);
//-------------------------------------------------------------------------------------------------------------------
void Eru_Enable(ERU_PIN_enum eru_pin);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ر�eru�ж�
//  @param      eru_pin         ����eruͨ��������
//  @return     void
//  Sample usage:               eru_disable_interrupt(ERU_CH0_REQ0_P15_4);
//-------------------------------------------------------------------------------------------------------------------
void Eru_Disable(ERU_PIN_enum eru_pin);




#endif /* SMARTCAR_SMARTCAR_ERU_H_ */
