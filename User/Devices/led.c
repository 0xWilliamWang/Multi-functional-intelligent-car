/**
  ******************************************************************************
  * @file    led.c 
  * @author  联航精英训练营   allen@unigress.com
  * @version V1.0
  * @date    2015-07-22
  * @brief   本代码中包含控制MINI103平台中小灯控制的函数实现，我们使用PB12~14
  *          来连接3个LED灯，由于所有LED灯采用共阴极设计，因此只需要将所用的IO端
  *          口设置为输出模式，并将该端口置低即可点亮对应的LED灯。
  ******************************************************************************
  * @attention
  *
  * 本程序所提供的源代码均为本程序作者或由网络收集整理而来，仅供学习和研究使用。
  * 如有侵犯的地方，请及时联系，我们会立即修改。使用本程序源码的用户必须明白，
  * 我们不能保证所提供的源码及其它资源的准确性、安全性和完整性，因此我们将不负责
  * 承担任何直接，间接因使用这些源码对自己和他人造成任何形式的损失或伤害。任何人
  * 在使用本代码时，应注明作者和出处。
  *
  * <h2><center>版权所有(C) 2013 太原联航科技有限公司</center></h2>
  ******************************************************************************
  */  
#include "led.h"
  
//初始化PB12...PB14为输出口.并使能这3个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  //使能PB端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14;
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz				 										//根据设定参数初始化GPIOE
    
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    GPIO_ResetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14);
}

/******************* (C) 版权所有 2013 太原联航科技有限公司 *******************/
