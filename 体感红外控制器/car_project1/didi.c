#include "STC15F2K60S2.H"

#include "beep.H"   
#include "uart2.h"
#include "uart1.h"
#include "sys.H"                 
#include "Key.h"
#include "displayer.H" 



void DIDI()
{
		SetBeep(1200,18);
}

void init_DIDI()
{
	BeepInit();
}