#include "allh.h"
unsigned int Time_1ms=0;
unsigned int Time_1s=0;

void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	
	TL0=T1MS;	
	TH0=T1MS>>8;	//给定时器赋初值，定时1ms
	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}

void Timer0() interrupt 1
{
	TL0=T1MS;	
	TH0=T1MS>>8;	//给定时器赋初值，定时1ms
	Time_1ms++;
	if(Time_1ms>=1000||temp>30)
	{
		Time_1ms=0;
		Time_1s++;
	}
}
