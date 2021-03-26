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
 * @note���ⲿ�жϴ���Dma����

    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/



#ifndef SMARTCAR_ERU_DMA_H
#define SMARTCAR_ERU_DMA_H

#include "SmartCar_Eru.h"
#include "IfxDma.h"

#define ERU_DMA_INT_SERVICE     IfxSrc_Tos_cpu0 //ERU����DMA�жϷ������ͣ����ж�����˭��Ӧ���� 0:CPU0 1:CPU1 3:DMA  ��������Ϊ����ֵ
#define ERU_DMA_INT_PRIO        60  //ERU����DMA�ж����ȼ� ���ȼ���Χ1-255 Խ�����ȼ�Խ�� ��ƽʱʹ�õĵ�Ƭ����һ��

#define CLEAR_DMA_FLAG(dma_ch)  IfxDma_clearChannelInterrupt(&MODULE_DMA, dma_ch);
#define DMA_SET_DESTINATION(dma_ch, destination_addr)   IfxDma_setChannelDestinationAddress(&MODULE_DMA, dma_ch, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr))

uint8 SmartCar_EruDma_Init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count);
void Dma_Stop(IfxDma_ChannelId dma_ch);
void Dma_Start(IfxDma_ChannelId dma_ch);

#endif
