//*******************************************************//
//						MyAdc.h								//
//*******************************************************//

#ifndef _MYADC_H
#define  _MYADC_H

#include "MyAll.h"

#define BUFFER_NUM  250
#define BUFFER_MF_NUM  16
#define NOISE_FILTER    2050


extern int temp1,temp2;
extern int SmoothingFilterValue ;
void AdcInit(void);
u16 AdcGetValue1(void);
u16 AdcGetValue2(void);


int AdcGetFilterValue1(void);
int  AdcGetFilterValue2(void);


int AdcNewGetValue1(void);
int AdcNewGetValue2(void);

void NoiseGet3sSmoothingFilterValue(void);

u16 AdcMedianFilterValue1(void) ;
u16 AdcMedianFilterValue2(void); 





#endif


