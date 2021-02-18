/*
 * SmartCar_PIT.h
 *
 *  Created on: 2021��1��22��
 *      Author: ��Ψ
 */

#ifndef SMARTCAR_SMARTCAR_PIT_H_
#define SMARTCAR_SMARTCAR_PIT_H_

#include "common.h"
#include "IfxCcu6_Timer.h"
#include "SysSe/Bsp/Bsp.h"
#include "SmartCar_GPIO.h"
//ģ���
typedef enum
{
    CCU6_0,
    CCU6_1,
}CCU6N_enum;

//ͨ����
typedef enum
{
    PIT_CH0,
    PIT_CH1,
}CCU6_CHN_enum;

//------------PIT�жϲ�����ض���------------
#define CCU6_0_CH0_INT_SERVICE  IfxSrc_Tos_cpu0 //����CCU6_0 PITͨ��0�жϷ������ͣ����ж�����˭��Ӧ���� 0:CPU0 1:CPU1 3:DMA  ��������Ϊ����ֵ
#define CCU6_0_CH0_ISR_PRIORITY 30  //����CCU6_0 PITͨ��0�ж����ȼ� ���ȼ���Χ1-255 Խ�����ȼ�Խ�� ��ƽʱʹ�õĵ�Ƭ����һ��

#define CCU6_0_CH1_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_0_CH1_ISR_PRIORITY 31

#define CCU6_1_CH0_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_1_CH0_ISR_PRIORITY 32

#define CCU6_1_CH1_INT_SERVICE  IfxSrc_Tos_cpu0
#define CCU6_1_CH1_ISR_PRIORITY 33


#define PIT_CLEAR_FLAG(ccu6n,pit_ch) IfxCcu6_clearInterruptStatusFlag(IfxCcu6_getAddress((IfxCcu6_Index)ccu6n), (IfxCcu6_InterruptSource)(7+(pit_ch*2)))

//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ��
//  @param      ccu6n           ѡ��CCU6ģ��(CCU6_0��CCU6_1)
//  @param      pit_ch          ѡ��ͨ��(PIT_CH0��PIT_CH1)
//  @param      time            ����ʱ��
//  @return     void
//  @note                       ��ʹ��.h�ļ��� ��ʱ�䵥λ�ĺ궨�庯��
//  Sample usage:               Pit_Init_ms(CCU6_0, PIT_CH0, 5000);    //���������ж�5000ms
//                              Pit_Init_us(CCU6_0, PIT_CH0, 5000);    //���������ж�5000us
//-------------------------------------------------------------------------------------------------------------------
void Pit_Init(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch, uint32 time);

//------------------------------------PIT�ж�ʱ�䵥λ��ѡ------------------------------------
#define Pit_Init_ms(ccu6n, pit_ch, time)  Pit_Init(ccu6n, pit_ch, time*1000)   //(��λΪ ����)
#define Pit_Init_us(ccu6n, pit_ch, time)  Pit_Init(ccu6n, pit_ch, time)        //(��λΪ ΢��)



//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit�ر�
//  @param      ccu6n           ѡ��CCU6ģ��(CCU6_0��CCU6_1)
//  @param      pit_ch          ѡ��ͨ��(PIT_CH0��PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Close(CCU6_0, PIT_CH0); //�ر�CCU60 ͨ��0�ļ�ʱ��
//-------------------------------------------------------------------------------------------------------------------
void Pit_Close(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      pit��ʼ
//  @param      ccu6n           ѡ��CCU6ģ��(CCU6_0��CCU6_1)
//  @param      pit_ch          ѡ��ͨ��(PIT_CH0��PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Start(CCU6_0, PIT_CH0); //��CCU60 ͨ��0�ļ�ʱ��
//-------------------------------------------------------------------------------------------------------------------
void Pit_Start(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ֹpit�ж�
//  @param      ccu6n           ѡ��CCU6ģ��(CCU6_0��CCU6_1)
//  @param      pit_ch          ѡ��ͨ��(PIT_CH0��PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Disable_Interrupt(CCU6_0, PIT_CH0); //��ֹCCU60 ͨ��0���ж�
//-------------------------------------------------------------------------------------------------------------------
void Pit_Disable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ��pit�ж�
//  @param      ccu6n           ѡ��CCU6ģ��(CCU6_0��CCU6_1)
//  @param      pit_ch          ѡ��ͨ��(PIT_CH0��PIT_CH1)
//  @return     void
//  @note
//  Sample usage:               Pit_Enable_Interrupt(CCU6_0, PIT_CH0);  //����CCU60 ͨ��0���ж�
//-------------------------------------------------------------------------------------------------------------------
void Pit_Enable_Interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);







#endif /* SMARTCAR_SMARTCAR_PIT_H_ */
