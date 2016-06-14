#ifndef __WHEEL_H
#define __WHEEL_H
#include "stm32f10x.h"
#include "stdio.h"
#include "VS1838B.h"

void Wheel_Init(void);
void InfraredControl(void);
void Run_Forward(void);
void Run_Behind(void);
void Turn_Right(void);
void Turn_RightSharp(void);
void Turn_Left(void);
void Turn_LeftSharp(void);
void Stop(void);

#endif //#define __WHEEL_H
