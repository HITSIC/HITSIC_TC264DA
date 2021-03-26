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


#include <SmartCar_Assert.h>
#include "IfxDma_Dma.h"
#include "IfxScuEru.h"
#include "SmartCar_EruDma.h"


typedef struct
{
    Ifx_DMA_CH linked_list[8];//DMA链表
    IfxDma_Dma_Channel channel;              //DMA通道句柄
}DMA_LINK;

#if(0 == ERU_DMA_INT_SERVICE)//由谁相应dma中断决定把全局变量放在哪一个CPU中
#pragma section all "cpu0_dsram"
IFX_ALIGN(256) DMA_LINK dma_link_list;

#elif(1 == ERU_DMA_INT_SERVICE)
#pragma section all "cpu1_dsram"
IFX_ALIGN(256) DMA_LINK dma_link_list;

#endif
#pragma section all restore


//-------------------------------------------------------------------------------------------------------------------
//  @brief      eru触发dma初始化
//  @param      dma_ch              选择DMA通道
//  @param      source_addr         设置源地址
//  @param      destination_addr    设置目的地址
//  @param      eru_pin             设置触发的eru通道
//  @param      trigger             设置触发方式
//  @param      dma_count           设置dma搬移次数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 SmartCar_EruDma_Init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count)
{
    IfxDma_Dma_Channel dmaChn;
    //eru触发DMA通道号   在eru文件中设置eru的优先级，即为触发的通道
    Eru_Init(eru_pin, trigger);

    IfxDma_Dma_Config        dmaConfig;
    IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);

    IfxDma_Dma               dma;
    IfxDma_Dma_initModule(&dma, &dmaConfig);

    IfxDma_Dma_ChannelConfig cfg;
    IfxDma_Dma_initChannelConfig(&cfg, &dma);

    uint8  list_num, i;
    uint16 single_channel_dma_count;

    SMARTCAR_ASSERT(!(dma_count%8));//传输次数必须为8的倍数


    list_num = 1;
    single_channel_dma_count = dma_count / list_num;
    if(16384 < single_channel_dma_count)
    {
        while(TRUE)
        {
            single_channel_dma_count = dma_count / list_num;
            if((single_channel_dma_count <= 16384) && !(dma_count % list_num))
            {
                break;
            }
            list_num++;
            if(list_num > 8) SMARTCAR_ASSERT(FALSE);
        }
    }


    if(1 == list_num)
    {
        cfg.shadowControl               = IfxDma_ChannelShadow_none;
        cfg.operationMode               = IfxDma_ChannelOperationMode_single;
        cfg.shadowAddress               = 0;
    }
    else
    {
        cfg.shadowControl               = IfxDma_ChannelShadow_linkedList;
        cfg.operationMode               = IfxDma_ChannelOperationMode_continuous;
        cfg.shadowAddress               = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (unsigned)&dma_link_list.linked_list[1]);
    }

    cfg.requestMode                     = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    cfg.moveSize                        = IfxDma_ChannelMoveSize_8bit;
    cfg.busPriority                     = IfxDma_ChannelBusPriority_high;

    cfg.sourceAddress                   = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), source_addr);
    cfg.sourceAddressCircularRange      = IfxDma_ChannelIncrementCircular_none;
    cfg.sourceCircularBufferEnabled     = TRUE;

    cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;

    cfg.channelId                       = (IfxDma_ChannelId)dma_ch;
    cfg.hardwareRequestEnabled          = FALSE;
    cfg.channelInterruptEnabled         = TRUE;
    cfg.channelInterruptPriority        = ERU_DMA_INT_PRIO;
    cfg.channelInterruptTypeOfService   = ERU_DMA_INT_SERVICE;



    cfg.destinationAddress              = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr);

    cfg.transferCount                   = single_channel_dma_count;

    IfxDma_Dma_initChannel(&dmaChn, &cfg);

    if(1 < list_num)
    {
        i = 0;
        while(i < list_num)
        {
            cfg.destinationAddress      = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr + single_channel_dma_count * i);
            if(i == (list_num - 1)) cfg.shadowAddress = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (unsigned)&dma_link_list.linked_list[0]);
            else                    cfg.shadowAddress = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (unsigned)&dma_link_list.linked_list[i+1]);
            cfg.transferCount           = single_channel_dma_count;

            IfxDma_Dma_initLinkedListEntry((void *)&dma_link_list.linked_list[i], &cfg);
            i++;
        }
    }


    IfxDma_Dma_getSrcPointer(&dma_link_list.channel)->B.CLRR = 1;

    return list_num;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      dma停止
//  @param      dma_ch              选择DMA通道
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Dma_Stop(IfxDma_ChannelId dma_ch)
{
    IfxDma_disableChannelTransaction(&MODULE_DMA, dma_ch);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      dma启动
//  @param      dma_ch              选择DMA通道
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Dma_Start(IfxDma_ChannelId dma_ch)
{
    IfxDma_enableChannelTransaction(&MODULE_DMA, dma_ch);
}
