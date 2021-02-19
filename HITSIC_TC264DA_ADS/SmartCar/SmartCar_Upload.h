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
 * @note����λ�����ݼ�ͼ����

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_UPLOAD_H
#define SMARTCAR_UPLOAD_H

#include "SmartCar_Uart.h"


/*
 * brief uart��������
 * */
void SmartCar_Uart_Upload(uint8* txData, Ifx_SizeT count);

/*
 * brief uart����λ����������
 * para my_var ������������ʼ��ַ
 * para var_num ���ݸ���
 * sample SmartCar_VarUpload(angle_data, 3);
 * */
void SmartCar_VarUpload(float *my_var, uint8 var_num);

/*
 * brief uart����λ������ͼƬ
 * para upload_img ������ͼƬ��ʼ��ַ
 * para row ����
 * para col ����
 * sample SmartCar_VarUpload(&image_buffer[0][0], 120, 188);
 * */
void SmartCar_ImgUpload(uint8 *upload_img, uint8 row, uint8 col);

//��ʱ����ʹ��PRINFT!!!
void PRINFT(const char* ftm, ...);

#endif
