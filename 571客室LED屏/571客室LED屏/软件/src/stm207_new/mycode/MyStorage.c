
//*****************************************************//
//		MyStorage.c
//*****************************************************//

#include "MyAll.h"



StorageInfoTypeDef StorageInfo;

int StorageInfoSaveFlag;



void StorageInit(void)
{

//	FlashInit();

	AT24C32_Init();

}

void StorageInfoSave(void)
{

	StorageInfoSaveFlag = 1;

}


void StorageInfoSaveProcess(void)
{
	/*static u8 a=1;
	if(a)
	{
		a = 0;
		//if(StorageInfoSaveFlag == 1)
	{
		StorageInfoSaveFlag = 0;
	
		StorageInfo.Head = 0x23;

		NetLocalIp[0] = 192;
		NetLocalIp[1] = 168;
		NetLocalIp[2] = 101;
		NetLocalIp[3] = 100;

		StorageInfo.LocalIp[0] = NetLocalIp[0];
		StorageInfo.LocalIp[1] = NetLocalIp[1];
		StorageInfo.LocalIp[2] = NetLocalIp[2];
		StorageInfo.LocalIp[3] = NetLocalIp[3];

		
	
		StorageInfo.RouterIp[0] = NetRouterIp[0];
		StorageInfo.RouterIp[1] = NetRouterIp[1];
		StorageInfo.RouterIp[2] = NetRouterIp[2];
		StorageInfo.RouterIp[3] = NetRouterIp[3];

		StorageInfo.MaskIp[0] = NetMaskIp[0];
		StorageInfo.MaskIp[1] = NetMaskIp[1];
		StorageInfo.MaskIp[2] = NetMaskIp[2];
		StorageInfo.MaskIp[3] = NetMaskIp[3];
	
		StorageInfo.DevId= DevId;		
		StorageInfo.TrainId= TrainId;

		StorageInfo.AudioVolume = AudioVolume;
		

//		FlashWrite();

		AT24C32_PageWrite(8, ((u8*)(&StorageInfo)), sizeof(StorageInfo));

		
		Delay(1000);
	return;

	} */

		
	if(StorageInfoSaveFlag == 1)
	{
		StorageInfoSaveFlag = 0;
	
		StorageInfo.Head = 0x23;

		StorageInfo.LocalIp[0] = NetLocalIp[0];
		StorageInfo.LocalIp[1] = NetLocalIp[1];
		StorageInfo.LocalIp[2] = NetLocalIp[2];
		StorageInfo.LocalIp[3] = NetLocalIp[3];

		
		StorageInfo.RouterIp[0] = NetRouterIp[0];
		StorageInfo.RouterIp[1] = NetRouterIp[1];
		StorageInfo.RouterIp[2] = NetRouterIp[2];
		StorageInfo.RouterIp[3] = NetRouterIp[3];

		StorageInfo.MaskIp[0] = NetMaskIp[0];
		StorageInfo.MaskIp[1] = NetMaskIp[1];
		StorageInfo.MaskIp[2] = NetMaskIp[2];
		StorageInfo.MaskIp[3] = NetMaskIp[3];
	
		StorageInfo.DevId= DevId;		
		StorageInfo.TrainId= TrainId;

		StorageInfo.AudioVolume = AudioVolume;
		

	//	FlashWrite();

		AT24C32_PageWrite(8, ((u8*)(&StorageInfo)), sizeof(StorageInfo));

		
		Delay(1000);
	

	}


}


void StorageInfoRead(void)
{

	AT24C32_PageRead(8, ((u8*)(&StorageInfo)), sizeof(StorageInfo));

//	FlashReadPage1();


	Delay(1000);

	if(StorageInfo.Head == 0x23)
	{
		NetLocalIp[0] = StorageInfo.LocalIp[0];
		NetLocalIp[1] = StorageInfo.LocalIp[1];
		NetLocalIp[2] = StorageInfo.LocalIp[2];
		NetLocalIp[3] = StorageInfo.LocalIp[3];

		/*NetLocalIp[0] = 192;
		NetLocalIp[1] = 168;
		NetLocalIp[2] = 101;
		NetLocalIp[3] = 100;*/

		NetRouterIp[0] = StorageInfo.RouterIp[0];
		NetRouterIp[1] = StorageInfo.RouterIp[1];
		NetRouterIp[2] = StorageInfo.RouterIp[2];
		NetRouterIp[3] = StorageInfo.RouterIp[3];

		NetMaskIp[0] = StorageInfo.MaskIp[0];
		NetMaskIp[1] = StorageInfo.MaskIp[1];
		NetMaskIp[2] = StorageInfo.MaskIp[2];
		NetMaskIp[3] = StorageInfo.MaskIp[3];


		//DevId = StorageInfo.DevId;
		TrainId = StorageInfo.TrainId;

		AudioVolume = StorageInfo.AudioVolume;


	}


}





