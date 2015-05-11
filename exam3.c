/*************************************
*���ƣ��ж�ʵ��
*���ܣ�P0�������ѭ����ʾ0��8
*	   ���ж�0�����ж�1����ʱ�ֱ���P2�ڡ�P1��������ʾ0��8
*	   ��ʵ�����ʾ�����ȼ����жϵ����ȼ����������ȼ����ж��������жϸ����ȼ�
*************************************/

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code table[]={			//����������ܱ����
0xc0, 0xf9, 0xa4, 0xb0,
0x99, 0x92, 0x82, 0xf8,
0x80, 0x90, 0x88, 0x83,
0xc6, 0xa1, 0x86, 0x8e};

uchar code seg_table[]={		//����������ܱ����
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
	EX0 = 1;	//�����ⲿ�ж�0����	
	IT1 = 1;
	EX1 = 1;	//�����ⲿ�ж�1����	
//	PX0 = 0;	//�����ж����ȼ�:�����ȼ��Ŀ��Դ�ϵ����ȼ���
//	PX1	= 1;	
	PX0 = 1;	//�����ж����ȼ�:�����ȼ��Ŀ��Դ�ϵ����ȼ���
	PX1 = 0;	
	EA = 1;		//�ж��ܿ���	
}

void delay_on(uint delay_time)		//��ʱ����
{
	int i;
	int j;
	for(i=0; i<=delay_time; i++)
		for(j=0; j<=delay_time; j++);
}

void outside_stop0() interrupt 0	//�ⲿ�ж�0������
{
	int num;
	for(num=0; num<=7; num++){
		P2 = table[num];
		delay_on(280);
		P2 = 0xff;
	}
		
}

void outside_stop1() interrupt 2	//�ⲿ�ж�1�Ĵ������
{
	int num;
	for(num=0; num<=7; num++){
		P1 = table[num];
		delay_on(280);
		P1 = 0xff;
	}
		
}



