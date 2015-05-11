/*************************************
*名称：中断实验
*功能：P0口数码管循环显示0～8
*	   外中断0、外中断1发生时分别在P2口、P1口依次显示0～8
*	   过实验可演示高优先级可中断低优先级，但低优先级的中断请求不能中断高优先级
*************************************/

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code table[]={			//共阳极数码管编码表
0xc0, 0xf9, 0xa4, 0xb0,
0x99, 0x92, 0x82, 0xf8,
0x80, 0x90, 0x88, 0x83,
0xc6, 0xa1, 0x86, 0x8e};

uchar code seg_table[]={		//共阴极数码管编码表
0x3f, 0x06, 0x5b, 0x4f,
0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71};

void stop_init();
void delay_on(uint delay_time);

void main()
{
	stop_init();	
	while(1){
		int num;
		for(num=0; num<=7; num++){
			P0 = table[num];
			delay_on(280);
			P0 = 0xff;
		}
	}
}

void stop_init()
{
	IT0 = 1;
	EX0 = 1;	//允许外部中断0开关	
	IT1 = 1;
	EX1 = 1;	//允许外部中断1开关	
//	PX0 = 0;	//设置中断优先级:高优先级的可以打断低优先级的
//	PX1	= 1;	
	PX0 = 1;	//设置中断优先级:高优先级的可以打断低优先级的
	PX1 = 0;	
	EA = 1;		//中断总开关	
}

void delay_on(uint delay_time)		//延时函数
{
	int i;
	int j;
	for(i=0; i<=delay_time; i++)
		for(j=0; j<=delay_time; j++);
}

void outside_stop0() interrupt 0	//外部中断0处理函数
{
	int num;
	for(num=0; num<=7; num++){
		P2 = table[num];
		delay_on(280);
		P2 = 0xff;
	}
		
}

void outside_stop1() interrupt 2	//外部中断1的处理程序
{
	int num;
	for(num=0; num<=7; num++){
		P1 = table[num];
		delay_on(280);
		P1 = 0xff;
	}
		
}



