//*******************************************************//
//						MyProtocol.h								//
//*******************************************************//

#ifndef _MYPROTOCOL_H
#define  _MYPROTOCOL_H

#include "MyAll.h"


#define PRTCL_SET_DEV_IP_ADDR					0x0101
#define PRTCL_SET_LED_MAC_ADDR				0x0130
#define PRTCL_SET_LED_WORK_MODE				0x010e
#define PRTCL_DOWNLOAD_LED_CONTENT			0x0009
#define PRTCL_SET_LED_ROLLING_SPEED              	0x010d       	 //
#define PRTCL_RETURN_LED_CONTENT				0x0220
#define PRTCL_RETURN_LED_ROLLING_SPEED		0x030d		//
#define PRTCL_DOWNLOAD_FEEDBACK				0x0402
#define PRTCL_SHOW_FEEDBACK					0x0403
#define PRTCL_RETURN_DEV_IP					0x0301
#define PRTCL_RETURN_MAC						0x0301
#define PRTCL_RETURN_VERSION_NUM  			0x0333		//
#define PRTCL_ASK_VERSION_NUM  				0x0233		//
#define PRTCL_ASK_DEV_IP						0x0201
#define PRTCL_SET_IP_AUTO						0x0001
#define PRTCL_LED_TOUCH_DISP 					0x0008
#define PRTCL_PROCESS_DATA          				0x0001   //LED屏过程数据


#define PRTCL_DEVTYPE_CC			0x01		//Center Controller
#define PRTCL_DEVTYPE_DCP	 		0x02		//Control Box
#define PRTCL_DEVTYPE_VIFU 			0x03		//Vehicle Interface Unit
#define PRTCL_DEVTYPE_RECON	 	0x04		//Reconnect Unit
#define PRTCL_DEVTYPE_RECORDER	0x05
#define PRTCL_DEVTYPE_RESERVE		0x06
#define PRTCL_DEVTYPE_DMP			0x07		//Dynamic Map
#define PRTCL_DEVTYPE_EHP			0x08		//Emergency Help Point
#define PRTCL_DEVTYPE_CLED			0x09		//Carriage LED
#define PRTCL_DEVTYPE_LLED			0x0A		//Locomotive LED
#define PRTCL_DEVTYPE_AMP			0x0B		//Amplifier
#define PRTCL_DEVTYPE_SWITCH		0x0C
#define PRTCL_DEVTYPE_PTU			0x0D


#define PRTCL_KEYWORD_INSPECTION		0x0001
#define PRTCL_KEYWORD_VOLUME			0x0002
#define PRTCL_KEYWORD_PLAYCLK			0x0003

#define PRTCL_KEYWORD_BROADCAST		0x0004
#define PRTCL_KEYWORD_TALK_DD			0x0005
#define PRTCL_KEYWORD_TALK_DC			0x0005
//控制
#define Ctrl_KEYWORD_ProcessData				0x0001


//返回
#define FeedBack_KEYWORD_ip_mac_id				0x0301
#define FeedBack_KEYWORD_softwareVersion		0x0333

//设置
#define Set_KEYWORD_mac						0x0130
#define Set_KEYWORD_IP						0x0101


//回读
#define Get_KEYWORD_ip_mac_id				0x0201
#define Get_KEYWORD_softwareVersion		0x0233


#define	DATA_MAX_SIZE	1056

/*__packed typedef struct 
{
	u16 TrainId;	   //列车号
	u8 DevType;		   //设备类型
	u8 DevId;		   //设备编号
	u32 Ip32;		   //设备IP

}ProtocolDeviceInfoTypeDef;*/


extern ProtocolDeviceInfoTypeDef ProtocolLocalInfo;
extern ProtocolDeviceInfoTypeDef ProtocolBroadInfo;

__packed typedef struct 
{
	u8 HeadMark;

	ProtocolDeviceInfoTypeDef DestInfo;

	ProtocolDeviceInfoTypeDef SrcInfo;

}ProtocolHeadTypeDef;


__packed typedef struct 
{
	u8 Buf[1280];

	
}ProtocolDataTypeDef;



__packed typedef struct 
{

	ProtocolHeadTypeDef Head;

	u16 KeyWord;

	u16 DataLength;

	ProtocolDataTypeDef DataBuf;

	
}ProtocolPackTypeDef;




/*__packed typedef struct 
{

	u8 Priority;

	u8 DaBuf[1024];

	
}ProtocolAudioDataTypeDef;



__packed typedef struct 
{

	u8 Others[5];

	u8 Amp[16];

	u8 EhpPhone;
	u8 EhpSpeaker;

	u8 Dva;

	u8 Reserve[6];

	
}ProtocolControlVolumeTypeDef;
*/




int ProtocolInit(void);


int ProtocolRcvHeadCheck(u8* pbuf);


u8 ProtocolRcvGetSrcDevType(u8* pbuf);

u8 ProtocolRcvGetSrcDevId(u8* pbuf);

u8 ProtocolRcvGetSrcStation(u8* pbuf);


u16 ProtocolRcvGetKeyword(u8* pbuf);

int ProtocolRcvGetDataLength(u8* pbuf);

u8* ProtocolRcvGetDataPointer(u8* pbuf);

u8 ProtocolRcvGetControlVolume(u8* pbuf, int len, u8 dev_type, u8 dev_id );

//新增
ProtocolDeviceInfoTypeDef ProtocolRcvGetSrcInfo(u8* pbuf);

ProtocolHeadTypeDef ProtocolHeadMake(ProtocolDeviceInfoTypeDef remote_info);


int ProtocolSndGetInspectionPack(u8 * pbuf, int * plen, u8 priority, u8 state);

int ProtocolSndGetLocalIpPack(u8* pbuf, int* plen, u32 localip);

int ProtocolSndGetDevIdPack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetLinePack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetStationPack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetAreaPack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetPlayclkPack(u8* pbuf, int* plen, u32 inda);

int ProtocolSndGetVolumePack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetTreblePack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetBassPack(u8* pbuf, int* plen, u8 inda);

int ProtocolSndGetAudioListenPack(u8* pbuf, int* plen, u8* inbuf, int inlen);

int ProtocolSndVersionPack(u8 * pbuf, int * plen,int data1, int data2,ProtocolDeviceInfoTypeDef info);
int  ProtocolSndDownResponse(u8 * pbuf, int * plen,int data1, int data2,int data3, int data4,ProtocolDeviceInfoTypeDef info);
int  ProtocolSndShowResponse(u8 * pbuf, int * plen,int data,ProtocolDeviceInfoTypeDef info);
int ProtocolSndDispContPack(u8 * pbuf, int * plen,int data1, int data2,int data3, ProtocolDeviceInfoTypeDef info);
int ProtocolSndRollSpeedPack(u8 * pbuf, int * plen,int data, ProtocolDeviceInfoTypeDef info);
int ProtocolSndProcessDataPack(u8* pbuf, int* plen, u8 state,u8 speed,u8 version_1,u8 version_2,u8 version_3,u8 version_4);
int ProtocolSndDevIpPack(u8 * pbuf, int * plen,int data1, int data2,int data3, int data4,ProtocolDeviceInfoTypeDef info);

#endif 

