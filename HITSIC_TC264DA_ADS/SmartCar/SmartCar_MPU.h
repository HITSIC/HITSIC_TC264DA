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



#ifndef SMARTCAR_MPU_H
#define SMARTCAR_MPU_H

#include "SmartCar_Hardware_IIC.h"
#include "SmartCar_Soft_IIC.h"
#include "string.h"



#define MPU6050_DEV_ADDR        0x68
#define MPU9250_DEV_ADDR        0x68
#define ICM20602_DEV_ADDR       0x69//SA0接地:0x68,SA0上拉0x69
// MPU6050内部地址
#define XG_OFFS_TC_H            0x04
#define XG_OFFS_TC_L            0x05
#define YG_OFFS_TC_H            0x07
#define YG_OFFS_TC_L            0x08
#define ZG_OFFS_TC_H            0x0A
#define ZG_OFFS_TC_L            0x0B
#define SELF_TEST_X_ACCEL       0x0D
#define SELF_TEST_Y_ACCEL       0x0E
#define SELF_TEST_Z_ACCEL       0x0F
#define XG_OFFS_USRH            0x13
#define XG_OFFS_USRL            0x14
#define YG_OFFS_USRH            0x15
#define YG_OFFS_USRL            0x16
#define ZG_OFFS_USRH            0x17
#define ZG_OFFS_USRL            0x18
#define SMPLRT_DIV              0x19    //陀螺仪采样率，典型值：0x07(125Hz)
#define MPU6050_CONFIG          0x1A    //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG             0x1B    //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG            0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_CONFIG_2          0x1D
#define LP_MODE_CFG             0x1E
#define ACCEL_WOM_X_THR         0x20
#define ACCEL_WOM_Y_THR         0x21
#define ACCEL_WOM_Z_THR         0x22
#define FIFO_EN                 0x23
#define FSYNC_INT               0x36
#define INT_PIN_CFG             0x37    //设置6050辅助I2C为直通模式寄存器
#define INT_ENABLE              0x38
#define FIFO_WM_INT_STATUS      0x39
#define INT_STATUS              0x3A
#define ACCEL_XOUT_H            0x3B
#define ACCEL_XOUT_L            0x3C
#define ACCEL_YOUT_H            0x3D
#define ACCEL_YOUT_L            0x3E
#define ACCEL_ZOUT_H            0x3F
#define ACCEL_ZOUT_L            0x40
#define TEMP_OUT_H              0x41
#define TEMP_OUT_L              0x42
#define GYRO_XOUT_H             0x43
#define GYRO_XOUT_L             0x44
#define GYRO_YOUT_H             0x45
#define GYRO_YOUT_L             0x46
#define GYRO_ZOUT_H             0x47
#define GYRO_ZOUT_L             0x48
#define SELF_TEST_X_GYRO        0x50
#define SELF_TEST_Y_GYRO        0x51
#define SELF_TEST_Z_GYRO        0x52
#define FIFO_WM_TH1             0x60
#define FIFO_WM_TH2             0x61
#define SIGNAL_PATH_RESET       0x68
#define ACCEL_INTEL_CTRL        0x69
#define USR_CONTROL             0x6A    //关闭6050对辅助I2C设备的控制
#define PWR_MGMT_1              0x6B    //电源管理，典型值：0x00(正常启用)
#define PWR_MGMT_2              0x6C
#define I2C_IF                  0x70
#define FIFO_COUNTH             0x72
#define FIFO_COUNTL             0x73
#define FIFO_R_W                0x74
#define WHO_AM_I                0x75    //IIC地址寄存器(默认数值0x68，只读)
#define XA_OFFSET_H             0x77
#define XA_OFFSET_L             0x78
#define YA_OFFSET_H             0x7A
#define YA_OFFSET_L             0x7B
#define ZA_OFFSET_H             0x7D
#define ZA_OFFSET_L             0x7E

typedef enum mpu_whoami{
    ICM20602 = 0X12,
    MPU6050 = 0x68,
    MPU9250 = 0x71,
}mpu_whoami_t;
typedef struct mpu{
        struct config{
                mpu_whoami_t mpu_model;
                uint8 gyro_fs;
                uint8 acc_fs;
                uint8 gyro_bw;
                uint8 acc_bw;
                float gyro_inv;
                float acc_inv;
                uint8 sample_div;
        }mpu_config;

        struct mpu_rawdata_t{//原始数据
                float acc_x;
                float acc_y;
                float acc_z;
                float gyro_x;
                float gyro_y;
                float gyro_z;
        }mpu_rawdata;
        struct convert_data_t{//转换后数据，供用户调用
                volatile float x;
                volatile float y;
                volatile float z;
        }acc,gyro;
        struct offset_data_t{//offset data
                float acc_x;
                float acc_y;
                float acc_z;
                float gyro_x;
                float gyro_y;
                float gyro_z;
        }offset_data;
        volatile float temp;//温度
        const char* name;//mpu型号
        uint8 if_init;//初始化标志
}mpu_t;


