#include "allh.h"

#define uint unsigned int 
#define uchar unsigned char
uchar data_byte; 
sbit io=P2^2;//dht11data端接单片机的P1^0口// 
void delay0(uchar ms)
{ 
  uchar i; 
  while(ms--)                 
 for(i=0;i<100;i++); 
} 
void delay1()
{ 
  uchar i; 
  for(i=0;i<1;i++); 
} 

void start()//开始信号 
{ 
  io=1; 
  delay1(); 
  io=0; 
  delay0(25);
  io=1;    
  delay1();
  delay1(); 
  delay1(); 

} 
uchar receive_byte()//接收一个字节// 
{ 
  uchar i,temp; 
	//接收8bit的数据 
  for(i=0;i<8;i++){ 		
	//等待50us的低电平开始信号结束 
 	while(!io);
 	delay1();
	delay1(); 
 	delay1(); 
 	temp=0;
 	if(io==1) 
	 temp=1; 
    while(io);
 	data_byte<<=1;
	data_byte|=temp; 
  } 
  return data_byte; 
} 

void receive(float *p1,float *p2)//接收数据// 
{
  uchar T_H,T_L,R_H,R_L,check,num_check,i; 

  start();//开始信号// 
  io=1;
  if(!io)//判断从机是否有低电平响应信号// 
  {  
	while(!io);//判断从机发出 80us 的低电平响应信号是否结束// 
	while(io);//判断从机发出 80us 的高电平是否结束?
	R_H=receive_byte();//湿度高位 
 	R_L=receive_byte();//湿度低位 
	T_H=receive_byte();//温度高位 
	T_L=receive_byte();//温度低位 
	check=receive_byte();//校验位 
	io=0;//当最后一bit数据接完毕后
	for(i=0;i<7;i++)//差不多50us的延时 
	delay1();
	//总线由上拉电阻拉高?＝?入空闲状态 
	io=1;
	num_check=R_H+R_L+T_H+T_L; 
	//判断读到的四个数据之和是否与校验位相同 
	if(num_check==check){
		*p1 =(float)(T_H%256)+((float)T_L/256.0);
		*p2 =(float)(R_H%256)+((float)R_L/256.0);
		} 
  }
}