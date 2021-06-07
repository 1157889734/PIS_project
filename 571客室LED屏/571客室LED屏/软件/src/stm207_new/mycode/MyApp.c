
//*****************************************************//
//		MyApp.c
//*****************************************************//


#include "MyAll.h"



u8 DevType;
u8 DevId;

u16 TrainId;

u16 temp_num;


int AppStartTimer;
int AppStartFlag;




void AppInit(void)
{
	AppStartTimer = 1;

	DevType = 0x09;

	DevId =0x01;

	TrainId = 0xff;

	temp_num = (DevId << 8) + DevType;
	srand(temp_num);

	get_device_id();
	
}

void AppStart(void)
{

	CommanderInit();


}



void AppProcess(void)
{

	

	


}


void App100ms(void)
{

	AppStartTimer++;

	if(AppStartTimer == 20)
	{
		AppStartFlag = 1;
		AppStart();
		
	}
	else if(AppStartTimer > 1000)
	{
		AppStartTimer = 1000;
		
	}

}


void App1000ms(void)
{

//	UdpTestSend();

//	TerminalInit();

}



int SetDeviceId(int inda)
{

	if(inda > 64)
	{
		return -1;
	}

	DevId = (u8)inda;

	StorageInfoSave();

	CommanderSendDeviceId();
	
	return 0;

}


int SetTrainId(int inda)
{

	if(inda > 65536)
	{
		return -1;
	}

	TrainId = (u16)inda;

	StorageInfoSave();

	CommanderSendTrainId();
	
	return 0;

}












