#ifndef	__ESP8266_H__
#define	__ESP8266_H__

/*MQTT 连接参数*/
#define clientId "sensor|securemode=3\\,signmethod=hmacsha256\\,timestamp=2219|"
#define username "device_1&k0t2mPBC4MH"
#define passwd "0C398D5942BB40DA0D59C46F0EBEA81FF74589C01C90EA604BE05259EDC3B482"
#define mqttHostUrl "k0t2mPBC4MH.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define port "1883"
#define post "/sys/k0t2mPBC4MH/device_1/thing/event/property/post"
#define post_name "temperature"

#define WIFI_Name "Troublemakers"
#define WIFI_Pass "3133406129"




extern unsigned char xdata Property_Data[];		//数据保存数组
void check(char *ACK_AT);
void ESP8266_Init(void);
unsigned char ESP8266_Re(char *ACK_AT);

#endif

