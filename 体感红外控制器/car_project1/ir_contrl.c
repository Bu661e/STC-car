#include "STC15F2K60S2.H"


#include "uart2.h"
#include "uart1.h"
#include "ir.h"
#include "sys.H"                 
#include "Key.h"
#include "displayer.H" 



unsigned char Compare =0;
unsigned char buffer_ir[1];


void set_speed_and_direct_ir()
{
	unsigned char inst_ir = buffer_ir[0];
	
	if(inst_ir > 0x10) Compare = inst & 0x0f; 
	else my_direct = inst;
	
}

void init_ir_contrl()
{
	IrInit(NEC_R05d);
	IrTxdSet(buffer_ir,1);
	SetEventCallBack(enumEventIrRxd, set_speed_and_direct_ir);
}

