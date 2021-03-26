/*
 * SmartCar_Systick.c
 *
 *  Created on: 2021��1��25��
 *      Author: ��Ψ
 */
#include "SmartCar_Systick.h"

static uint32 systick_count[2];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick��ʱ����
//  @param      time            ��Ҫ��ʱ��ʱ��
//  @return     void
//  Sample usage:               ������ã���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
void Systick_Delay(STMN_enum stmn, uint32 time)
{
    uint32 stm_clk;
    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));
    IfxStm_waitTicks(IfxStm_getAddress((IfxStm_Index)stmn), (uint32)((uint64)stm_clk*time/1000000000));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick��ʱ������
//  @param      stmn            ѡ��ʹ�õ�ģ��
//  @return     void
//  Sample usage:               Systick_Start(STM0);//��¼�µ�ǰ��ʱ��
//-------------------------------------------------------------------------------------------------------------------
void Systick_Start(STMN_enum stmn)
{

    systick_count[stmn] = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief     ��õ�ǰSystem tick timer��ֵ
//  @param     stmn             ѡ��ʹ�õ�ģ��
//  @return    uint32           ���شӿ�ʼ�����ڵ�ʱ��(��λ10ns)
//  Sample usage:               uint32 tim = Systick_Get(STM0);
//-------------------------------------------------------------------------------------------------------------------
uint32 Systick_Get(STMN_enum stmn)
{
    uint32 time;
    uint32 stm_clk;

    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));

    time = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn)) - systick_count[stmn];
    time = (uint32)((uint64)time * 100000000 / stm_clk);
    return time;
}


