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


int code tempdata[] = {239, 197, 175, 160, 150, 142, 135, 129, 124, 120, 116, 113, 109, 107, 104, 101,
                       99, 97, 95, 93, 91, 90, 88, 86, 85, 84, 82, 81, 80, 78, 77, 76,
                       75, 74, 73, 72, 71, 70, 69, 68, 67, 67, 66, 65, 64, 63, 63, 62,
                       61, 61, 60, 59, 58, 58, 57, 57, 56, 55, 55, 54, 54, 53, 52, 52,
                       51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44,
                       43, 43, 42, 42, 41, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37,
                       36, 36, 36, 35, 35, 34, 34, 34, 33, 33, 32, 32, 32, 31, 31, 31,
                       30, 30, 29, 29, 29, 28, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25,
                       24, 24, 24, 23, 23, 23, 22, 22, 22, 21, 21, 21, 20, 20, 20, 19,
                       19, 19, 18, 18, 18, 17, 17, 16, 16, 16, 15, 15, 15, 14, 14, 14,
                       13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 9, 9, 9, 8, 8, 8, 7,
                       7, 7, 6, 6, 5, 5, 54, 4, 3, 3, 3, 2, 2, 1, 1, 1, 0, 0, -1, -1, -1,
                       -2, -2, -3, -3, -4, -4, -5, -5, -6, -6, -7, -7, -8, -8, -9, -9,
                       -10, -10, -11, -11, -12, -13, -13, -14, -14, -15, -16, -16, -17,
                       -18, -19, -19, -20, -21, -22, -23, -24, -25, -26, -27, -28, -29,
                       -30, -32, -33, -35, -36, -38, -40, -43, -46, -50, -55, -63, 361};

struct_ADC temp;
int sum = 0, countdown = 100;
unsigned char buffer_adc[2] = {0, 0}; //�� ��

void calc_temp_and_light()
{
    temp = GetADC();
	buffer_adc[1] = temp.Rop;
    if (countdown)
    {
        countdown--;
        sum += temp.Rt >> 2;
    }
    else
    {
        sum = tempdata[sum / 100];
		buffer_adc[0] = sum;
		
        sum = 0;
        countdown = 100;
    }
}



void init_light()
{
	AdcInit(ADCexpEXT);
	SetEventCallBack(enumEventSys10mS, calc_temp_and_light);
}

