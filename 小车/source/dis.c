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

#ifdef _displayer_H_

code char decode_table[] = {
    0x3F, // "0" 0
    0x06, // "1" 1
    0x5B, // "2" 2
    0x4F, // "3" 3
    0x66, // "4" 4
    0x6D, // "5" 5
    0x7D, // "6" 6
    0x07, // "7" 7
    0x7F, // "8" 8
    0x6F, // "9" 9
    0x77, // "A" 10
    0x7C, // "B" 11
    0x39, // "C" 12
    0x5E, // "D" 13
    0x79, // "E" 14
    0x71, // "F" 15
    0x76, // "H" 16
    0x38, // "L" 17
    0x37, // "n" 18
    0x3E, // "u" 19
    0x73, // "P" 20
    0x5C, // "o" 21
    0x40, // "-" 22
    0x80, // "." 23
    0x00  // Unknown   24
};

#endif 

unsigned char sign = 15;

// unsigned char a;
// unsigned char b;
// unsigned char c;
// unsigned char d;

void print_info()
{
	switch (my_direct)
	{
		case forward:
			sign = 15;
			break;
		case back:
			sign = 11;
			break;
		case left:
			sign = 17;
			break;
		case right:
			sign = 10;
			break;
	}
	
	if(my_model == bluetooth) Seg7Print(11, 17, 24, 24, sign, 24, 24, Compare - 1);
	else if(my_model == ir) Seg7Print(1, 10, 24, 24, sign, 24, 24, Compare - 1);
	else Seg7Print(10, 5, 24, 24, sign, 24, 24, Compare - 1);
	
		 
}

void init_dis()
{
	DisplayerInit();
    SetDisplayerArea(0, 7);
	
	SetEventCallBack(enumEventSys100mS, print_info);
}

