#include "allh.h"
unsigned char xdata Rx_Data[RxDataLong];		//���ݱ�������
unsigned char xdata Rx_New_Data = 0;		//��õ�һ��������
unsigned char xdata flag = 0,len = 0;


/*****************************************************
*�������ƣ�putchar(char c)
*�������ܣ������ַ�������
*��ڲ�����char c
*���ڲ�����c
*****************************************************/
char putchar(char c)
{
	//����ض��򵽴���
	SBUF = c;
	while(TI == 0);
	TI = 0;
	return c; //���ظ������ĵ�����printf
}


void Uart_Init(void)
{
	SCON = 0x50 ; //���ڹ�����ʽ1��8λUART�������ʿɱ�
	T2CON = 0x34; //T2��ʱ��ģʽΪ�����ʷ��������պͷ�����ͬ������
	TL2 = RCAP2L = (65536-(FOSC/32/Baud)); //���ò����ʵͰ�λ
	TH2 =	RCAP2H = (65536-(FOSC/32/Baud))>>8;  //���ò����ʸ߰�λ

	ES = 1;		//���ڿ���	
	EA = 1;		//���жϿ���
}

/*****************************************************
*�������ƣ�UART_ReceiveByte(void)
*�������ܣ�uart�յ����ݲ��������ݽ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UART_ReceiveByte(void)
{
	Rx_New_Data = SBUF;		//�յ������ֽ�
	Rx_Data[len]	=	Rx_New_Data;	//�����ݴ��뵽������
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



