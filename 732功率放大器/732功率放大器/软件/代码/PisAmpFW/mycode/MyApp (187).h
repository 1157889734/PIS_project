//*******************************************************//
//						MyApp.h								//
//*******************************************************//

#ifndef _MYAPP_H
#define  _MYAPP_H

#include "MyAll.h"




#define AMPSTATE_OK			0
#define AMPSTATE_OVP			1
#define AMPSTATE_UVP			2
#define AMPSTATE_SHORT		3
#define AMPSTATE_ERR			4


#define NDSTATE_NULL			0
#define NDSTATE_ONLY1		1
#define NDSTATE_ONLY2		2
#define NDSTATE_BOTH			3




extern u8 DevType;
extern u8 DevId;

extern u16 TrainId;


extern int AppStartTimer;
extern int AppStartFlag;


extern u8 Addr;

extern int AmpState;

extern int DC24V1State;
extern int DC24V2State;


extern int NoiseDetectState;

extern u8 CurrentState;

extern u8 AppVersion1;
extern u8 AppVersion2;
extern u8 AppVersion3;
extern u8 AppVersion4;





void AppInit(void);

void AppOff(void);

void AppStart(void);


void AppProcess(void);


void App10ms(void);

void App100ms(void);

void App1000ms(void);



int SetDeviceId(int inda);

int SetTrainId(int inda);


void DisplayDb(void);

void LedLight(int num, int brightness);

int LedGetBrightness(int num);


void LedLightProcess(void);



int GetAmpState(void);


void GetDC24Vs(void);

void GetNoiseDetectState(void);


void GetCurrentState(void);








#endif


