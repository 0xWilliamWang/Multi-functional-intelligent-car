#ifndef __VS1838B_H
#define __VS1838B_H 

#include "sys.h"

#define RDATA PGin(14) // 红外线数据输入引脚
#define REMOTE_ID 0    // 控制器识别码

void Remote_Init(void);
u8 Remote_Process(void);
u8 Remote_Process_PWM(void);
u8 Pulse_Width_Check(void);

#endif //__VS1838B_H
