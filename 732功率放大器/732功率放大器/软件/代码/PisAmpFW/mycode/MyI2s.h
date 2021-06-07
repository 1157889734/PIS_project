//*******************************************************//
//						MyI2s.h								//
//*******************************************************//

#ifndef _MYI2S_H
#define  _MYI2S_H

#include "MyAll.h"


#define L3MODE_ADDR	0
#define L3MODE_DATA	1


#define DMAPLAY_PACK_SIZE	2048

#define DMALISTEN_PACK_SIZE	2048


extern int DmaPlayFlag;


void I2s2_Init(void);

void I2s2Down(void);

void I2s2Up(void);

void DmaPlay_Init(void);

void DmaPlay_Isr(void);

void DmaPlayWriteLeft(void);

void DmaPlayWriteRight(void);

void I2s2_Play(u16 inda);

void DmaPlay_Play(uint32_t Addr, uint32_t Size);

void I2s3_Init(void);

void I2s3Down(void);

void I2s3Up(void);

void DmaListen_Init(void);

void DmaListen_Isr(void);

void DmaListenUpLoadLeft(void);
void DmaListenUpLoadRight(void);

void I2sOff(void);

#endif


