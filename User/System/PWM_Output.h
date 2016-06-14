#ifndef __PWM_Output_H
#define __PWM_Output_H

#include "stm32f10x.h"
#include "stdio.h"

void GPIOA_Init(void);
void TIM2_TimeBsae_Init(void);
void TIM2_CompareConfig(unsigned int CCR_Value);
void PWM_ControlWheel(void);
void PWMCtrlWheel_Init(void);
#endif //#define __PWM_Output_H
