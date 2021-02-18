/*
 * SmartCar_Systick.h
 *
 *  Created on: 2021��1��25��
 *      Author: ��Ψ
 */

#ifndef SMARTCAR_SMARTCAR_SYSTICK_H_
#define SMARTCAR_SMARTCAR_SYSTICK_H_

#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "common.h"

typedef enum  // ö��STMģ���
{
    STM0,
    STM1,
}STMN_enum;


void Systick_Delay(STMN_enum stmn, uint32 time);
void Systick_Start(STMN_enum stmn);
uint32 Systick_Get(STMN_enum stmn);

//------------------------------------���º궨��������ʱ------------------------------------
#define Delay_ms(stmn, time)    Systick_Delay(stmn, time*1000000)   //������ʱʱ��  ��λms
#define Delay_us(stmn, time)    Systick_Delay(stmn, time*1000)      //������ʱʱ��  ��λus
#define Delay_ns(stmn, time)    Systick_Delay(stmn, time)           //������ʱʱ��  ��λns

//------------------------------------���º궨�����ڻ�ȡ��ǰʱ��------------------------------------
#define GetTime_ms(stmn)        Systick_Get(stmn)/100000            //��ȡ��ǰ��ʱʱ��  ��λms
#define GetTime_us(stmn)        Systick_Get(stmn)/100               //��ȡ��ǰ��ʱʱ��  ��λus
#define GetTime_ns(stmn)        Systick_Get(stmn)*10                //��ȡ��ǰ��ʱʱ��  ��λns




#endif /* SMARTCAR_SMARTCAR_SYSTICK_H_ */
