#include "PWM_Output.h"
#include "VS1838B.h"

volatile u8 GetValue = 0;
volatile unsigned int Set_Output_Value = 500;

void GPIOA_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //����TIM2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	/**����pwm����Ķ�ӦGPIO�ܽ�****/	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		     //��������ʽ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void TIM2_TimeBsae_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_TimeBaseStructure.TIM_Period = 999;      //�趨������ֵ 1000
	TIM_TimeBaseStructure.TIM_Prescaler = 72;	     //����Ԥ��Ϊ72����Ϊ1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
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
	// ʱ���ѿ���
	/***ͨ��1������*****/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// ����ʹ�ܵ������ر�
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  // ���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); // ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
	/***ͨ��2������*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	/***ͨ��3������*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/***ͨ��4������*****/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Value;	  //����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��4
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE);         //ʹ�ܶ�ʱ��2	          
	
	//TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);   // ʹ���жϣ���PWM������б�Ҫ��
	
	printf("\r\n \r\n Enter TIM2_Compare_GPIO_Config Function \r\n");
	printf("\r\n CCR_Value = %d/1000\r\n",CCR_Value);
}

void PWM_ControlWheel(void)
{
	GetValue = Remote_Process_PWM();
	if(GetValue == 224) // ����
	{
		Set_Output_Value =  Set_Output_Value - 100;
		if(Set_Output_Value < 100)
		{
			Set_Output_Value = 100;
		}
		TIM2_CompareConfig(Set_Output_Value);
		GetValue = 0;
	}
	if(GetValue == 144)  // ����
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
