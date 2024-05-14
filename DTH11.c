#include "allh.h"

#define uint unsigned int 
#define uchar unsigned char
uchar data_byte; 
sbit io=P2^2;//dht11data�˽ӵ�Ƭ����P1^0��// 
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

void start()//��ʼ�ź� 
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
uchar receive_byte()//����һ���ֽ�// 
{ 
  uchar i,temp; 
	//����8bit������ 
  for(i=0;i<8;i++){ 		
	//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ��� 
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

void receive(float *p1,float *p2)//��������// 
{
  uchar T_H,T_L,R_H,R_L,check,num_check,i; 

  start();//��ʼ�ź�// 
  io=1;
  if(!io)//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź�// 
  {  
	while(!io);//�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����// 
	while(io);//�жϴӻ����� 80us �ĸߵ�ƽ�Ƿ����?
	R_H=receive_byte();//ʪ�ȸ�λ 
 	R_L=receive_byte();//ʪ�ȵ�λ 
	T_H=receive_byte();//�¶ȸ�λ 
	T_L=receive_byte();//�¶ȵ�λ 
	check=receive_byte();//У��λ 
	io=0;//�����һbit���ݽ���Ϻ�
	for(i=0;i<7;i++)//���50us����ʱ 
	delay1();
	//������������������?��?�����״̬ 
	io=1;
	num_check=R_H+R_L+T_H+T_L; 
	//�ж϶������ĸ�����֮���Ƿ���У��λ��ͬ 
	if(num_check==check){
		*p1 =(float)(T_H%256)+((float)T_L/256.0);
		*p2 =(float)(R_H%256)+((float)R_L/256.0);
		} 
  }
}