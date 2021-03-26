/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            SmartCar_Encoder
 * @company         哈工大智能车创新俱乐部
 * @author          李洋 qq:2367381108
 * @version         v1.0
 * @Software        ADS
 * @Target core     TC264
 * @date            2021-2-05
 *
 * @note：上位机数据及图像发送

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_UPLOAD_H
#define SMARTCAR_UPLOAD_H

#include "SmartCar_Uart.h"


/*
 * brief uart发送数据
 * */
void SmartCar_Uart_Upload(uint8* txData, Ifx_SizeT count);

/*
 * brief uart向上位机发送数据
 * para my_var 待发送数据起始地址
 * para var_num 数据个数
 * sample SmartCar_VarUpload(angle_data, 3);
 * */
void SmartCar_VarUpload(float *my_var, uint8 var_num);

/*
 * brief uart向上位机发送图片
 * para upload_img 待发送图片起始地址
 * para row 行数
 * para col 列数
 * sample SmartCar_VarUpload(&image_buffer[0][0], 120, 188);
 * */
void SmartCar_ImgUpload(uint8 *upload_img, uint8 row, uint8 col);

//暂时请勿使用PRINFT!!!
void PRINFT(const char* ftm, ...);

#endif
