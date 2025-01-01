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

void set_btn_info()
{
	if(GetKeyAct(enumKey2) == enumKeyPress)
	{
		my_model++;
		my_model %= 3;
	}
	else if(GetKeyAct(enumKey1) == enumKeyPress)
	{
		Compare++;
		if(Compare == 11)  Compare = 1;
	}
	
	switch (my_model)
	{
		case bluetooth:
			init_btooth();
			break;
		case ir:
			init_ir();
			break;
		case rs485:
			break;
	}
	
}


void init_btn()
{
	KeyInit();
	
	SetEventCallBack(enumEventKey, set_btn_info);
}

