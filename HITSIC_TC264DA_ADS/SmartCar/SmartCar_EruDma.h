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
 * @note：外部中断触发Dma传输

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/



#ifndef SMARTCAR_ERU_DMA_H
#define SMARTCAR_ERU_DMA_H

#include "SmartCar_Eru.h"
#include "IfxDma.h"

#define ERU_DMA_INT_SERVICE     IfxSrc_Tos_cpu0 //ERU触发DMA中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define ERU_DMA_INT_PRIO        60  //ERU触发DMA中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define CLEAR_DMA_FLAG(dma_ch)  IfxDma_clearChannelInterrupt(&MODULE_DMA, dma_ch);
#define DMA_SET_DESTINATION(dma_ch, destination_addr)   IfxDma_setChannelDestinationAddress(&MODULE_DMA, dma_ch, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr))

uint8 SmartCar_EruDma_Init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count);
void Dma_Stop(IfxDma_ChannelId dma_ch);
void Dma_Start(IfxDma_ChannelId dma_ch);

#endif
