/*
 * common.c
 *
 *  Created on: 2021��1��22��
 *      Author: ��Ψ
 */

#include "common.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;//�¼�ͬ������

App_Cpu0 g_AppCpu0; //Ƶ����Ϣ����
void get_clk(void)
{

    //���ÿ��Ź�
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());


    //��ȡʱ��Ƶ�ʣ����ڲ鿴��ǰϵͳ����Ƶ��
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();//���໷
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());//������
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();//ϵͳ
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

}
