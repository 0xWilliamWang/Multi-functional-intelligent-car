/**
  ******************************************************************************
  * @file    
  * @author  kyle
  * @version V1.0
  * @date    2015-7-28 10:02:19
  * @brief   开发一款基于STM32F103VBT6的多功能智能车
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */  
#include "sys.h"
#include "led.h"
#include <stdio.h> 
#include "delay.h"
#include "wheel.h"
#include "VS1838B.h"
#include "usart.h"
#include "PWM_Output.h"
#include "SpeedDetection.h"
#include "bsp_ili9341_lcd.h"

#define SIZE 40

extern void Lcd_Delay(__IO uint32_t nCount);
extern volatile float Speed1;
extern volatile float DriveDistance1;
extern volatile float Speed2;
extern volatile float DriveDistance2;
volatile u32 SpeedDetectionValue3 = 0;
char line1[SIZE];
char line2[SIZE];
char line3_state[SIZE];
char line4[SIZE];
char line5[SIZE];
char line6[SIZE];
char line7[SIZE];
char line8[SIZE];
char line9[SIZE];
char line10[SIZE];

void LcdShow(void);
void WriteToLcd (void);
#define L 0
#define H 1

u8 flag = 0;

int cnt = 0;

int main(void)
{
	USART1_Init();
	GPIODConfig();
	
	while(1)
	{ 
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) == 1 && flag)
		{
			printf("ENTER");
			cnt++;
			flag = 0;
		}  
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) == 0)
		{
			printf("out");
			flag = 1;
		}  
		printf("\r\n cnt = %d \r\n",cnt);
	}	
	
}

void LcdShow(void)
{
		LCD_DispStr(10, 10, (uint8_t *)line1, RED);
		LCD_DispStr(10, 30, (uint8_t *)line2, RED);
		LCD_DispStr(10, 40, (uint8_t *)line3_state, RED);
		LCD_DispStr(10, 50, (uint8_t *)line4, RED);
		LCD_DispStr(10, 60, (uint8_t *)line5, RED);
		LCD_DispStr(10, 70, (uint8_t *)line6, RED);
		LCD_DispStr(10, 80, (uint8_t *)line7, RED);
		LCD_DispStr(10, 90, (uint8_t *)line8, RED);
		LCD_DispStr(10, 100, (uint8_t *)line9, RED);
		LCD_DispStr(10, 120, (uint8_t *)line10, RED);

}
void WriteToLcd (void)
{
	sprintf(line1,"***Multi-functional intelligent car***");
	sprintf(line2,"The current state:");
	sprintf(line4,"The current speed:");
	sprintf(line5,"            left : %f cm",Speed1);
	sprintf(line6,"            right: %f cm",Speed2);
	sprintf(line7,"The current distance:");
	sprintf(line8,"            left : %f cm",DriveDistance1);
	sprintf(line9,"            right: %f cm",DriveDistance2);
	sprintf(line10,"***********By WangKaiXuan*************");	
}