enum mpu_accel_fs{  //in ACCEL_CONFIG(0X1C),full scale
    MPU_FS_2G = 0,  //2G
    MPU_FS_4G,      //4G
    MPU_FS_8G,      //8G
    MPU_FS_16G,     //16G
    NUM_MPU_AFS
};
enum mpu_accel_ois_fs{  //in ACCEL_CONFIG(0X1C),accel ois full scale
    MPU_OIS_FS_2G = 0,  //2G
    MPU_OIS_FS_4G,      //4G
    MPU_OIS_FS_8G,      //8G
    MPU_OIS_FS_16G,     //16G
    NUM_MPU_OIS_AFS
};

enum mpu_accel_bw{  //in ACCEL_CONFIG2(0X1D) ,BW settting
  MPU_ABW_218 = 1,   //218H
  MPU_ABW_99,        //99Hz
  MPU_ABW_45,        //45Hz
  MPU_ABW_21,        //21Hz
  MPU_ABW_10,        //10Hz
  MPU_ABW_5,         //5Hz
  MPU_ABW_420,       //420Hz
  NUM_MPU_ABW
};

enum mpu_gyro_fs{   //in GYRO_COFIG,full scale
    MPU_FS_250DPS = 0,  //250
    MPU_FS_500DPS,      //500
    MPU_FS_1000DPS,     //1000
    MPU_FS_2000DPS,     //2000
    NUM_MPU_GFS
};

enum mpu_gyro_bw{   //in CONFIG,BW setting
    MPU_GBW_250 = 0,//250Hz
    MPU_GBW_176,    //176Hz
    MPU_GBW_92,     //92Hz
    MPU_GBW_41,     //41Hz
    MPU_GBW_20,     //20Hz
    MPU_GBW_10,     //10Hz
    MPU_GBW_5,      //5Hz
    NUM_MPU_GBW
};

/*
 * brief 陀螺仪自检，软件iic，移植自逐飞库
 * */
void SmartCar_MPU_SelfCheck(void);

/*
 * brief 陀螺仪初始化，软件iic，移植自逐飞库
 * */
void SmartCar_MPU_Init1(void);

/*
 * brief 获得陀螺仪加速度，软件iic，移植自逐飞库
 * */
void SmartCar_MPU_Getacc1(mpu_t* my_mpu);

/*
 * brief 获得陀螺仪角加速度，软件iic，移植自逐飞库
 * */
void SmartCar_MPU_Getgyro1(mpu_t* my_mpu);

/*
 * brief 获得陀螺仪温度，软件iic，移植自逐飞库
 * */
void SmartCar_MPU_Gettemp1(mpu_t* my_mpu);

/*
 * brief 为结构体mpu_t设置默认值
 * */
void SmartCar_MPU_Set_DefaultConfig(mpu_t* my_mpu);

/*
 * brief 陀螺仪使用引脚初始化，分别为初始化为port口，或者硬件iic功能
 * */
void SmartCar_MPU_PinInit(void);

/*
 * brief 陀螺仪初始化，硬件iic
 * */
uint8 SmartCar_MPU_Init2(mpu_t* my_mpu);

/*
 * brief 设置陀螺仪低通滤波器带宽
 * */
void Set_LPF(mpu_t* my_mpu, enum mpu_accel_fs abw, enum mpu_gyro_fs gbw);

/*
 * brief 设置陀螺仪量程
 * */
void Set_FS(mpu_t* my_mpu, enum mpu_accel_fs afs, enum mpu_gyro_fs gfs);

/*
 * brief 陀螺仪专用延时
 * */
void MPU_Delay_Ms(uint32 ms);

/*
 * brief 加速度零漂
 * */
void SmartCar_AccOffset(mpu_t* my_mpu);

/*
 * brief 角加速度零漂
 * */
void SmartCar_GyroOffset(mpu_t* my_mpu);

/*
 * brief  获得陀螺仪加速度，硬件iic
 * */
void SmartCar_MPU_Getacc2(mpu_t* my_mpu);

/*
 * brief 获得陀螺仪角加速度，硬件iic
 * */
void SmartCar_MPU_Getgyro2(mpu_t* my_mpu);

/*
 * brief 获得陀螺仪温度，硬件iic
 * */
void SmartCar_MPU_Gettemp2(mpu_t* my_mpu);

/*
 * brief 向陀螺仪寄存器写数据，陀螺仪专用
 * */
void SmartCar_MPU_Writereg(uint8 device_addr, uint8 reg_addr, uint8* data_addr);

/*
 * brief 从陀螺仪寄存器读数据，陀螺仪专用
 * */
void SmartCar_MPU_Readregs(uint8 device_addr, uint8 reg_addr, uint8* data_addr, uint8 data_num);

#endif
