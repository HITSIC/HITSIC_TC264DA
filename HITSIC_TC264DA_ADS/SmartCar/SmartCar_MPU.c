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
 * @note：MPU使用

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#include "SmartCar_MPU.h"
//#include <IfxI2c_I2c.h>

IfxI2c_I2c_Device i2cdev_handle;

uint8 WHO;
/*simple usage*/
void SmartCar_MPU_SelfCheck(void)
{
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, PWR_MGMT_1,0x00);
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);
    while(0x07 != SmartCar_SoftI2c_Readreg(MPU6050_DEV_ADDR, SMPLRT_DIV));
    {
        //卡在这里原因有以下几点
        //1 MPU6050坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
        //4 可能没有调用模拟IIC的初始化函数
    }
}

void SmartCar_MPU_Init1(void)
{
    SmartCar_SoftI2c_PinInit();
    SmartCar_MPU_SelfCheck();
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);   //解除休眠状态
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);   //125HZ采样率
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, MPU6050_CONFIG, 0x04);       //
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);  //2000
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10); //8g
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, USR_CONTROL, 0x00);//关闭6050对辅助I2C设备的控制
    SmartCar_SoftI2c_Writereg(MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
}

void SmartCar_MPU_Getacc1(mpu_t* my_mpu)
{
    uint8 data[6];
    SmartCar_SoftI2c_Readregs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, data, 6);
    my_mpu->mpu_rawdata.acc_x = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[0]<<8) | data[1]);
    my_mpu->mpu_rawdata.acc_y = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[2]<<8) | data[3]);
    my_mpu->mpu_rawdata.acc_z = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[4]<<8) | data[5]);
}
void SmartCar_MPU_Getgyro1(mpu_t* my_mpu)
{
    uint8 data[6];
    SmartCar_SoftI2c_Readregs(MPU6050_DEV_ADDR, GYRO_XOUT_H, data, 6);
    my_mpu->mpu_rawdata.gyro_x = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[0]<<8) | data[1]);
    my_mpu->mpu_rawdata.gyro_y = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[2]<<8) | data[3]);
    my_mpu->mpu_rawdata.gyro_z = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[4]<<8) | data[5]);
}

void SmartCar_MPU_Gettemp1(mpu_t* my_mpu)
{
    uint8 data[2];
    SmartCar_SoftI2c_Readregs(MPU6050_DEV_ADDR, TEMP_OUT_H, data, 2);
    my_mpu->temp = (short int)(((short int)data[0]<<8 | data[1]));
}


void SmartCar_MPU_PinInit(void)
{
    //SmartCar_SoftI2c_PinInit();
    SmartCar_HardwareI2c_Init(IfxI2c0_SCL_P02_5_INOUT, IfxI2c0_SDA_P02_4_INOUT, 400*1000);
}

void SmartCar_MPU_Set_DefaultConfig(mpu_t* my_mpu)
{
    memset(my_mpu, 0, sizeof(mpu_t));
    Set_LPF(my_mpu, MPU_ABW_218, MPU_GBW_176);
    Set_FS(my_mpu, MPU_FS_4G, MPU_FS_2000DPS);
}

