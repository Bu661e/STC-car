#include "STC15F2K60S2.H"
#include "sys.H"
#include "displayer.H"
#include "beep.H" 
#include "key.h"
#include "uart2.h"
#include "math.h"
#include "beep.h"
#include "ir.h"
#include "adc.h"
#include "DS1302.h"
#include "ADXL345_Func.h"
code  unsigned long SysClock=11059200;

#ifdef _displayer_H_
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71,
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9     A      B  		C 		D			E			F	*/  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80,
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
														0x00,0x08,0x40,0x01, 0x41, 0x48,0x3D,
													
							/*            (无)   下-  中-  上-  上中-  中下-    		G				*/
								/*        26    27  	 28 		29		30		31		32				*/
													0x76, 0x10, 0x0E, 0x7A, 0x38, 0x55, 0x54, 
							/*          H      I  		J 		K			L			M			N				*/
								/*        33    34  	 35 		36		37		38		39				*/	
													0x5C, 0x73, 0x67,       0x50, 0x65, 0x78, 
								/*          O      P  	Q						R			S			T						*/
								/*        40    41  	 42 				43		44		45				*/	
													0x3E, 0x1C, 0x6A, 0x64, 0x6E, 0x5A,	
								/*          U      V  	W	  	X			Y			Z					*/
								/*        46    47  	 48		 49			50     51				*/	

							/*小写abcd，从52开始*/						
													0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d,
													0x76, 0x0f, 0x0e, 0x75, 0x38, 0x37, 0x54,
													0x5c, 0x73, 0x67,         0x31, 0x49, 0x78,
													0x3e, 0x1c, 0x7e, 0x64, 0x6e, 0x59};
#endif

char KeyPressing=0;
char initing=0; //开机前需初始化
unsigned char carSpeed=0x11;
unsigned char sendBuffer[1];
unsigned char ir_command = 0x00;
													
#define THRESHOLD_ANGLE 30       // 角度变化阈值，用于判断翻转手势
#define THRESHOLD_ACCELERATION 50U //加速度变化阈值，用于判断平移手势  

													
//发送指令
void send2car(unsigned char carCommand){
			sendBuffer[0]=carCommand;
			IrPrint(sendBuffer,1);
		//	Uart2Print(sendBuffer,1);
}			

//速度调整
void speed_callback(){

	//调整速度
	if(GetAdcNavAct(enumAdcNavKeyUp) == enumKeyPress){
		carSpeed++;
		SetBeep(800,18);
	}
	if(GetAdcNavAct(enumAdcNavKeyDown) == enumKeyPress){
		carSpeed--;
		SetBeep(800,18);
	}  
	if(GetAdcNavAct(enumAdcNavKeyCenter) == enumKeyPress){
		carSpeed=0x11;
		SetBeep(800,18);
	} 
	if(carSpeed < 0x11 || carSpeed  > 0x1a){
			if(carSpeed < 0x11)carSpeed=0x11;
			if(carSpeed > 0x1a)carSpeed=0x1a;
	} 
	send2car(carSpeed);
}

//动作指令识别													
void Gesture_Recognition(){

	//静止态显示car和速度
		Seg7Print(12,10,43,26,47,carSpeed&0x0f,26,28);	

	
		//翻转
	if(accZ_f > THRESHOLD_ACCELERATION){
		
		//前后翻转（不按K1）  //前
	if(angleY_f > THRESHOLD_ANGLE  && angleX_f < THRESHOLD_ANGLE  && KeyPressing==0){
		Seg7Print(12,10,43,26,47,carSpeed&0x0f,26,15);
		ir_command=0x01;
		send2car(ir_command);
  }	
	//前后翻转（按K1）	//后
	else if(angleY_f > THRESHOLD_ANGLE  && angleX_f < THRESHOLD_ANGLE && KeyPressing==1){
		Seg7Print(12,10,43,26,47,carSpeed&0x0f,26,11);
		ir_command=0x04;
		send2car(ir_command);
  }		

	//左右翻转（不按K1）//左 
	else if(angleX_f > THRESHOLD_ANGLE && angleY_f < THRESHOLD_ANGLE && KeyPressing==0 ){
		Seg7Print(12,10,43,26,47,carSpeed&0x0f,26,37);
		ir_command=0x02;
		send2car(ir_command);
  }
	//左右翻转（按K1） //右
	else if(angleX_f > THRESHOLD_ANGLE   && angleY_f < THRESHOLD_ANGLE && KeyPressing==1){
		Seg7Print(12,10,43,26,47,carSpeed&0x0f,26,43);
		ir_command=0x03;
		send2car(ir_command);
  }	

}

}

