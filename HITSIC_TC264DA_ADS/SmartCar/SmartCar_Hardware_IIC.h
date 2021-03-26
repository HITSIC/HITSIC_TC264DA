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
 * @note：硬件iic

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_HARDWARE_IIC_H
#define SMARTCAR_HARDWARE_IIC_H

#include <IfxI2c_I2c.h>


/*
 * brief 硬件初始化I2c通信
 * para scl_pin 时钟脚
 * para sda_pin 数据脚
 * para baudrate 波特率
 * sample IIC_Hardware_Init(IfxI2c0_SCL_P02_5_INOUT, IfxI2c0_SDA_P02_4_INOUT, 400000);
 * */
void SmartCar_HardwareI2c_Init(IfxI2c_Scl_InOut scl_pin, IfxI2c_Sda_InOut sda_pin, float32 baudrate);

/*
 * brief 写数据到从设备
 * para reg_addr 从设备寄存器地址
 * para data_addr 数据地址
 * para data_num 数据大小
 * sample SmartCar_HardwareI2c_Writereg(0x75, data_addr, 1);
 * */
uint8 SmartCar_HardwareI2c_Writereg(uint8 reg_addr, uint8* data_addr,uint8 data_num);

/*
 * brief 写数据到从设备
 * para reg_addr 从设备寄存器地址
 * para data_addr 数据地址
 * para data_num 数据大小
 * sample SmartCar_HardwareI2c_Readreg(0x75, data_addr, 1);
 * */
uint8 SmartCar_HardwareI2c_Readreg(uint8 reg_addr, uint8* data_addr,uint8 data_num);

#endif
