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
 * @note��Ӳ��iic

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_HARDWARE_IIC_H
#define SMARTCAR_HARDWARE_IIC_H

#include <IfxI2c_I2c.h>


/*
 * brief Ӳ����ʼ��I2cͨ��
 * para scl_pin ʱ�ӽ�
 * para sda_pin ���ݽ�
 * para baudrate ������
 * sample IIC_Hardware_Init(IfxI2c0_SCL_P02_5_INOUT, IfxI2c0_SDA_P02_4_INOUT, 400000);
 * */
void SmartCar_HardwareI2c_Init(IfxI2c_Scl_InOut scl_pin, IfxI2c_Sda_InOut sda_pin, float32 baudrate);

/*
 * brief д���ݵ����豸
 * para reg_addr ���豸�Ĵ�����ַ
 * para data_addr ���ݵ�ַ
 * para data_num ���ݴ�С
 * sample SmartCar_HardwareI2c_Writereg(0x75, data_addr, 1);
 * */
uint8 SmartCar_HardwareI2c_Writereg(uint8 reg_addr, uint8* data_addr,uint8 data_num);

/*
 * brief д���ݵ����豸
 * para reg_addr ���豸�Ĵ�����ַ
 * para data_addr ���ݵ�ַ
 * para data_num ���ݴ�С
 * sample SmartCar_HardwareI2c_Readreg(0x75, data_addr, 1);
 * */
uint8 SmartCar_HardwareI2c_Readreg(uint8 reg_addr, uint8* data_addr,uint8 data_num);

#endif
