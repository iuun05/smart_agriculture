#include "allh.h"

unsigned char xdata Property_Data[2];		//���ݱ�������

char *_led_on_ = "\"sunlight\":1";
char *_led_off_ = "\"sunlight\":0";
char *_fan_on_ = "\"fan\":1";
char *_fan_off_ = "\"fan\":0";
char *_pumb_on_ ="\"pumb\":1";
char *_pumb_off_ ="\"pumb\":0";

//�����ƶ˷��͵�ָ��
void check(char *ACK_AT) {
    if (strstr(_led_on_, ACK_AT) != NULL) {
        led = 1;
    }
    if (strstr(_led_off_, ACK_AT) != NULL) {
        led = 0;
    }
    if (strstr(_fan_on_, ACK_AT) != NULL) {
        fan = 1;
    }
    if (strstr(_fan_off_, ACK_AT) != NULL) {
        fan = 0;
    }
    if (strstr(_pumb_on_, ACK_AT) != NULL) {
        pumb = 1;
    }
    if (strstr(_pumb_off_, ACK_AT) != NULL) {
        pumb = 0;
    }
}

/*****************************************************
*�������ƣ�void ESP8266_Init(void)
*�������ܣ�ESP8266������ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void ESP8266_Init(void)
{
	printf("AT+CWMODE=1\r\n");	//����WiFi����ģʽΪStationģʽ:����ESP8266ģ��ȥ�����Լ��ҵ�wifi,
															//�ֻ�Ҳ�����Լ��ҵ�wifiȻ��ʵ�����ֻ���WiFiģ���ͨ��,(�Լ���wifi�൱��һ���н�)
	while(ESP8266_Re("OK")==0)printf("AT+CWMODE=1\r\n");//����ֵ�Ƿ�ΪOK
	_DELAY_MS(300);
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_Name,WIFI_Pass);
	while(ESP8266_Re("OK")==0)printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_Name,WIFI_Pass);
	_DELAY_MS(300);
	printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\"\,\"%s\"\,0,0,\"\"\r\n",username,passwd);		//AT+MQTTUSERCFG - ���� MQTT �û�����
	while(ESP8266_Re("OK")==0)printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",username,passwd);//����ֵ�Ƿ�ΪOK
	_DELAY_MS(300);
	printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",clientId);		//���� MQTT �ͻ��� ID
	while(ESP8266_Re("OK")==0)printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",clientId);//����ֵ�Ƿ�ΪOK
	_DELAY_MS(300);
	printf("AT+MQTTCONN=0,\"%s\",%s,1\r\n",mqttHostUrl,port);	//����ָ�� MQTTЭ��
	while(ESP8266_Re("OK")==0)printf("AT+MQTTCONN=0,\"%s\",%s,1\r\n",mqttHostUrl,port);//����ֵ�Ƿ�ΪOK
	_DELAY_MS(300);
}
/*****************************************************
*�������ƣ�ESP8266_Re(char *ACK_AT)
*�������ܣ���Ӧ���źŽ��н���
*��ڲ�����void
*���ڲ�����0��Ӧ��ʧ��
					1��Ӧ��ɹ�
*****************************************************/
unsigned char ESP8266_Re(char *ACK_AT)
{		
	unsigned char xdata *ret = 0;
	unsigned char xdata i;

	_DELAY_MS(200);
	if(ACK_AT == NULL)
	{
		return 0;
	}
	else
	{
		ret = Rx_Data;
		if(ret != 0)
		{
			check(ACK_AT);																					//����ƶ��·���ָ��
			
			if(strstr((const char *)ret,(const char *)ACK_AT) != NULL)
			{	
				for(i=0;i<len;i++)
				{
					Rx_Data[i]=0;
				}
				len = 0;
				return 1;
			}
			else
			{
				for(i=0;i<len;i++)
				{
					Rx_Data[i]=0;
				}
				len = 0;
				return 0;
			}			
		}
		else
		{
			len = 0;
			return 0;
		}		
	}
}

