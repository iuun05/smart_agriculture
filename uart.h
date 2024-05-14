#ifndef	__UART_H__
#define	__UART_H__

#define FOSC 11059200			//ʱ��Ƶ��
#define Baud 115200			//������

#define RxDataLong 128			//�������ݳ���

extern unsigned char xdata Rx_Data[];
extern unsigned char xdata flag,len;

void Uart_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_ReceiveByte(void);
#endif
