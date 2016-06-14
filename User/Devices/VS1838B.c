#include "VS1838B.h"
#include "delay.h"  
#include "usart.h"

volatile u32 Remote_Odr=0; // 命令暂存
volatile u8  Remote_Cnt=0; // 此次按下键的次数
volatile u8  Remote_Rdy=0; // 红外线接收的数据
volatile u8 t1,t2;   

void Remote_Init(void)
{							 
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 	/*时钟引脚配置*/	 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);  
  /*中断配置*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource14); 
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
 /*NVIC配置*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}   

u8 Pulse_Width_Check(void)
{
    u8 t=0;	 
    while(RDATA)
    {	 
				t++;
				Delay_us(20);					 
        if(t==250)
					return t;
    }
    return t;
}			   

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14) != RESET) 
	{	
		u8 res=0;
		u8 OK=0; 
		u8 RODATA=0;   		 
		while(1)
		{        
        if(RDATA)
        {
            res=Pulse_Width_Check();  
//						printf("res: %d\n", res);

					if(res==250)break;
            if(res>=200&&res<250)OK=1;
            else if(res>=85&&res<200)
            {  							    		 
                Remote_Rdy=1;
                Remote_Cnt++;
                break;
            }
            else if(res>=50&&res<85)RODATA=1;//1.5ms
            else if(res>=10&&res<50)RODATA=0;//500us
            if(OK)
            {
                Remote_Odr<<=1;
                Remote_Odr+=RODATA; 
                Remote_Cnt=0;
            }   
        }			 						 
		} 
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

u8 Remote_Process(void)
{               
    u8 t1,t2;   
    t1=Remote_Odr>>24;
    t2=(Remote_Odr>>16)&0xff;
    Remote_Rdy=0; 		      
    if(t1==(u8)~t2&&t1==REMOTE_ID)
    { 
        t1=Remote_Odr>>8;
        t2=Remote_Odr; 	
        if(t1==(u8)~t2)return t1;
    }     
    return 0;
}

u8 Remote_Process_PWM(void)
{               
    u8 t1,t2;   
    t1=Remote_Odr>>24;
    t2=(Remote_Odr>>16)&0xff;
    Remote_Rdy=0; 		      
    if(t1==(u8)~t2&&t1==REMOTE_ID)
    { 
        t1=Remote_Odr>>8;
        t2=Remote_Odr; 	
				Remote_Odr = 0;
        if(t1==(u8)~t2)
					return t1;
    }     
    return 0;
}
