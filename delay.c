#include "delay.h"
#include "intrins.h"
/*
		延时函数
		500ms per
*/

void Delay(unsigned char xms)
{
	unsigned char data i, j,k;
	while(xms--)
	{

		_nop_();
		i = 4;
		j = 129;
		k = 119;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}

void _DELAY_MS(unsigned char ms)           
{
	unsigned char data i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}


void _DELAY_US(unsigned char n)
{
    while(--n);
}
