#include "STC15F2K60S2.H"
#include "motor.h"
#include "btooth.h"
#include "dis.h"
#include "btn.h"
#include "buzzer.h"
#include "ir_re.h"
#include "vibration.h"

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

unsigned char buffer_DS[1], match[1]={0x11};


void DStop()
{
	Compare = 1; 	
}

void init_DStop()
{
	Uart2Init(1200, Uart2Usedfor485);
	SetUart2Rxd(buffer_DS, 1, match, 0);
	SetEventCallBack(enumEventUart2Rxd, DStop);
}