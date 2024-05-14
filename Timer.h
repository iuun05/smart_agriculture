#ifndef	__TIMER_H__
#define	__TIMER_H__

#define FOSC	11059200			//时钟频率
#define T1MS (65536-FOSC/12/1000)		//1ms时间的重装载值
																		//其中12代表单片机的工作模式,烧录时选择

extern unsigned int Time_1ms;
extern unsigned int Time_1s;

void Timer0Init(void);		//Timer0定时器初始化函数


#endif

