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




#include "SmartCar_MT9V034.h"
#include "SmartCar_GPIO.h"
#include "SmartCar_Systick.h"
#include "SmartCar_Upload.h"
#include "SmartCar_Oled.h"

IFX_ALIGN(4) uint8 mt9v034_image[MT9V034_H][MT9V034_W];//���ֽڶ���
uint8 image_size_half[MT9V034_H / 2][MT9V034_W / 2];

uint8 uart_receive[3] = {0};
uint8 uart_receive_num = 0;
vuint8 uart_receive_flag;
uint8 link_list_num;
CAMERA_TYPE_enum camera_type;
uint8 *camera_buffer_addr;


int16 MT9V034_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
                              //һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
    {EXP_TIME,          450}, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
    {FPS,               50},  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
    {SET_COL,           MT9V034_W}, //ͼ��������        ��Χ1-752     K60�ɼ���������188
    {SET_ROW,           MT9V034_H}, //ͼ��������        ��Χ1-480
    {LR_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {UD_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {GAIN,              32},  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�


    {INIT,              0}    //����ͷ��ʼ��ʼ��
};

//������ͷ�ڲ���ȡ������������
int16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����
    {EXP_TIME,          0},   //�ع�ʱ��
    {FPS,               0},   //ͼ��֡��
    {SET_COL,           0},   //ͼ��������
    {SET_ROW,           0},   //ͼ��������
    {LR_OFFSET,         0},   //ͼ������ƫ����
    {UD_OFFSET,         0},   //ͼ������ƫ����
    {GAIN,              0},   //ͼ������
};

void MT9V034_Uart_Callback(void)
{
    while(SmartCar_Uart_Queue(&uart_receive[uart_receive_num], MT9V034_COF_UART))
    {
        uart_receive_num++;
        if(1 == uart_receive_num && 0xA5 != uart_receive[0])
        {
            uart_receive_num = 0;
        }
        if(3 == uart_receive_num)
        {
            uart_receive_num = 0;
            uart_receive_flag = 1;
            IfxAsclin_Asc_clearRx(&uart[MT9V034_COF_UART]);
        }
    }
}

void MT9V034_SetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2])
{
    uint16 temp,i;
    uint8 send_buffer[4];
    uint8 time = 0;
    uart_receive_flag = 0;
//    do
//    {
        time++;
//        if(time > 10)   {break;}
        for(i = 0; i < CONFIG_FINISH;i++)
        {
            send_buffer[0] = 0xA5;
            send_buffer[1] = (uint8)buff[i][0];
            temp = buff[i][1];
            send_buffer[2] = temp >> 8;
            send_buffer[3] = (uint8)temp;
            SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
            Delay_ms(STM0, 2);
            //delay(2ms);
        }
        while(!uart_receive_flag){};
        uart_receive_flag = 0;
        /*for(int j = 0; j<2; j++)
        {
            PRINFT("send_buf %d = %d/n ", j+2, send_buffer[j+2]);
        }*/
        while((0xff != uart_receive[1]) || (0xff != uart_receive[2]));//���ݶ�ȡ��̫�ȶ�����֤�ܳ�ʼ���ɹ���ǿ�з�������
}

void MT9V034_GetConfig(uint8 uart_num, int16 buff[CONFIG_FINISH - 1][2])
{
    uint16 temp,i;
    uint8 send_buffer[4];

    for(i = 0;i<CONFIG_FINISH - 1;i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = GET_STATUS;
        temp = buff[i][0];
        send_buffer[2] = temp >> 8;
        send_buffer[3] = (uint8)temp;
        SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
        //Delay_ms(STM0, 10);
        //SmartCar_Uart_Transfer(send_buffer, 4, 0);
        while(!uart_receive_flag){};//SmartCar_Uart_Transfer(send_buffer, 4, uart_num); };
        uart_receive_flag = 0;
        /*for(int j = 0; j<2; j++)
        {
            PRINFT("send_buf %d = %d/n ", j+1, uart_receive[j+1]);
        }*/

        buff[i][1] = uart_receive[1] << 8 | uart_receive[2];
    }
}

uint16 MT9V034_GetVersion(uint8 uart_num)
{
    uint16 temp;
    uint8 send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = GET_STATUS;
    temp = GET_VERSION;
    send_buffer[2] = temp >> 8;
    send_buffer[3] = (uint8)temp;
    SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
    while(!uart_receive_flag){};
    uart_receive_flag = 0;
    return ((uint16)(uart_receive[1] << 8) | uart_receive[2]);
}

