#include "allh.h"



//Ĭ��ֵ
unsigned char max_co2=800;
unsigned char	max_hum=80;
unsigned char	max_tvoc=100;
unsigned char	max_vol=2000;
unsigned char	max_soil=2000;
unsigned char	max_temp=30;

unsigned char fan_=0,led_=0,pumb_=0;
float xdata temp,hum;
unsigned int xdata voltage,co2,tvoc,soil;		//���������ѹֵ
unsigned long data sgp30_dat;
unsigned char user= 1;											//Ĭ���Զ������Զ�����
unsigned char cnt = 0;
unsigned char state = 0;
unsigned char a = 0;



void control(unsigned char user){
			if(user){
			//�к������࣬ʪ�ȹ��ߣ������ŷ���
			if(co2>max_co2||tvoc>max_tvoc||hum>max_hum){
				fan=1;
				fan_=1;
			}
			else{
				fan=0;
				fan_=0;
			}
			
			//���չ��ͣ������յ�
			if(voltage>max_vol){
				led=1;
				led_=1;
			}
			else{
				led=0;
				led_=0;
			}
			
			//����ʪ�ȹ��ͣ�����ˮ��
			if(soil>max_soil){
				pumb_=0;
				pumb=1;
			}
			else{
				pumb=1;
				pumb_=0;
			}
		}
}


void init(){
	Uart_Init();
	fan=0;
	led=0;
	pumb=1;
	SGP30_Init();   //��ʼ��SGP30
	do{
		SGP30_Write(0x20,0x08);	
		sgp30_dat = SGP30_Read();//��ȡSGP30��ֵ
		co2  =(sgp30_dat & 0xffff0000) >> 16;//ȡ��CO2Ũ��ֵ
		tvoc =sgp30_dat & 0x0000ffff;       //ȡ��TVOCֵ
		Delay(2);
	}while(co2 == 400 && tvoc == 0);
	ESP8266_Init();
}



void main()
{
	Delay(2);
	init();
	cnt = 0;
		while(1)
	{
		//��ʪ��ת��ģ��
		Delay(8);
		receive(&temp,&hum);//��������// 
		Delay(8);
		
		//���������ȡģ��
		voltage = ReadAD(0x94) & 0xFFF;	//ͨ��0����cmd��0x94  ͨ��1�-���cmd��0xd4  ͨ��2��λ��cmd��0xa4 ͨ��3�ⲿ����AIN3 cmd��0xe4
		Delay(8);
		
		//soil = (ReadAD(0xe4)-16838)/50000;
		soil = ReadAD(0xe4) & 0xFFF;
		Delay(6);
		
		//�����ȡ
		SGP30_Write(0x20,0x08);
		sgp30_dat = (unsigned long)SGP30_Read();//��ȡSGP30��ֵ
		co2  =(sgp30_dat & 0xffff0000) >> 16;//ȡ��CO2Ũ��ֵ
		tvoc =sgp30_dat & 0x0000ffff;       //ȡ��TVOCֵ
		control(user);
		printf("AT+MQTTPUB=0,\"/sys/k0t2mPBC4MH/device_1/thing/event/property/post\",\"{\\\"params\\\":{\\\"temperature\\\":%.1f\\,\\\"Humidity\\\":%.1f\\,\\\"co2\\\":%d\\,\\\"tvoc\\\":%d\\,\\\"LightLux\\\":%d\\,\\\"soil\\\":%d}}\",1,0\r\n",temp,hum,co2,tvoc,voltage,soil);
		Delay(6);
		cnt++;
	}
}



