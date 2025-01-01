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

unsigned char buffer_ir[1];


void set_speed_and_direct_ir()
{
	unsigned char inst = buffer_ir[0];
	
	if(inst > 0x10) Compare = inst & 0x0f; 
	else my_direct = inst  & 0x07;
	
}

void init_ir()
{
	IrInit(NEC_R05d);
	SetIrRxd(buffer_ir,1);
	SetEventCallBack(enumEventIrRxd, set_speed_and_direct_ir);

}