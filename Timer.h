#ifndef	__TIMER_H__
#define	__TIMER_H__

#define FOSC	11059200			//ʱ��Ƶ��
#define T1MS (65536-FOSC/12/1000)		//1msʱ�����װ��ֵ
																		//����12����Ƭ���Ĺ���ģʽ,��¼ʱѡ��

extern unsigned int Time_1ms;
extern unsigned int Time_1s;

void Timer0Init(void);		//Timer0��ʱ����ʼ������


#endif

