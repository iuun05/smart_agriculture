#include "allh.h"
unsigned char xdata Rx_Data[RxDataLong];		//数据保存数组
unsigned char xdata Rx_New_Data = 0;		//获得的一个新数据
unsigned char xdata flag = 0,len = 0;


/*****************************************************
*函数名称：putchar(char c)
*函数功能：发送字符到串口
*入口参数：char c
*出口参数：c
*****************************************************/
char putchar(char c)
{
	//输出重定向到串口
	SBUF = c;
	while(TI == 0);
	TI = 0;
	return c; //返回给函数的调用者printf
}


void Uart_Init(void)
{
	SCON = 0x50 ; //串口工作方式1，8位UART，波特率可变
	T2CON = 0x34; //T2定时器模式为波特率发生器接收和发送相同波特率
	TL2 = RCAP2L = (65536-(FOSC/32/Baud)); //设置波特率低八位
	TH2 =	RCAP2H = (65536-(FOSC/32/Baud))>>8;  //设置波特率高八位

	ES = 1;		//串口开启	
	EA = 1;		//总中断开启
}

/*****************************************************
*函数名称：UART_ReceiveByte(void)
*函数功能：uart收到数据并进行数据解析
*入口参数：void
*出口参数：void
*****************************************************/
void UART_ReceiveByte(void)
{
	Rx_New_Data = SBUF;		//收到数据字节
	Rx_Data[len]	=	Rx_New_Data;	//将数据传入到数组中
	if(len>=RxDataLong-1)
	{
		len = 0;
	}
	else
	{
		len++;
	}
}



void Uart_Isr() interrupt 4 using 1
{
	if(RI)
	{
		RI = 0;	
		UART_ReceiveByte();	
	}
}



