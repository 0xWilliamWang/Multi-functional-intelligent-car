#include "SpeedDetection.h"
#include "usart.h"

volatile u32 SpeedDetectionValue1 = 0;
volatile u32 SpeedDetectionValue2 = 0;
volatile u32 FlagSpeed = 0;

volatile float Speed1 = 0.0;
volatile float Speed2 = 0.0;
volatile float DriveDistance1 = 0.0;
volatile float DriveDistance2 = 0.0;


void SpeedDetection_Init(void)
{
	GPIODConfig();
}
void GPIODConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_7;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // …œ¿≠ ‰»Î
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void keyscanf(void)
{
	if(GPIO_ReadInputDataBit(GPIOD,3) == 0)
	{
		SpeedDetectionValue1++;
	}    	
}
void ViewSpeedDetection(void)
{
	printf("\r\n SpeedDetectionValue1 = %d \r\n",SpeedDetectionValue1);
	printf("\r\n SpeedDetectionValue2 = %d \r\n",SpeedDetectionValue2);
}

void SpeedDetection(void)
{
	if(FlagSpeed)
	{
		FlagSpeed = 0;
		
		Speed1 = (SpeedDetectionValue1/20)*18.84;
		DriveDistance1 += (SpeedDetectionValue1/20)*18.84;
		
		Speed2 = (SpeedDetectionValue2/20)*18.84;
		DriveDistance2 += (SpeedDetectionValue2/20)*18.84;
		
		SpeedDetectionValue1 = 0;
		SpeedDetectionValue2 = 0;
	}
}


void ViewSpeedSpeedDetection(void)
{
	printf("\r\n Speed1 = %fcm \r\n",Speed1);
	printf("\r\n DriveDistance1 = %fcm \r\n",DriveDistance1);

	printf("\r\n Speed2 = %fcm \r\n",Speed2);
	printf("\r\n DriveDistance2 = %fcm \r\n",DriveDistance2);
}