uint16 MT9V034_SetExptime(uint8 uart_num, uint16 light)
{
    uint16 temp;
    uint8 send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_EXP_TIME;
    temp = light;
    send_buffer[2] = temp >> 8;
    send_buffer[3] = (uint8)temp;
    SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
    while(!uart_receive_flag){};
    uart_receive_flag = 0;
    return ((uint16)(uart_receive[1] << 8) | uart_receive[2]);
}

uint16 MT9V034_Setreg(uint8 uart_num, uint8 addr, uint16 data)
{
    uint16 temp;
    uint8 send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_ADDR;
    temp = addr;
    send_buffer[2] = temp >> 8;
    send_buffer[3] = (uint8)temp;
    SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
    //Delay_ms(STM0,10);
    Delay_ms(STM0, 10);
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_DATA;
    temp = data;
    send_buffer[2] = temp >> 8;
    send_buffer[3] = (uint8)temp;
    SmartCar_Uart_Transfer(send_buffer, 4, uart_num);
    while(!uart_receive_flag){};
    uart_receive_flag = 0;
    return ((uint16)(uart_receive[1] << 8) | uart_receive[2]);
}

void SmartCar_MT9V034_Init(void)
{
    uint8 i;
    camera_type = CAMERA_GRAYSCALE;
    camera_buffer_addr = mt9v034_image[0];
    boolean interrupt_state = disableInterrupts();
    SmartCar_Uart_Init(IfxAsclin1_TX_P02_2_OUT, IfxAsclin1_RXG_P02_3_IN, 9600, MT9V034_COF_UART);
    enableInterrupts();
    //Delay_ms(STM0,1000);
    MT9V034_GetConfig(MT9V034_COF_UART, GET_CFG);
    uart_receive_flag = 0;
    MT9V034_SetConfig(MT9V034_COF_UART, MT9V034_CFG);
    MT9V034_GetConfig(MT9V034_COF_UART, GET_CFG);
    disableInterrupts();
    for(i = 0;i<8;i++)//����ͷ���ݲɼ����ų�ʼ��
    {
        GPIO_Init(&MT9V034_DATA_PIN_MODULE, i, PULLUP, 0);
    }
    link_list_num = SmartCar_EruDma_Init(MT9V034_DMA_CH, GET_PORT_IN_ADDR(0*32), camera_buffer_addr, MT9V034_PCLK_PIN, FALLING, MT9V034_W*MT9V034_H);//����P00_0
    Eru_Init(MT9V034_VSYNC_PIN, FALLING);//���жϳ�ʼ��
    restoreInterrupts(interrupt_state);
}

uint8 mt9v034_finish_flag = 0;
uint8 mt9v034_dma_int_num;

void MT9V034_VSYNC(void)
{
    //��vsync�жϱ�־λ
    CLEAR_GPIO_FLAG(MT9V034_VSYNC_PIN);
    //IfxScuEru_clearEventFlag((IfxScuEru_InputChannel)(MT9V034_VSYNC_PIN/3));
    mt9v034_dma_int_num = 0;
    if(!mt9v034_finish_flag)
    {
        if(1 == link_list_num)
        {
            //δ������ʽ����ģʽ
            //IfxDma_setChannelDestinationAddress(&MODULE_DMA, MT9V034_DMA_CH, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), camera_buffer_addr));
            DMA_SET_DESTINATION(MT9V034_DMA_CH, camera_buffer_addr);
        }
        Dma_Start(MT9V034_DMA_CH);
    }
}

void MT9V034_DMA(void)
{
    //���жϱ�־λ
    CLEAR_DMA_FLAG(MT9V034_DMA_CH);
    //IfxDma_clearChannelInterrupt(&MODULE_DMA, MT9V034_DMA_CH);
    mt9v034_dma_int_num++;
    if(mt9v034_dma_int_num >= link_list_num)
    {
        mt9v034_dma_int_num = 0;
        mt9v034_finish_flag = 1;
        Dma_Stop(MT9V034_DMA_CH);
    }
}

void SmartCar_Show_IMG(uint8* image, uint16 ro, uint16 co)
{
    image_size_half_forOLED((uint8*)image, (uint8*)image_size_half, ro, co);
    dis_bmp(ro / 2, co / 2, (uint8*)image_size_half, 100);
}
