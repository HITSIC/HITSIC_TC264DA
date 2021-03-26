/*
 * SmartCar_Flash.h
 *
 *  Created on: 2021��2��3��
 *      Author: ��Ψ
 */

#ifndef SMARTCAR_SMARTCAR_FLASH_H_
#define SMARTCAR_SMARTCAR_FLASH_H_

#include "common.h"
#include "IfxFlash_cfg.h"
#include "IfxScuWdt.h"
#include "IfxFlash.h"


#define EEPROM_BASE_ADDR             IFXFLASH_DFLASH_START
#define EEPROM_SIZE                  IFXFLASH_DFLASH_SIZE                   //һ����96KB
#define EEPROM_SECTOR_SIZE           (EEPROM_SIZE / IFXFLASH_DFLASH_NUM_LOG_SECTORS)
#define EEPROM_SECTOR_NUM            (IFXFLASH_DFLASH_NUM_LOG_SECTORS)      //һ����12������

#define EEPROM_PAGE_SIZE             IFXFLASH_DFLASH_PAGE_LENGTH
#define EEPROM_SECTOR_PAGE_NUM       (EEPROM_SECTOR_SIZE/EEPROM_PAGE_SIZE)  //ÿ��������1024ҳ


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ú궨���flash�������ݶ�ȡ
//  @param      sector_num      ��Ҫд����������
//  @param      page_num        ��Ҫ��ȡ��ҳ
//  @param      type            ��ȡ����������uint32 uint16 uint8 int32 float��
//  @return                     ���ظ�����ַ������
//  @since      v1.0
//  Sample usage:               Page_Read(0,0,uint32);//��ȡ0������  ��0Ҳ���� ����Ϊuint32
//-------------------------------------------------------------------------------------------------------------------
#define     Page_Read(sector_num,page_num,type)    (*(type *)((uint32)((EEPROM_BASE_ADDR + (sector_num)*EEPROM_SECTOR_SIZE) + (page_num*8))))

#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������
//  @param      sector_num      ��Ҫд����������   ������Χ0-11
//  @return     void
//  @since      v1.0
//  Sample usage:               Sector_Erase(0);
//-------------------------------------------------------------------------------------------------------------------
void Sector_Erase(uint32 sector_num);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���һҳ��д��
//  @param      sector_num      ��Ҫд����������   ������Χ0-11
//  @param      page_num        ��Ҫд���ҳ���     ������Χ0-1023
//  @param      buf             ��Ҫд������ݵ�ַ   ������������ͱ���Ϊuint32
//  @return     void
//  @since      v1.0
//  Sample usage:               Page_Program(0,0, &buf);
//-------------------------------------------------------------------------------------------------------------------
void Page_Program(uint32 sector_num, uint32 page_num, uint32 *buf);
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���һ������д��   ��buf��1024������д������
//  @param      sector_num      ��Ҫд����������   ������Χ0-11
//  @param      buf             ��Ҫд������ݵ�ַ   ������������ͱ���Ϊuint32
//  @return     void
//  @since      v1.0
//  Sample usage:               Sector_Program(0,0, &buf[0]);
//-------------------------------------------------------------------------------------------------------------------
void Sector_Program(uint32 sector_num, uint32* buf);


#endif /* SMARTCAR_SMARTCAR_FLASH_H_ */
