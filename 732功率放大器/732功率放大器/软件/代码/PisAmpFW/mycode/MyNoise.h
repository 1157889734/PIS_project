//*******************************************************//
//						MyNoise.h								//
//*******************************************************//

#ifndef _MYNOISE_H
#define  _MYNOISE_H

#include "MyAll.h"



extern int Noise1Value;
extern int Noise2Value;

extern int Noise1DB;
extern int Noise2DB;

extern int NoiseDB;

extern int NoiseMode;







void NoiseInit(void);




void Noise10ms(void);
void Noise25ms(void);

void Noise100ms(void);

void Noise1000ms(void);

int NoiseGetDB(int adv);

int NoiseGetMyDB(void);

int NoiseCalculateOtherDB(int noise_db, int noise_mydb);


extern u32 Noise1Buf[SAMPLE_NUM];
extern u32 Noise2Buf[SAMPLE_NUM];



int NoiseNewProsess(void);

int NoiseNewGetMyDB(void);

//int Noise1Buf[SAMPLE_NUM];
//int Noise2Buf[SAMPLE_NUM];

extern int MyNoise1SampleFlag ;




#endif


