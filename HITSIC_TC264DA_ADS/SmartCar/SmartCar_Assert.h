/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 *
 * @file            SmartCar_Assert
 * @company         ���������ܳ����¾��ֲ�
 * @author          ���� qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2020-2-05
 *
 * @note��

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#ifndef SMARTCAR_ASSERT_H
#define SMARTCAR_ASSERT_H


#include "Ifx_Types.h"

void assert(pchar __file, unsigned int __line, pchar __function);



#define SMARTCAR_ASSERT(expr)   ((expr) ? ((void)0) : assert(__FILE__, __LINE__, __func__))

#endif
