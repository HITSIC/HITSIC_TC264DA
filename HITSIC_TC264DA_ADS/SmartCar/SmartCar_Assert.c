/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,���������ܳ����¾��ֲ�
 * All rights reserved.
 *
 * @file            SmartCar_Assert
 * @company         ���������ܳ����¾��ֲ�
 * @author          ���� qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note��

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include <SmartCar_Assert.h>
#include "stdio.h"

void assert(pchar __file, unsigned int __line, pchar __function)
{
    //������Դ��� �����ļ�Ŀ¼ �����ļ��� ���ú�������
#if(DEBUG_PRINTF)
    printf("ASSERTION: %s %d %s\n",__file, __line, __function);
#endif
#pragma warning 507
    while(TRUE)
    {
        //�ȴ�����Ա��� ���Դ���

    }
#pragma warning default
}
