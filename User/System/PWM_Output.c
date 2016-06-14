#include "PWM_Output.h"
#include "VS1838B.h"

volatile u8 GetValue = 0;
volatile unsigned int Set_Output_Value = 500;

void GPIOA_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //开启TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	/**配置pwm输出的对应GPIO管脚****/	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		     //复用推挽式输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void TIM2_TimeBsae_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_TimeBaseStructure.TIM_Period = 999;      //设定总周期值 1000
	TIM_TimeBaseStructure.TIM_Prescaler = 72;	     //设置预分为72，即为1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}

void PWMCtrlWheel_Init(void)
{
	GPIOA_Init();
	TIM2_TimeBsae_Init();
}
void TIM2_CompareConfig(unsigned int CCR_Value)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 时钟已开启
	/***通道1的配置*****/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 配置使能的输出与关闭
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  // 设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); // 使能TIM2在CCR1上的预装载寄存器
	/***通道2的配置*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	/***通道3的配置*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/***通道4的配置*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  //设置通道4的电平跳变值，输出另外一个占空比的PWM
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	  //使能通道4
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE);         //使能定时器2	          
	
	//TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);   // 使能中断，在PWM输出中有必要吗？
	
	printf("\r\n \r\n Enter TIM2_Compare_GPIO_Config Function \r\n");
	printf("\r\n CCR_Value = %d/1000\r\n",CCR_Value);
}

void PWM_ControlWheel(void)
{
	GetValue = Remote_Process_PWM();
	if(GetValue == 224) // 减速
	{
		Set_Output_Value =  Set_Output_Value - 100;
		if(Set_Output_Value < 100)
		{
			Set_Output_Value = 100;
		}
		TIM2_CompareConfig(Set_Output_Value);
		GetValue = 0;
	}
	if(GetValue == 144)  // 加速
	{
		Set_Output_Value = Set_Output_Value + 100;
		if(Set_Output_Value > 900)
		{
			Set_Output_Value = 900;
		}
		TIM2_CompareConfig(Set_Output_Value);
		GetValue = 0;
	}	
	printf("\r\n GetValue = %d \r\n",GetValue);
	printf("\r\n Set_Output_Value = %d \r\n",Set_Output_Value);
}
