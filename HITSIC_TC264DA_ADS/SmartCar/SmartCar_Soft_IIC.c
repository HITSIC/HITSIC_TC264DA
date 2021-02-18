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
 * @note�����iic
 *      SDA:P02_4       SCL:P02_5

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/


#include "SmartCar_Soft_IIC.h"


/*���Ų������壬�������*/
#define SDA_LEVEL          IfxPort_getPinState(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SDA_SET_HIGH()     IfxPort_setPinHigh(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SDA_SET_LOW()      IfxPort_setPinLow(&IIC_SDA_PIN_MODULE,IIC_SDA_PIN_NUM)
#define SCL_SET_HIGH()     IfxPort_setPinHigh(&IIC_SCL_PIN_MODULE,IIC_SCL_PIN_NUM)
#define SCL_SET_LOW()      IfxPort_setPinLow(&IIC_SCL_PIN_MODULE,IIC_SCL_PIN_NUM)
#define DIR_IN()           IfxPort_setPinModeInput(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_InputMode_noPullDevice)
#define DIR_OUT()          IfxPort_setPinMode(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_Mode_outputPushPullGeneral)


uint8 i2c_main;//��������ַ
uint8 i2c_sub;//�������Ĵ�����ַ
uint8* i2c_buf;//����/���������׵�ַ
uint8 i2c_num;//���ͽ������ݸ���

#define ACK 1//��Ӧ��
#define NACK 0//��Ӧ��

uint16 simi2c_delay_time = SIMIIC_DELAY_TIME;//��ʱʱ��

void SmartCar_SoftI2c_DelaySet(uint16 time)
{
    simi2c_delay_time = time;
}

void SmartCar_SoftI2c_Delay(void)
{
    //����
    uint16 delay_time;
    delay_time = simi2c_delay_time;
    while(delay_time--){};
    //��������systick��ʱ���
}

//i2c���俪ʼ
void SmartCar_SoftI2c_Start(void)
{
    SDA_SET_HIGH();
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    SDA_SET_LOW();
    SmartCar_SoftI2c_Delay();
    SCL_SET_LOW();
}

//i2c����ֹͣ
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

//��������豸����Ӧ��/��Ӧ���ź�
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

//�����ȴ����豸Ӧ���ź�
static int SmartCar_Sccb_Waitack(void)
{
    SCL_SET_LOW();
    DIR_IN();
    SmartCar_SoftI2c_Delay();
    SCL_SET_HIGH();
    SmartCar_SoftI2c_Delay();
    if(SDA_LEVEL)//Ӧ��ߵ�ƽ���쳣��ͨ��ʧ��
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

//���͵����ֽ�
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

//����һ���ֽ�����
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

//д���ݵ��豸�Ĵ�����
void SmartCar_SoftI2c_Writereg(uint8 device_addr, uint8 reg_addr, uint8 data)
{
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//���豸��ַ��дλ0
    SmartCar_SoftI2c_Sendch(reg_addr);//���豸�Ĵ�����ַ
    SmartCar_SoftI2c_Sendch(data);
    SmartCar_SoftI2c_Stop();
}

//���豸�Ĵ���������
uint8 SmartCar_SoftI2c_Readreg(uint8 device_addr, uint8 reg_addr)//IIC_type type//������һ��ѡ��ͨ�ŷ�ʽ
{
    uint8 data;
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//���豸��ַ��дλ0
    SmartCar_SoftI2c_Sendch(reg_addr);//���豸�Ĵ�����ַ
    //if(type == SCCB)SmartCar_SoftI2c_Stop();

    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x01);//���豸��ַ�Ӷ�λ1
    data = SmartCar_SoftI2c_Readch(NACK);
    SmartCar_SoftI2c_Stop();
    return data;
}

//�Ӵ��豸�Ĵ�����ȡ���ֽ�����
void SmartCar_SoftI2c_Readregs(uint8 device_addr, uint8 reg_addr, uint8* data_addr, uint8 num)//IIC_type type)//ѡ��ͨ�ŷ�ʽ
{
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x00);//���豸��ַ��дλ0
    SmartCar_SoftI2c_Sendch(reg_addr);//���豸�Ĵ�����ַ
    //if(type== SCCB)SmartCar_SoftI2c_Stop;
    SmartCar_SoftI2c_Start();
    SmartCar_SoftI2c_Sendch((device_addr<<1) | 0x01);//���豸��ַ�Ӷ�λ1
    while(--num)
    {
        *data_addr = SmartCar_SoftI2c_Readch(ACK);
        data_addr++;
    }
    *data_addr = SmartCar_SoftI2c_Readch(NACK);
    SmartCar_SoftI2c_Stop();
}

//���ų�ʼ��
void SmartCar_SoftI2c_PinInit(void)
{
    IfxPort_setPinMode(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&IIC_SCL_PIN_MODULE, IIC_SCL_PIN_NUM);
    IfxPort_setPinMode(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinHigh(&IIC_SDA_PIN_MODULE, IIC_SDA_PIN_NUM);
}
