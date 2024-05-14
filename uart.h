#ifndef	__UART_H__
#define	__UART_H__

#define FOSC 11059200			//时钟频率
#define Baud 115200			//波特率

#define RxDataLong 128			//接收数据长度

extern unsigned char xdata Rx_Data[];
extern unsigned char xdata flag,len;

void Uart_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_ReceiveByte(void);
#endif
