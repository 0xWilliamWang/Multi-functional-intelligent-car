#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
 
#define LEDON 1     		//����
#define LEDOFF 0			//Ϩ��


#define LED2 PBout(12)	// PB12
#define LED3 PBout(13)	// PB13
#define LED4 PBout(14)	// PB14

void LED_Init(void);//��ʼ��
		 				    
#endif
