#include "allh.h"
unsigned int Time_1ms=0;
unsigned int Time_1s=0;

void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	
	TL0=T1MS;	
	TH0=T1MS>>8;	//����ʱ������ֵ����ʱ1ms
	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}

void Timer0() interrupt 1
{
	TL0=T1MS;	
	TH0=T1MS>>8;	//����ʱ������ֵ����ʱ1ms
	Time_1ms++;
	if(Time_1ms>=1000||temp>30)
	{
		Time_1ms=0;
		Time_1s++;
	}
}
