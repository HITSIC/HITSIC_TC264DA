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
 * @note������ͷ���
 *          ����ͷ������ؽ�Ĭ��ʹ�ô�P00_0��ʼ�İ˸����ţ�ʹ��DMAͨ��5��Ϊ����ͷDMAͨ�������жϴ����ⲿ�ж�2

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_MT9V034_H
#define SMARTCAR_MT9V034_H

#include "SmartCar_Uart.h"
#include "SmartCar_Eru.h"
#include "SmartCar_EruDma.h"
#include "common.h"

#define MT9V034_W               188                 //ͼ����  ��Χ1-188
#define MT9V034_H               120                 //ͼ��߶�  ��Χ1-120

//--------------------------------------------------------------------------------------------------
//��������
//--------------------------------------------------------------------------------------------------
#define MT9V034_COF_UART        1              //��������ͷ��ʹ�õ��Ĵ���
#define MT9V034_COF_UART_TX     IfxAsclin1_TX_P02_2_OUT
#define MT9V034_COF_UART_RX     IfxAsclin1_RXG_P02_3_IN

#define MT9V034_VSYNC_PIN       CH3_P02_0  //���ж����� ��ѡ��Χ�ο�ERU_PIN_enumö�� ��������������ѡ��Ϊͬһ��ͨ���������ǹ����жϵ�ͨ��
                                                    //���糡�ж�ѡ��ERU_CH3 ��ô�������žͲ���ѡ��ERU_CH7����Ϊ3��7���ж��ǹ��õġ�

#define MT9V034_DATA_PIN_MODULE        MODULE_P00               //����D0��������  ����D0����ΪP00_0 ��ôD1��ʹ�õ�������ΪP00_1����������
                                                    //�����ò���P00_0��P02_0��P15_0����������Ϊ��������

#define MT9V034_PCLK_PIN        CH2_P02_1 //��������ʱ������ ��ѡ��Χ�ο�ERU_PIN_enumö�� �����볡�ж�����ѡ��Ϊͬһ��ͨ���������ǹ����жϵ�ͨ��
                                                    //���糡�ж�ѡ��ERU_CH3 ��ô�������žͲ���ѡ��ERU_CH7����Ϊ3��7���ж��ǹ��õġ�

#define MT9V034_DMA_CH          IfxDma_ChannelId_5  //����ʹ�õ�DMAͨ�� 0-47��ѡ  ͨ����Խ�����ȼ�Խ��

//����ͷ����ö��
typedef enum
{
    INIT = 0,               //����ͷ��ʼ������
    AUTO_EXP,               //�Զ��ع�����
    EXP_TIME,               //�ع�ʱ������
    FPS,                    //����ͷ֡������
    SET_COL,                //ͼ��������
    SET_ROW,                //ͼ��������
    LR_OFFSET,              //ͼ������ƫ������
    UD_OFFSET,              //ͼ������ƫ������
    GAIN,                   //ͼ��ƫ������
    CONFIG_FINISH,          //������λ����Ҫ����ռλ����

    COLOR_GET_WHO_AM_I = 0xEF,
    SET_EXP_TIME = 0XF0,    //���������ع�ʱ������
    GET_STATUS,             //��ȡ����ͷ��������
    GET_VERSION,            //�̼��汾������

    SET_ADDR = 0XFE,        //�Ĵ�����ַ����
    SET_DATA                //�Ĵ�����������
}CMD;

typedef enum //ö�ٶ˿ڵ�ƽ
{
    CAMERA_BIN=1,       //С���
    CAMERA_BIN_UART,    //С��紮�ڰ汾
    CAMERA_GRAYSCALE,   //�����
    CAMERA_COLOR       //��ͫ
}CAMERA_TYPE_enum;


extern uint8  uart_receive[3];         //�����ڽ���������Ϣʱ����  ��ֹ�û�ʹ�øñ���
extern uint8  uart_receive_num;        //�����ڽ���������Ϣʱ����  ��ֹ�û�ʹ�øñ���
extern vuint8 uart_receive_flag;  //�����ڽ���������Ϣʱ����  ��ֹ�û�ʹ�øñ���
extern CAMERA_TYPE_enum camera_type;
extern uint8* camera_buffer_addr;

extern uint8    mt9v034_finish_flag;//һ��ͼ��ɼ���ɱ�־λ
extern uint8    mt9v034_image[MT9V034_H][MT9V034_W];

void MT9V034_Uart_Callback(void);
void MT9V034_SetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2]);
void MT9V034_GetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2]);
uint16 MT9V034_GetVersion(uint8 uart_num);
uint16 MT9V034_SetExptime(uint8 uart_num, uint16 light);
unsigned short MT9V034_Setreg(uint8 uart_num, uint8 addr, uint16 data);
void SmartCar_MT9V034_Init(void);
void MT9V034_VSYNC(void);
void MT9V034_DMA(void);
void SmartCar_Show_IMG(uint8* image, uint16 ro, uint16 co);

#endif
