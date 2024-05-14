#include "allh.h"

unsigned char xdata Property_Data[2];		//数据保存数组

char *_led_on_ = "\"sunlight\":1";
char *_led_off_ = "\"sunlight\":0";
char *_fan_on_ = "\"fan\":1";
char *_fan_off_ = "\"fan\":0";
char *_pumb_on_ ="\"pumb\":1";
char *_pumb_off_ ="\"pumb\":0";

//解析云端发送的指令
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
*函数名称：void ESP8266_Init(void)
*函数功能：ESP8266参数初始化
*入口参数：void
*出口参数：void
*****************************************************/
void ESP8266_Init(void)
{
	printf("AT+CWMODE=1\r\n");	//配置WiFi工作模式为Station模式:就是ESP8266模块去连接自己家的wifi,
															//手机也连接自己家的wifi然后实现了手机和WiFi模块的通信,(自己家wifi相当于一个中介)
	while(ESP8266_Re("OK")==0)printf("AT+CWMODE=1\r\n");//返回值是否为OK
	_DELAY_MS(300);
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_Name,WIFI_Pass);
	while(ESP8266_Re("OK")==0)printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_Name,WIFI_Pass);
	_DELAY_MS(300);
	printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\"\,\"%s\"\,0,0,\"\"\r\n",username,passwd);		//AT+MQTTUSERCFG - 配置 MQTT 用户属性
	while(ESP8266_Re("OK")==0)printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",username,passwd);//返回值是否为OK
	_DELAY_MS(300);
	printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",clientId);		//配置 MQTT 客户端 ID
	while(ESP8266_Re("OK")==0)printf("AT+MQTTCLIENTID=0,\"%s\"\r\n",clientId);//返回值是否为OK
	_DELAY_MS(300);
	printf("AT+MQTTCONN=0,\"%s\",%s,1\r\n",mqttHostUrl,port);	//连接指定 MQTT协议
	while(ESP8266_Re("OK")==0)printf("AT+MQTTCONN=0,\"%s\",%s,1\r\n",mqttHostUrl,port);//返回值是否为OK
	_DELAY_MS(300);
}
/*****************************************************
*函数名称：ESP8266_Re(char *ACK_AT)
*函数功能：对应答信号进行解析
*入口参数：void
*出口参数：0：应答失败
					1：应答成功
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
			check(ACK_AT);																					//检测云端下发的指令
			
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

