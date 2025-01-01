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



void init_motor()
{
	
	P4M0 = 0x3f;               
    P4M1 = 0x00;	// 推挽模式 
	
	SetEventCallBack(enumEventSys1mS, pwm);
	
	
}

void go_forward()
{
	
	P41 = 0;
	P42 = 1;	//左轮子向前
	
 	P43 = 0;
 	P44 = 1;	//右轮子向前
}

void go_back()
{
	
	P41 = 1;
	P42 = 0;	
	
 	P43 = 1;
 	P44 = 0;	
	
}

void go_left()
{
	P41 = 0;
	P42 = 0;	
	
 	P43 = 0;
 	P44 = 1;
}

void go_right()
{
	P41 = 0;
	P42 = 1;	
	
 	P43 = 0;
 	P44 = 0;
}

void stop()
{
	P41 = 0;
	P42 = 0;	
	

 	P43 = 0;
 	P44 = 0;
}


unsigned char  Bound = 10, Compare = 1; //pwm
unsigned char  Counter = 0;
enum direct my_direct = forward;

void pwm()
{
	Counter++;
	Counter %= Bound;
	
	LedPrint(Counter);
	if(Counter < Compare)
	{
		switch (my_direct)
		{
			case forward:
				go_forward();
				break;
			case back:
				go_back();
				break;
			case left:
				go_left();
				break;
			case right:
				go_right();
				break;
		}
	}
	else stop();
}


void set_compare(int cmp)
{
	Compare = cmp;
}

void set_mydirect(enum direct new_direct)
{
	my_direct = new_direct;
}
