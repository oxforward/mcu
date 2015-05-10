#include<reg52.h>
#include<intrijs.h>
#include<stdio.h>

#define uchar unsigned char
#define uint unsigned int
sbit seg_lock = P3^7;

uchar flag, a;
uchar flag_urat, flag_time, flag_on, a, i, t0_num, ad_val;
float ad_vo;

uchar code seg_table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delay_on(uint delay_time)
{
    uint i, j;
    for(i = delay_time; i > 0; i--)
        for(j = 110; j > 0; j--);
}

void github()
{
	int git = 0;
}

void init()
{
    TMOD = 0x21;
//  SCON = 0x50;
    TH0 = (65536 - 50000) / 256;
    TL0 = (65536 - 50000) % 256;
    TH1 = 0xfd;
    Tl0 = 0xfd;
    TR1 = 1;
    ET0 = 1;
    SM0 = 1;
    SM1 = 1;
    REN = 1;
    EA = 1;
    ES = 1;

}

void display(uchar value)
{
    uchar hundred, ten, unit;
    hundred = value / 100;
    ten = value % 100 / 10;
    unit = value % 10;
    seg_lock = 1;
    P0 = seg_table[hundred];
    seg_lock = 0;
    P0 = 0xff;
    P2 = 0x7e;  //无法实现全部数码管一起亮

}