uint8 SmartCar_MPU_Init2(mpu_t* my_mpu)
{
    SmartCar_MPU_PinInit();
    uint8 who_am_i = 0xff;
    WHO = 0xff;
    uint8 slave_addr = MPU6050_DEV_ADDR;
    while(TRUE)
    {
        uint8 time = 50;
        SmartCar_MPU_Readregs(slave_addr, WHO_AM_I, &who_am_i, 1);
        if(MPU6050 == who_am_i)
        {
            my_mpu->mpu_config.mpu_model = MPU6050;
            break;
        }
        else if(MPU9250 == who_am_i)
        {
            my_mpu->mpu_config.mpu_model = MPU9250;
            break;
        }
        else if(ICM20602 == who_am_i)
        {
            my_mpu->mpu_config.mpu_model = ICM20602;
            break;
        }
        else
        {
            slave_addr = slave_addr ^ 0x01;//反转陀螺仪地址最低位(0x69,0x68)
            MPU_Delay_Ms(10);
            time--;
            if(time < 0)
            {
                return -1;
            }
        }
    }
    uint8 vari = 0x80;
    SmartCar_MPU_Writereg(slave_addr, PWR_MGMT_1, &vari);
    do{
        MPU_Delay_Ms(10);
        SmartCar_MPU_Readregs(slave_addr, PWR_MGMT_1, &vari, 1);
    }while(!(0x41 == vari || 0x01 == vari || 0x40 == vari));
    vari = 0x00;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, PWR_MGMT_1, &vari);//使用内部时钟
    vari = 0x00;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, PWR_MGMT_2, &vari);//开启mpu
    vari = my_mpu->mpu_config.gyro_bw;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, MPU6050_CONFIG, &vari);//配置陀螺仪数字滤波器
    vari = my_mpu->mpu_config.acc_bw;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, ACCEL_CONFIG_2, &vari);//加速度计数字滤波器
    vari = my_mpu->mpu_config.sample_div;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, SMPLRT_DIV, &vari);//采样速率 internal_sample_rate/(smplrt_div + 1)
    vari = my_mpu->mpu_config.gyro_fs << 3;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, GYRO_CONFIG, &vari);//设置陀螺仪角速度量程
    vari = my_mpu->mpu_config.acc_fs << 3;
    MPU_Delay_Ms(10);
    SmartCar_MPU_Writereg(slave_addr, ACCEL_CONFIG, &vari);//设置陀螺仪加速度量程
    MPU_Delay_Ms(10);
    my_mpu->if_init = 1;
    return 0;
}

void Set_LPF(mpu_t* my_mpu, enum mpu_accel_fs abw, enum mpu_gyro_fs gbw)
{
    my_mpu->mpu_config.acc_bw = abw;
    my_mpu->mpu_config.gyro_bw = gbw;
}

void Set_FS(mpu_t* my_mpu, enum mpu_accel_fs afs, enum mpu_gyro_fs gfs)
{
    my_mpu->mpu_config.acc_fs = afs;
    my_mpu->mpu_config.gyro_fs = gfs;
    switch(my_mpu->mpu_config.acc_fs)
    {
        case (uint8)MPU_FS_2G:
            my_mpu->mpu_config.acc_inv = 2.0 * 9.8 / 32768.0;
            break;
        case (uint8)MPU_FS_4G:
            my_mpu->mpu_config.acc_inv = 4.0 * 9.8 / 32768.0;
            break;
        case (uint8)MPU_FS_8G:
            my_mpu->mpu_config.acc_inv = 8.0 * 9.8 / 32768.0;
            break;
        case (uint8)MPU_FS_16G:
            my_mpu->mpu_config.acc_inv = 16.0 * 9.8 / 32768.0;
            break;
        default:
            my_mpu->mpu_config.acc_inv = 2.0 * 9.8 / 32768.0;
            break;
    }
    switch(my_mpu->mpu_config.gyro_fs)
    {
        case (uint8)MPU_FS_250DPS:
            my_mpu->mpu_config.gyro_inv = 250.0/32768.0;
            break;
        case (uint8)MPU_FS_500DPS:
            my_mpu->mpu_config.gyro_inv = 500.0/32768.0;
            break;
        case (uint8)MPU_FS_1000DPS:
            my_mpu->mpu_config.gyro_inv = 1000.0/32768.0;
            break;
        case (uint8)MPU_FS_2000DPS:
            my_mpu->mpu_config.gyro_inv = 2000.0/32768.0;
            break;
        default:
            my_mpu->mpu_config.gyro_inv = 2000.0/32768.0;
            break;
    }
}

void MPU_Delay_Ms(uint32 ms)
{
    while (--ms)
    {
        uint32 x = 2501;
        while (--x)
        {

        }
    }
}

