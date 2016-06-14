#include "wheel.h"
#include "stdio.h"
#include "string.h"

extern char line3_state[];

int InfraredCode = 0;

void Wheel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF,ENABLE);  // 使能时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,ENABLE);  // 使能时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   // 选择控制引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 引脚设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 设置输出频率50Mhz
	GPIO_Init(GPIOF,&GPIO_InitStructure);  // 调用库函数，初始化GPIOC

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13|GPIO_Pin_14;   // 选择控制引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // 引脚设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 设置输出频率50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStructure);  // 调用库函数，初始化GPIOC
}

void Run_Forward(void)
{		
	GPIO_SetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动


	GPIO_SetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Runing_Forward");
//	printf("\r\n \r\n Runing_Forward\r\n");
}

void Run_Behind(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动


	GPIO_SetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	
	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Runing_Behind");

//	printf("\r\n \r\n Runing_Behind\r\n");
}

void Turn_Right(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Turning_Right");
	//printf("\r\n \r\n Turning_Right\r\n");
}

void Turn_RightSharp(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动


	GPIO_SetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Turn_RightSharp");

//	printf("\r\n \r\n Turn_RightSharp\r\n");
}

void Turn_Left(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Turn_Left");

//	printf("\r\n \r\n Turning_Left\r\n");
}

void Turn_LeftSharp(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动


	GPIO_SetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_SetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Turn_LeftSharp");

//	printf("\r\n \r\n Turn_LeftSharp\r\n");
}

void Stop(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOF,GPIO_Pin_0);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);  // 通过控制驱动模块来控制直流电机的转动

	GPIO_ResetBits(GPIOB,GPIO_Pin_14);  // 通过控制驱动模块来控制直流电机的转动
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);  // 通过控制驱动模块来控制直流电机的转动

	memset(line3_state,'\0',strlen(line3_state));
	sprintf(line3_state,"            Stoping");

//	printf("\r\n \r\n Stoping \r\n");	
}

void InfraredControl(void)
{
	InfraredCode = Remote_Process();
	if(InfraredCode == 162)
		Turn_Left();

	if(InfraredCode == 98)
		Run_Forward();

	if(InfraredCode == 226)
		Turn_Right();

	if(InfraredCode == 2)
		Run_Behind();

	if(InfraredCode == 168)
		Stop();	

	if(InfraredCode == 34)
		Turn_LeftSharp();	

	if(InfraredCode == 194)
		Turn_LeftSharp();	
}
