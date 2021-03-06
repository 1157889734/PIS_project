//*******************************************************//
//						MyNet.h								//
//*******************************************************//

#ifndef _MYNET_H
#define  _MYNET_H

#include "MyAll.h"

#define LED_LEN   		160        //屏的列数
#define MAX_REV_LEN         9216     //假定一条信息最大8包，一包最大1024字节

#define RUN_STATUS_OK   	0
#define RUN_STATUS_FAULT  	1
#define LED_SW_VERSION_1	1		//软件发布版1?
#define LED_SW_VERSION_2	1		//软件发布版2?
#define LED_SW_VERSION_3	19		//软件发布版3?
#define LED_SW_VERSION_4    32		//软件发布版4?

extern u8 NetDispCont[MAX_REV_LEN];      //每段信息最多50个字，每个字是32个字节
extern u16 NetDispLen;
extern u8 roll_speed;

extern u8 NetLocalMac[6];
extern u8 NetLocalIp[4];
extern u8 NetRouterIp[4];
extern u8 NetMaskIp[4];
extern u8 NetShowIp[4];


extern int NetStartingFlag;
extern int NetListenSendFlag;

extern u8* pNetReceiveBuf;
extern int NetReceiveBufSize;
extern u8 *pNetSendBuf; 
extern int NetSendBufSize;
extern u8 Color;

extern u8 work_mode;
extern u8 content_flag;


__packed typedef struct 
	
{
	u16 TrainId;	   //列车号
	u8 DevType;		   //设备类型
	u8 DevId;		   //设备编号
	u32 Ip32;		   //设备IP

}ProtocolDeviceInfoTypeDef;

	
int NetInit(void);


void NetProcess(void);

void Net50ms(void);

void Net500ms(void);



int NetSetLocalIp4(u8 ip1, u8 ip2, u8 ip3, u8 ip4);

u32 NetIp4toIp32(u8* ip4);




//int NetControlReceiveProcess(u8* pbuf, int len);

//int NetControlReceiveVolume(void);

//int NetControlSendInspection(void);

//int NetBroadcastReceiveProcess(u8* pbuf, int len);

//int NetTalkReceiveProcess(u8* pbuf, int len);

//int NetPlayclkReceiveProcess(u8* pbuf, int len);

//int NetPlayclkSendProcess(void);


extern  void  Ask_version_num_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Ask_dev_ip_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
//extern  void  Return_led_content_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);

extern  void  Set_led_roll_speed_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Set_ip_auto_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Set_mac_addr_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Set_ip_addr_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);


extern  void  led_touch_disp_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Download_led_content_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Return_roll_speed_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
extern  void  Set_led_work_mode_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info);
#endif


