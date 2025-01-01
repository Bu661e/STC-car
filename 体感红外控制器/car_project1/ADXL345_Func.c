/**********************************
****ADXL345相关数据处理.c文件******
**********************************/
#include "ADXL345_Func.h"
#include <math.h>
xdata uchar standard_Collect_ADXL345_Num[3]={30,20,10};
xdata uchar geY=0,geX=0,shiY=0,shiX=0,geZ=0,shiZ=0;//显示变量uchar(X,Y,Z轴倾斜角的高地位值 )
xdata int x0g[2],y0g[2],z0g[2],x1g,y1g,z1g;//校准时的基准值;
xdata int offX=0,offY=0,offZ=0;//初始偏移值
xdata double factorX=0,factorY=0,factorZ=0;//重力因子
xdata int dataX=0,dataY=0,dataZ=0;	//处理后的x，y，z重力加速度寄存器值
xdata uint sumY_acc=0,sumX_acc=0,sumZ_acc=0;//x，y，z重力加速度寄存器值的累加和(加速度使用)
xdata uint sumY_angle=0,sumX_angle=0,sumZ_angle=0;//x，y，z重力加速度寄存器值的累加和（角度使用）
xdata double angleX=0,angleY=0,angleZ=0;//最后计算出的x，y，z轴角度值
xdata int real_Collect_ADXL345_Num=0;//x，y，z轴加速度寄存器值得累加次数
xdata int speed=0;
xdata uchar ready=0,readyX=0,readyY=0,readyZ=0;
xdata uchar collectFlag=0;
xdata uchar geY_a,geX_a,shiY_a,shiX_a,geZ_a,shiZ_a;//X,Y,Z平均加速度的高地位值 
xdata double angleX_f=0,angleY_f=0,angleZ_f=0;//计算后可供使用的角度值
xdata uint accX_f=0,accY_f=0,accZ_f=0;//计算后可供使用的加速度值

void Get_X()
{   
	int dis_data;
    dis_data=((Buffer[1]<<8)+Buffer[0])-offX;  //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
    dataX=dis_data;			
}


void Get_Y()
{   
	int dis_data;  
    dis_data=((Buffer[3]<<8)+Buffer[2])-offY;  //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
	dataY=dis_data;
}


void Get_Z()
{     
	int dis_data;
    dis_data=((Buffer[5]<<8)+Buffer[4])-offZ;    //合成数据   
	if(dis_data<0)
		dis_data=-dis_data;
    dataZ=dis_data;
}

void Cal_XYZ()
{
	double temp_y,temp_x,temp_z;
	temp_x=((double)sumX_angle)/standard_Collect_ADXL345_Num[speed]*factorX;
	temp_y=((double)sumY_angle)/standard_Collect_ADXL345_Num[speed]*factorY;
	temp_z=((double)sumZ_angle)/standard_Collect_ADXL345_Num[speed]*factorZ;
	angleX=(double)(acos((double)((temp_x/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265); //X轴角度值
	angleY=(double)(acos((double)((temp_y/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265);  //Y轴角度值
	angleZ=(double)(acos((double)((temp_z/(sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z)))))*180/3.14159265);  //y轴角度值	
}
void ACC_XYZ(int flag)
{  
	Get_X();
	Get_Y();
	Get_Z();
	sumX_acc+=dataX;
	sumY_acc+=dataY;
	sumZ_acc+=dataZ;
	
	sumX_angle+=dataX;
	sumY_angle+=dataY;
	sumZ_angle+=dataZ;
	real_Collect_ADXL345_Num++;
    if(real_Collect_ADXL345_Num==standard_Collect_ADXL345_Num[speed])
	{
		if(flag==0)
		{
			sumX_acc=sumX_acc/standard_Collect_ADXL345_Num[speed]%256;
			sumY_acc=sumY_acc/standard_Collect_ADXL345_Num[speed]%256;
			sumZ_acc=sumZ_acc/standard_Collect_ADXL345_Num[speed]%256;
			shiX_a=sumX_acc/16;
			geX_a=sumX_acc%16;
			shiY_a=sumY_acc/16;
			geY_a=sumY_acc%16;
			shiZ_a=sumZ_acc/16;
			geZ_a=sumZ_acc%16;

		}
		if(flag==1)
		{
			int tempx,tempy,tempz;
			Cal_XYZ();
			tempx=90-(((int)(angleX*10))/10);
			tempy=90-(((int)(angleY*10))/10);
			tempz=90-(((int)(angleZ*10))/10);
			shiX=tempx/10;
			geX=tempx%10;
			shiY=tempy/10;
			geY=tempy%10;
			shiZ=tempz/10;
			geZ=tempz%10;		
		}
		//算加速度和角度
			if(flag==2)
		{	
			//加速度
			int tempx,tempy,tempz;
			sumX_acc=sumX_acc/standard_Collect_ADXL345_Num[speed]%256;
			sumY_acc=sumY_acc/standard_Collect_ADXL345_Num[speed]%256;
			sumZ_acc=sumZ_acc/standard_Collect_ADXL345_Num[speed]%256;
			accX_f=sumX_acc;
			accY_f=sumY_acc;
			accZ_f=sumZ_acc;
			shiX_a=sumX_acc/16;
			geX_a=sumX_acc%16;
			shiY_a=sumY_acc/16;
			geY_a=sumY_acc%16;
			shiZ_a=sumZ_acc/16;
			geZ_a=sumZ_acc%16;
			//角度
			Cal_XYZ();
			tempx=90-(((int)(angleX*10))/10);
			tempy=90-(((int)(angleY*10))/10);
			tempz=90-(((int)(angleZ*10))/10);
			angleX_f=tempx;
			angleY_f=tempy;
			angleZ_f=tempz;
			shiX=tempx/10;
			geX=tempx%10;
			shiY=tempy/10;
			geY=tempy%10;
			shiZ=tempz/10;
			geZ=tempz%10;		
		}
	real_Collect_ADXL345_Num=0;
	sumX_acc=0;
	sumY_acc=0;
	sumZ_acc=0;
	
	sumX_angle=0;
	sumY_angle=0;
	sumZ_angle=0;
	}
}
