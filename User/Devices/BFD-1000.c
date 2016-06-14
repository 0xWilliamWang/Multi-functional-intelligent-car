#include "BFD-1000.h"
/*
BFD-1000: 检测到黑线输出低电平，反之---
Near：红外壁障信号输出，接近为高电平、远离为低电平
CLP：触碰开关，有触碰高电平输出、无触碰低电平输出
*/

uchar BDF1000_Value_check[6]; // 触碰开关：1、循迹信号：1-5、壁障信号：6

void BDF1000_Config(void)
{
	
}

void BFD_1000_Check (void)
{
	//BDF1000_Value_check[0] = 
	if(BDF1000_Value_check == 0)
	{

	}
}
