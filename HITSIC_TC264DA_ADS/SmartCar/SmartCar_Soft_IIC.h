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
 * @note：软件iic
 *      SDA:P02_4       SCL:P02_5

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_SOFT_IIC_H
#define SMARTCAR_SOFT_IIC_H

#include <IfxPort_Io.h>

#define IIC_SCL_PIN_MODULE MODULE_P02
#define IIC_SCL_PIN_NUM    5
#define IIC_SDA_PIN_MODULE MODULE_P02
#define IIC_SDA_PIN_NUM    4

#define SIMIIC_DELAY_TIME 20

void SmartCar_SoftI2c_DelaySet(uint16 time);
void SmartCar_SoftI2c_Delay(void);
void SmartCar_SoftI2c_Start(void);
void SmartCar_SoftI2c_Stop(void);
void SmartCar_SoftI2c_Sendack(unsigned char ack_data);
static int SmartCar_Sccb_Waitack(void);
void SmartCar_SoftI2c_Sendch(uint8 ch);
uint8 SmartCar_SoftI2c_Readch(uint8 ack_x);
void SmartCar_SoftI2c_Writereg(uint8 device_addr, uint8 reg_addr, uint8 data);
uint8 SmartCar_SoftI2c_Readreg(uint8 device_addr, uint8 reg_addr);
void SmartCar_SoftI2c_Readregs(uint8 device_addr, uint8 reg_addr, uint8* data_addr, uint8 num);
void SmartCar_SoftI2c_PinInit(void);

#endif
