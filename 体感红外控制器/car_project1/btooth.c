#include "STC15F2K60S2.H"
#include "motor.h"  
#include "direct.h"
#include "speed.h"


#include "uart2.h"
#include "uart1.h"
#include "sys.H"                 
#include "Key.h"
#include "displayer.H" 



extern enum direct my_direct;
unsigned char buffer[1], *match;
unsigned char sign = 15; //'F'




void set_speed_and_direct()
{
	unsigned char inst = buffer[0];
	
	if(inst > 0x10) Compare = inst & 0x0f; 
	else my_direct = inst;
	
}

void init_btooth()
{
	Uart2Init(9600, Uart2UsedforEXT);
	SetUart2Rxd(buffer, 1, match, 0);
	
	SetEventCallBack(enumEventUart2Rxd, set_speed_and_direct);
}