/*
 * SmartCar_GPIO.h
 *
 *  Created on: 2021��1��22��
 *      Author: ��Ψ
 */

#ifndef SMARTCAR_SMARTCAR_GPIO_H_
#define SMARTCAR_SMARTCAR_GPIO_H_

#include "IFXPORT.h"

//Port object
#define  P00        &MODULE_P00
#define  P02        &MODULE_P02
#define  P10        &MODULE_P10
#define  P11        &MODULE_P11
#define  P13        &MODULE_P13
#define  P14        &MODULE_P14
#define  P15        &MODULE_P15
#define  P20        &MODULE_P20
#define  P21        &MODULE_P21
#define  P22        &MODULE_P22
#define  P23        &MODULE_P23
#define  P33        &MODULE_P33


// ������ѡ��
typedef enum
{
    NO_PULL   ,     //������������
    PULLDOWN  ,     //��������
    PULLUP    ,     //��������
    PUSHPULL  ,     //�������
    OPENDRAIN ,     //��©���
}GPIOMODE_enum;


#define GET_PORT_IN_ADDR(pin)   (uint8 *)(&IfxPort_getAddress((IfxPort_Index)(pin/32))->IN + pin%32/8)

//------------------------------------------------------
//ͨ��GPIO����
//-------------------------------------------------------------------------------------------------------------------



//  @brief      GPIO��ʼ��
//  @param      port        ѡ��Ķ˿ڣ�����SmartCar_GPIO.h��Port object�ĺ궨��
//  @param      pinIndex    ���ź�
//  @param      pinmode     �������ã������ò�����GPIOMODE_enumö��ֵȷ����
//  @param      dat         ���ų�ʼ��ʱ���õĵ�ƽ״̬�����ʱ��Ч ��0���͵�ƽ 1���ߵ�ƽ
//  @return     void
//  Sample usage:           GPIO_Init(P20,9, PUSHPULL,0);//P20_9��ʼ��ΪGPIO���ܡ�����������͵�ƽ
//  @note                   ��Ҫ�ر�ע��P20_2�ǲ�����������ģ�����ֻ������Ĺ���
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Init(Ifx_P *port, uint8 pinIndex,GPIOMODE_enum pinmode,uint8 dat);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO�������
//  @param      port        ѡ��Ķ˿ڣ�����SmartCar_GPIO.h��Port object�ĺ궨��
//  @param      pinIndex    ���ź�
//  @param      dat         0���͵�ƽ 1���ߵ�ƽ
//  @return     void
//  Sample usage:           GPIO_Set(P20,9, 1);//P20_9 ����ߵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Set(Ifx_P *port, uint8 pinIndex, uint8 dat);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO״̬��ȡ
//  @param      port        ѡ��Ķ˿ڣ�����SmartCar_GPIO.h��Port object�ĺ궨��
//  @param      pinIndex    ���ź�
//  @return     uint8       0���͵�ƽ 1���ߵ�ƽ
//  Sample usage:           uint8 status = GPIO_Read(P20,9);//��ȡP20_9���ŵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
uint8 GPIO_Read(Ifx_P *port, uint8 pinIndex);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO ��ת
//  @param      port        ѡ��Ķ˿ڣ�����SmartCar_GPIO.h��Port object�ĺ궨��
//  @param      pinIndex    ���ź�
//  @return     void
//  Sample usage:           GPIO_Toggle(P20,9);//P20_9���ŵ�ƽ��ת
//-------------------------------------------------------------------------------------------------------------------
void GPIO_Toggle(Ifx_P *port, uint8 pinIndex);






#endif /* SMARTCAR_SMARTCAR_GPIO_H_ */
