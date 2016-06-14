#ifndef __BSP_ILI9341_LCD_H
#define	__BSP_ILI9341_LCD_H

#include "stm32f10x.h"

/***************************************************************************************
2^26 =0X0400 0000 = 64MB,ÿ�� BANK ��4*64MB = 256MB
64MB:FSMC_Bank1_NORSRAM1:0X6000 0000 ~ 0X63FF FFFF
64MB:FSMC_Bank1_NORSRAM2:0X6400 0000 ~ 0X67FF FFFF
64MB:FSMC_Bank1_NORSRAM3:0X6800 0000 ~ 0X6BFF FFFF
64MB:FSMC_Bank1_NORSRAM4:0X6C00 0000 ~ 0X6FFF FFFF

ѡ��BANK1-BORSRAM4 ���� TFT����ַ��ΧΪ0X6C00 0000 ~ 0X6FFF FFFF
FSMC_A23 ��LCD��DC(�Ĵ���/����ѡ��)��
�Ĵ�������ַ = 0X6C00 0000
RAM����ַ = 0X6D00 0000 = 0X6C00 0000+2^23*2 = 0X6C00 0000 + 0X100 0000 = 0X6D00 0000
��ѡ��ͬ�ĵ�ַ��ʱ����ַҪ���¼���  
****************************************************************************************/


#define Bank1_LCD_C    ((u32)0x6C000000)	   //Disp Reg ADDR
#define Bank1_LCD_D    ((u32)0x6D000000)       //Disp Data ADDR       // A23 PE2

/*ѡ��LCDָ���Ĵ���*/
#define LCD_WR_REG(index)    ((*(__IO u16 *) (Bank1_LCD_C)) = ((u16)index))
/*��LCD GRAMд������*/
#define LCD_WR_Data(val)       ((*(__IO u16 *) (Bank1_LCD_D)) = ((u16)(val)))

#define LCD_ILI9341_CMD(index)       LCD_WR_REG(index)
#define LCD_ILI9341_Parameter(val)	 LCD_WR_Data(val)

#define COLUMN		240
#define PAGE		320	

// SRT ��string����д
#define STR_WIDTH		6		/* �ַ���� */
#define STR_HEIGHT		12		/* �ַ��߶� */

#define BACKGROUND		BLACK

#define WHITE		 		 0xFFFF	/* ��ɫ */
#define BLACK        0x0000	/* ��ɫ */
#define GREY         0xF7DE	/* ��ɫ */
#define BLUE         0x001F	/* ��ɫ */
#define BLUE2        0x051F	/* ǳ��ɫ */
#define RED          0xF800	/* ��ɫ */
#define MAGENTA      0xF81F	/* ����ɫ�����ɫ */
#define GREEN        0x07E0	/* ��ɫ */
#define CYAN         0x7FFF	/* ����ɫ����ɫ */
#define YELLOW       0xFFE0	/* ��ɫ */

void LCD_Init(void);
void Lcd_GramScan( uint16_t option );
void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_SetCursor(uint16_t x, uint16_t y);
void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void LCD_SetPoint(uint16_t x , uint16_t y , uint16_t color);
uint16_t LCD_GetPoint(uint16_t x , uint16_t y);
void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color);
void LCD_DispStr(uint16_t x, uint16_t y, uint8_t *pstr, uint16_t color);
void LCD_DisNum(uint16_t x, uint16_t y, uint32_t num, uint16_t color);


#endif /* __BSP_ILI9341_LCD_H */
