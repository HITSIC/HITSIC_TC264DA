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



#include "SmartCar_Hardware_IIC.h"


/*
 *      check in file Libraries/iLLD/TC26B/Tricore/_PinMap/IfxI2c_PinMap.c
 *      scl_pin:
 *      IfxI2c0_SCL_P02_5_INOUT
 *      IfxI2c0_SCL_P13_1_INOUT
 *      IfxI2c0_SCL_P15_4_INOUT
 *      sda_pin:
 *      IfxI2c0_SDA_P02_4_INOUT
 *      IfxI2c0_SDA_P13_2_INOUT
 *      IfxI2c0_SDA_P15_5_INOUT
*/

static IfxI2c_I2c i2c_handle;
static IfxI2c_I2c_Device i2cdev_handle;
uint8 data[64];

void SmartCar_HardwareI2c_Init(IfxI2c_Scl_InOut scl_pin, IfxI2c_Sda_InOut sda_pin, float32 baudrate)
{
    IfxI2c_I2c_Config i2c_config;
    IfxI2c_I2c_initConfig(&i2c_config, &MODULE_I2C0);
    //configure pins
    const IfxI2c_Pins i2c_pin = {
            &scl_pin,
            &sda_pin,
            IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    i2c_config.pins = &i2c_pin;
    i2c_config.baudrate = baudrate;
    //initialize module
    IfxI2c_I2c_initModule(&i2c_handle, &i2c_config);

    //initialize device
    //create device config
    IfxI2c_I2c_deviceConfig i2cdevice_config;
    IfxI2c_I2c_initDeviceConfig(&i2cdevice_config, &i2c_handle);
    //configure the device address
    i2cdevice_config.deviceAddress = 0x68 << 1;
    IfxI2c_I2c_initDevice(&i2cdev_handle, &i2cdevice_config);
    //end initialize
}
void SmartCar_HardwareI2c_Writereg(uint8 reg_addr, uint8* data_addr, uint8 data_num)
{
    data[0] = reg_addr;//high address
    //data[1] = (uint8)reg_addr;//low address
    for(int i = 1;i<data_num + 1;i++)
    {
        data[i] = *(data_addr + i-1);
    }
    //IfxI2c_I2c_write(&i2cdev_handle, data, data_num);
    while(IfxI2c_I2c_write(&i2cdev_handle, data, data_num + 1) == IfxI2c_I2c_Status_nak);
}
void SmartCar_HardwareI2c_Readreg(uint8 reg_addr, uint8* data_addr, uint8 data_num)
{
    data[0] = reg_addr;//high address
    //data[1] = (uint8)reg_addr;//low address
    //IfxI2c_I2c_write(&i2cdev_handle, data, 1);
    //IfxI2c_I2c_read(&i2cdev_handle,data_addr,data_num);
    while(IfxI2c_I2c_write(&i2cdev_handle, data, 1) == IfxI2c_I2c_Status_nak);
    while(IfxI2c_I2c_read(&i2cdev_handle,data_addr,data_num) == IfxI2c_I2c_Status_nak);
}
