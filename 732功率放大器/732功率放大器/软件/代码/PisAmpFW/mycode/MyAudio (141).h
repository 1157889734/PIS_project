//*******************************************************//
//						MyAudio.h								//
//*******************************************************//

#ifndef _MYAUDIO_H
#define  _MYAUDIO_H

#include "MyAll.h"





#define PLAY_PACK_SIZE	1024
#define PLAY_PACK_NUM	8


#define LISTEN_PACK_SIZE	1024
#define LISTEN_PACK_NUM	2



#define SPEAKER_STATE_NORMAL	0
#define SPEAKER_STATE_SHORT		1
#define SPEAKER_STATE_OPEN		2

#define  LIMITMAX    20

extern int AudioNdOffsetAim;



typedef struct 
{
	int EnableFlag;

	u8 SourceType;
	u8 SourceId;

	u8 Type;
	u16 Priority;

	
}AudioPlayInfoTypeDef;



extern AudioPlayInfoTypeDef AudioPlayInfo;



///////////////////////////////////////////////////////////


extern u8 PlayLeftFifo[PLAY_PACK_SIZE * PLAY_PACK_NUM];
extern u8* pPlayLeftFifo;
extern int PlayLeftProduceIndex;
extern int PlayLeftConsumeIndex;
extern int PlayLeftWaitFlag;		//used for clear the audio fifo automatically


extern int PlayLeftProduceByteIndex;
extern int PlayLeftConsumeByteIndex;
extern int PlayLeftBytesToWrite;
extern int PlayLeftBytesToRead;




extern u8 PlayRightFifo[PLAY_PACK_SIZE * PLAY_PACK_NUM];
extern u8* pPlayRightFifo;
extern int PlayRightProduceIndex;
extern int PlayRightConsumeIndex;
extern int PlayRightWaitFlag;		//used for clear the audio fifo automatically


/////////////////////////////////////////////////////////////


extern u8 ListenLeftFifo[LISTEN_PACK_SIZE * LISTEN_PACK_NUM];
extern u8* pListenLeftFifo;
extern int ListenLeftProduceIndex;
extern int ListenLeftConsumeIndex;

extern int ListenLeftFlag;
extern int ListenLeftEnable;


extern u8 ListenRightFifo[LISTEN_PACK_SIZE * LISTEN_PACK_NUM];
extern u8* pListenRightFifo;
extern int ListenRightProduceIndex;
extern int ListenRightConsumeIndex;

extern int ListenRightFlag;
extern int ListenRightEnable;


////////////////////////////////////////////////////////


extern int AudioVolume;
extern int AudioTreble;
extern int AudioBass;



extern int AudioFrontPlayFlag;
extern int AudioBackPlayFlag;




extern u32 PlayClock;
extern int PlayClockSendFlag;
extern int PlayClockEnable;
extern int PlayClockRcvFlag;



extern int SampleV;
extern int SampleI;
extern int SampleR;


extern int SpeakerState;


extern int EmeVolumeSetFlag;

extern int EmeAudioTestFlag;


extern int AudioUpDownFlag;


extern int AudioNdedVolume;


extern int AudioInputSampleV;
extern int AudioInputSampleI;




void AudioInit(void);

void AudioDown(void);

void AudioUp(void);

void AudioProcess(void);


void Audio10ms(void);

void Audio100ms(void);

void Audio200ms(void);

void Audio500ms(void);



int AudioWriteFrontData(u8* pbuf);

int AudioWriteBackData(u8* pbuf);

int AudioPlayLeftFifoWrite(u8* pbuf, int len);
int AudioPlayLeftFifoRead(u8* pbuf, int len);


int AudioPlayTestSinWrite(u8* pbuf);
int AudioPlayTestSin(int cmd, int frequency);
void AudioPlayTestSinProcess(void);



void AudioListenSendProcess(void);

void AudioSampleProcess(void);

void AudioSamplingV(u8* pbuf, int len);
void AudioSamplingI(u8* pbuf, int len);



int AudioSetVolume(int inda);


void EmeVolumeSet(void);
void EmeVolumeSetProcess(void);

void EmeAudioTestFlagSet(int inflag);



int AudioPlayClockSend(void);


int AudioSetNdOffset(int ndv);

int AudioSetNdOffsetProcess(void);






void AudioInputSampleProcess(void);		//new method of AudioSampleProcess()






#endif


