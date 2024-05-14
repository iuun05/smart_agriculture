/*********************************************************************************
* 【网    站】：	http://www.qxmcu.com/ 
* 【淘宝店铺】：	http://qxmcu.taobao.com/
* 【实验平台】：	清翔 QX-MCS51 单片机开发板
* 【外部晶振】： 	11.0592mhz	
* 【主控芯片】： 	STC89C52
* 【编译环境】： 	Keil μVisio4	
********************************************************************************/
#include <reg52.h>
#include <intrins.h>
#include "allh.h"

#define MAIN_Fosc		11059200UL	//宏定义主时钟HZ

sbit CS = P3^7;
sbit DCLK = P2^1;
sbit DIN = 	P2^0;
sbit DOUT = P2^5;
/*====================================
使用typedef给已有数据类型取别名
====================================*/
typedef unsigned char uchar;
typedef unsigned int uint;

//通道0光敏cmd：0x94  通道1热敏cmd：0xd4  通道2电位器cmd：0xa4 通道3外部输入AIN3 cmd：0xe4

/*====================================
函数	：SPI_Write(uchar DAT)
参数	：DAT需要发送的数据
返回值	：无
描述	：发送一个字节数据
====================================*/
void SPI_Write(uchar DAT)
{
	uchar i; 
	for(i=0; i<8; i++) //分别写8次，每次写1位
	{
		DCLK = 0;//拉低时钟总线，允许DIN变化
		if(DAT & 0x80)//先写数据最高位
			DIN = 1;  //写1
		else
			DIN = 0;  //写0
		DCLK = 1;	  //拉高时钟，让从机读DIN
		DAT <<= 1;	  //为发送下一位左移1位
	}
}
/*====================================
函数	：ReadByte()
参数	：无
返回值	：返回读出的数据
描述	：
====================================*/
uint SPI_Read()
{
	uchar i; 
	uint DAT;
	for(i=0; i<12; i++)//分别读12次，每次读一位
	{
		DAT <<= 1; //数据左移1位，准备接收一位
		DCLK = 1;   //拉高时钟总线，读取SDA上的数据
		DCLK = 0;   //拉低时钟总线，允许从机控制SDA变化
		if(DOUT)
			DAT |= 0X01;//为1则写1，否则不行执行写1，通过左移补0
	}
	return(DAT); //返回读出的数据
}

/*====================================
函数	：PCF8591Read(uchar cmd)
参数	：cmd XPT2046控制字节
返回值	：AD转出的数字量
描述	：读指定通道的输入的模拟量专为数字量
====================================*/
uint ReadAD(uchar cmd)
{
	uint DAT;
	CS = 0;
	SPI_Write(cmd);
	DCLK = 0;   //拉低时钟总线
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DAT = SPI_Read();
	CS = 1;
	return(DAT);//返回读出数据
			
}