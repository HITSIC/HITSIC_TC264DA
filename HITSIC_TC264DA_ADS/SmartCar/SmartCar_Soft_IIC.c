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


#include "SmartCar_Soft_IIC.h"


/*引脚操作定义，方便调用*/
#define SDA_LEVEL          IfxPort_getPinState(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SDA_SET_HIGH()     IfxPort_setPinHigh(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SDA_SET_LOW()      IfxPort_setPinLow(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SCL_SET_HIGH()     IfxPort_setPinHigh(&IIC_SCL_PIN_MODULE,IIC_SCL_PIN_NUM)
#define SCL_SET_LOW()      IfxPort_setPinLow(&IIC_SCL_PIN_MODULE,IIC_SCL_PIN_NUM)
#define DIR_IN()           IfxPort_setPinModeInput(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_InputMode_noPullDevice)
#define DIR_OUT()          IfxPort_setPinMode(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_Mode_outputPushPullGeneral)


uint8 i2c_main;//从器件地址
uint8 i2c_sub;//从器件寄存器地址
uint8* i2c_buf;//发送/接受数据首地址
uint8 i2c_num;//发送接收数据个数

#define ACK 1//主应答
#define NACK 0//从应答

uint16 simi2c_delay_time = SIMIIC_DELAY_TIME;//延时时间

void SmartCar_SoftI2c_DelaySet(uint16 time)
{
    simi2c_delay_time = time;
}

void SmartCar_SoftI2c_Delay(void)
{
    //暂用
    uint16 delay_time;
    delay_time = simi2c_delay_time;
    while(delay_time--){};
    //后续请用systick延时填充
}

//i2c传输开始
void SmartCar_SoftI2c_Start(void)
{
    SDA_SET_HIGH();
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    SDA_SET_LOW();
    SmartCar_SoftI2c_Delay();
    SCL_SET_LOW();
}

//i2c传输停止
void SmartCar_SoftI2c_Stop(void)
{
    SDA_SET_LOW();
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    SDA_SET_HIGH();
    SmartCar_SoftI2c_Delay();
}

//主机向从设备发送应答/非应答信号
void SmartCar_SoftI2c_Sendack(unsigned char ack_data)
{
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
    if(ack_data)
    {
        SDA_SET_LOW();
    }
    else
    {
        SDA_SET_HIGH();
    }
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
}

//主机等待从设备应答信号
static int SmartCar_Sccb_Waitack(void)
{
    SCL_SET_LOW();
    DIR_IN();
    SmartCar_SoftI2c_Delay();
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    if(SDA_LEVEL)//应答高电平，异常，通信失败
    {
        DIR_OUT();
        SCL_SET_LOW();
        return 0;
    }
    DIR_OUT();
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
    return 1;
}

//发送单个字节
void SmartCar_SoftI2c_Sendch(uint8 ch)
{
    uint8 i = 8;
    while(i--)
    {
        if(ch & 0x80) SDA_SET_HIGH();
        else        SDA_SET_LOW();
        ch <<= 1;
        SmartCar_SoftI2c_Delay();

        SCL_SET_HIGH();
        SmartCar_SoftI2c_Delay();
        SCL_SET_LOW();
    }
    SmartCar_Sccb_Waitack();
}

//接受一个字节数据
uint8 SmartCar_SoftI2c_Readch(uint8 ack_x)
{
    uint8 i;
    uint8 c;
    c = 0;
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
    SDA_SET_HIGH();
    DIR_IN();
    for(i = 0;i<8;i++)
    {
        SmartCar_SoftI2c_Delay();
        SCL_SET_LOW();
        SmartCar_SoftI2c_Delay();
        SCL_SET_HIGH();
        SmartCar_SoftI2c_Delay();
        c <<= 1;
        if(SDA_LEVEL)
        {
            c += 1;
        }
    }
    DIR_OUT();
    SCL_SET_LOW();
    SmartCar_SoftI2c_Delay();
    SmartCar_SoftI2c_Sendack(ack_x);
    return c;
}

//写数据到设备寄存器中
void SmartCar_SoftI2c_Writereg(uint8 device_addr, uint8 reg_addr, uint8 data)
{
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//从设备地址加写位0
    SmartCar_SoftI2c_Sendch(reg_addr);//从设备寄存器地址
    SmartCar_SoftI2c_Sendch(data);
    SmartCar_SoftI2c_Stop();
}

//从设备寄存器读数据
uint8 SmartCar_SoftI2c_Readreg(uint8 device_addr, uint8 reg_addr)//IIC_type type//这里有一个选择通信方式
{
    uint8 data;
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//从设备地址加写位0
    SmartCar_SoftI2c_Sendch(reg_addr);//从设备寄存器地址
    //if(type == SCCB)SmartCar_SoftI2c_Stop();

    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x01);//从设备地址加读位1
    data = SmartCar_SoftI2c_Readch(NACK);
    SmartCar_SoftI2c_Stop();
    return data;
}

//从从设备寄存器读取多字节数据
void SmartCar_SoftI2c_Readregs(uint8 device_addr, uint8 reg_addr, uint8* data_addr, uint8 num)//IIC_type type)//选择通信方式
{
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//从设备地址加写位0
    SmartCar_SoftI2c_Sendch(reg_addr);//从设备寄存器地址
    //if(type== SCCB)SmartCar_SoftI2c_Stop;
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x01);//从设备地址加读位1
    while(--num)
    {
        *data_addr = SmartCar_SoftI2c_Readch(ACK);
        data_addr++;
    }
    *data_addr = SmartCar_SoftI2c_Readch(NACK);
    SmartCar_SoftI2c_Stop();
}

//引脚初始化
void SmartCar_SoftI2c_PinInit(void)
{
    IfxPort_setPinMode(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM);
    IfxPort_setPinMode(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM);
}