void SmartCar_AccOffset(mpu_t* my_mpu)
{
    uint8 data[6];
    float acc_xtotal,acc_ytotal,acc_ztotal;
    if(my_mpu->if_init == 0)
    {
        return ;
    }
    //my_mpu->offset_data.acc_x = 0;
    //my_mpu->offset_data.acc_y = 0;
    //my_mpu->offset_data.acc_z = 0;
    for(int i = 0;i<1000;i++)
    {
        SmartCar_MPU_Readregs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, data, 6);
        MPU_Delay_Ms(5);
        my_mpu->mpu_rawdata.acc_x = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[0]<<8) | data[1]);
        my_mpu->mpu_rawdata.acc_y = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[2]<<8) | data[3]);
        my_mpu->mpu_rawdata.acc_z = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[4]<<8) | data[5]);
        acc_xtotal += my_mpu->mpu_rawdata.acc_x;
        acc_ytotal += my_mpu->mpu_rawdata.acc_y;
        acc_ztotal += my_mpu->mpu_rawdata.acc_z;
    }
    my_mpu->offset_data.acc_x = acc_xtotal/1000.0;
    my_mpu->offset_data.acc_y = acc_ytotal/1000.0;
    my_mpu->offset_data.acc_z = acc_ztotal/1000.0;
}

void SmartCar_GyroOffset(mpu_t* my_mpu)
{
    uint8 data[6];
    float gyro_xtotal,gyro_ytotal,gyro_ztotal;
    if(my_mpu->if_init == 0)
    {
        return ;
    }
    for(int i = 0;i<1000;i++)
    {
        SmartCar_MPU_Readregs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, data, 6);
        MPU_Delay_Ms(5);
        my_mpu->mpu_rawdata.gyro_x = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[0]<<8) | data[1]);
        my_mpu->mpu_rawdata.gyro_y = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[2]<<8) | data[3]);
        my_mpu->mpu_rawdata.gyro_z = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[4]<<8) | data[5]);
        gyro_xtotal += my_mpu->mpu_rawdata.gyro_x;
        gyro_ytotal += my_mpu->mpu_rawdata.gyro_y;
        gyro_ztotal += my_mpu->mpu_rawdata.gyro_z;
    }
    my_mpu->offset_data.gyro_x = gyro_xtotal/1000.0;
    my_mpu->offset_data.gyro_y = gyro_ytotal/1000.0;
    my_mpu->offset_data.gyro_z = gyro_ztotal/1000.0;
}

void SmartCar_MPU_Getacc2(mpu_t* my_mpu)
{
    uint8 data[6];
    SmartCar_MPU_Readregs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, data, 6);
    my_mpu->mpu_rawdata.acc_x = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[0]<<8) | data[1]) - my_mpu->offset_data.acc_x;
    my_mpu->mpu_rawdata.acc_y = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[2]<<8) | data[3]) - my_mpu->offset_data.acc_y;
    my_mpu->mpu_rawdata.acc_z = my_mpu->mpu_config.acc_inv * (short int)(((short int)data[4]<<8) | data[5]) - my_mpu->offset_data.acc_z;
}

void SmartCar_MPU_Getgyro2(mpu_t* my_mpu)
{
    uint8 data[6];
    SmartCar_MPU_Readregs(MPU6050_DEV_ADDR, GYRO_XOUT_H, data, 6);
    my_mpu->mpu_rawdata.gyro_x = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[0]<<8) | data[1]) - my_mpu->offset_data.gyro_x;
    my_mpu->mpu_rawdata.gyro_y = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[2]<<8) | data[3]) - my_mpu->offset_data.gyro_y;
    my_mpu->mpu_rawdata.gyro_z = my_mpu->mpu_config.gyro_inv * (short int)(((short int)data[4]<<8) | data[5]) - my_mpu->offset_data.gyro_z;
}

void SmartCar_MPU_Gettemp2(mpu_t* my_mpu)
{
    uint8 data[2];
    SmartCar_MPU_Readregs(MPU6050_DEV_ADDR, TEMP_OUT_H, data, 2);
    my_mpu->temp = (short int)(((short int)data[0]<<8 | data[1]));
}

void SmartCar_MPU_Writereg(uint8 device_addr, uint8 reg_addr, uint8* data_addr)
{
    //SmartCar_SoftI2c_Writereg(device_addr, reg_addr, *data_addr);
    SmartCar_HardwareI2c_Writereg(reg_addr, data_addr, 1);
}

void SmartCar_MPU_Readregs(uint8 device_addr, uint8 reg_addr, uint8* data_addr, uint8 data_num)
{
    //SmartCar_SoftI2c_Readregs(device_addr, reg_addr, data_addr, data_num);
    i2cdev_handle.deviceAddress = device_addr << 1;
    SmartCar_HardwareI2c_Readreg(reg_addr, data_addr,data_num);
}
