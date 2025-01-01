#include "STC15F2K60S2.H"
#include "motor.h"
#include "btooth.h"
#include "dis.h"
#include "btn.h"
#include "buzzer.h"
#include "ir_re.h"
#include "vibration.h"
#include "light.h"

#include "direct.h"
#include "speed.h"
#include "model.h"


#include "uart2.h"
#include "uart1.h"
#include "sys.H"                 
#include "Key.h"
#include "displayer.H" 
#include "Beep.h"
#include "ir.h"
#include "vib.H"

extern enum direct my_direct;
unsigned char buffer[1], *match;

void set_speed_and_direct()
{
	unsigned char inst = buffer[0];
	
	if (inst > 0x20) make_noise();
	else if(inst > 0x10) Compare = inst & 0x0f; 
	else my_direct = inst;
	  
}

void sent_temp_and_light()
{
	Uart2Print(buffer_adc, 2);
}

void init_btooth()
{
	Uart2Init(9600, Uart2UsedforEXT);
	SetUart2Rxd(buffer, 1, match, 0);
	
	SetEventCallBack(enumEventUart2Rxd, set_speed_and_direct);
	SetEventCallBack(enumEventSys1S, sent_temp_and_light);
}