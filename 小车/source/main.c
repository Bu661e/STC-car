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

code unsigned long SysClock = 11059200; // System clock frequency (Hz), used for timing calculations

enum model my_model = rs485;

void main()
{

	init_motor();
	init_dis();
	init_btn();
	init_buzzer();
	init_vib();
	init_light();
	


	MySTC_Init();
    while (1)
    {
        MySTC_OS();
    }

}