unsigned char ir_counter=0; 
//初始化完成后每50ms识别一次手势
void my10mS_callback(){
	
	if(initing<4)return;
	if(ir_counter==5)ir_counter=0;
	
	Multiple_Read_ADXL345();//获取参数
	ACC_XYZ(2);//实时获取角度和加速度（平均值）  

	if(ir_counter==1){
	Gesture_Recognition();//识别动作
	}

	ir_counter++;
}


void myKey_callback(){

	char k;
	
	//使用K2初始化方向（3次-X，Y，Z）
	k=GetKeyAct(enumKey2);
		if(initing==3 && k == enumKeyPress ){
				Seg7Print(26,26,26,26,0,26,26,26);
				offX=(x0g[0]+x0g[1])/2;
				offY=(y0g[0]+y0g[1])/2;
				offZ=(z0g[0]+z0g[1])/2;
				factorX=(double)1000/abs(x1g-offX);
				factorY=(double)1000/abs(y1g-offY);
				factorZ=(double)1000/abs(z1g-offZ);
			  initing++;
}
		if(initing==2 && k == enumKeyPress ){	 
			Seg7Print(26,26,26,1,26,26,26,26);
			Multiple_Read_ADXL345();
			x0g[0]=(Buffer[1]<<8)+Buffer[0];
			y0g[0]=(Buffer[3]<<8)+Buffer[2];
			z1g=(Buffer[5]<<8)+Buffer[4];
			initing++;
}

	if(initing==1 && k == enumKeyPress ){ 
			Seg7Print(26,26,26,2,26,26,26,26);
			Multiple_Read_ADXL345();
			x0g[1]=(Buffer[1]<<8)+Buffer[0];
			z0g[1]=(Buffer[5]<<8)+Buffer[4];
			y1g=(Buffer[3]<<8)+Buffer[2];
			initing++;
}
	if(initing==0 && k == enumKeyPress ){
		Seg7Print(26,26,26,3,26,26,26,26);
		Multiple_Read_ADXL345();//将多个寄存器值读取到Buffer数组中
			z0g[0]=(Buffer[5]<<8)+Buffer[4];
			y0g[1]=(Buffer[3]<<8)+Buffer[2];
			x1g=(Buffer[1]<<8)+Buffer[0];
			initing++;
}

	//K1按键状态
	k=GetKeyAct(enumKey1);
	if( k == enumKeyPress ) KeyPressing=1;
	  else if( k == enumKeyRelease ) KeyPressing=0;

}


void main()
{
  DisplayerInit();  
	KeyInit();
	AdcInit(ADCexpEXT);
	Init_ADXL345();
	BeepInit();
	LedPrint(0);
	IrInit(NEC_R05d);
	SetDisplayerArea(0,7);
	Uart2Init(9600,Uart2Usedfor485);

	
  Delay(500);	                   //上电延时		
	P0M1=0x00;
  P0M0=0xff;
						
	
		//检验ADXL345芯片是否可访问						
  if(Single_Read_ADXL345(0x00)==0xE5)	     			//0——不能访问	  // 1——可访问（待机模式）
	 {												//                             2——可访问（测量模式、正常情况下）
	      Seg7Print(10, 10, 10, 10, 10, 10, 10, 1);                                   	//读出的数据为0XE5,表示时序正确, 显示“1” 
        if(Single_Read_ADXL345(0x2D)==0x08) Seg7Print(26,26,26,26,26,26,26,2);    //读出的数据为0x08 表示给345上电了，显示“2”
   }
	else   Seg7Print(10, 10, 10, 10, 10, 10, 10, 0);							    //显示“0” 

	 
	Seg7Print(26,11, 14, 15, 40, 43, 14, 26);

	Multiple_Read_ADXL345();//将多个寄存器值读取到Buffer数组中
	offX=(Buffer[1]<<8)+Buffer[0];
	offY=(Buffer[3]<<8)+Buffer[2];
	offZ=(Buffer[5]<<8)+Buffer[4];				 

	SetEventCallBack(enumEventSys10mS, my10mS_callback);
	SetEventCallBack(enumEventKey, myKey_callback);
	SetEventCallBack(enumEventNav,speed_callback);
	 MySTC_Init();	          
    while(1)                 
        { 

					MySTC_OS();    
        }      
}


