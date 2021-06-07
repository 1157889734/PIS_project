//*******************************************************//
//						MyTimer.h								//
//*******************************************************//

#ifndef _MYTIMER_H
#define  _MYTIMER_H

#include "MyAll.h"

#define CNT_10US  1
#define CNT_250US  25

#define CNT_10MS 10
#define CNT_20MS 20
#define CNT_25MS 25

#define CNT_50MS 50
#define CNT_100MS 100
#define CNT_200MS 200
#define CNT_500MS 500

#define CNT_1000MS 1000
#define CNT_2000MS 2000
#define CNT_3000MS 3000
#define SAMPLE_NUM 25

extern int MyTmCnt10us;
extern int MyTmCnt250us;
extern int MyTmCnt10ms;
extern int MyTmCnt20ms;
extern int MyTmCnt25ms;
extern int MyTmCnt50ms;
extern int MyTmCnt100ms;
extern int MyTmCnt200ms;
extern int MyTmCnt500ms;
extern int MyTmCnt1000ms;
extern int MyTmCnt2000ms;
extern int MyTmCnt5000ms;
extern int MyNoiseSampleFlag;

extern void SysTick_Init(void);
extern void SysTick_Isr(void);

void TimerOff(void);

extern void Timer1_Init(void);
extern void Timer1_Isr(void);


extern void MyTimer10(void);
extern void MyTimer20(void);
extern void MyTimer25(void);

extern void MyTimer50(void);
extern void MyTimer100(void);
extern void MyTimer200(void);
extern void MyTimer500(void);
extern void MyTimer1000(void);
extern void MyTimer2000(void);
extern void MyTimer250us(void);

 

#endif
