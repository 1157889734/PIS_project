
#ifndef  _SERIAL_BUS_H
#define  _SERIAL_BUS_H

#include "MyAll.h"


#define		IP_offset				(124)		//第一个屏 相对1号中控的ip偏移
#define		IP_resSUM				(16)		//PIS 系统中车头屏的预留ip数量
#define 		PRTCL_HEADS_LEN			 21	

#define 		 FirstCCtrl_ID					(0x01)	// 1 CCtrl ID
#define 		 FirstLED_ID					(0x01)	// 1 LED  ID

extern u8 Download_flag;


typedef struct {
	
	uint8	run_status;			 //运行状态
	uint8	software_version_1;	 //程序版本号字节1
	uint8	software_version_2;	 //程序版本号字节2
	uint8	software_version_3;	 //程序版本号字节3
	uint8	software_version_4;	 //程序版本号字节4
	
}TAG_LED_Process_Data;	    	//车厢LED过程数据?

//TAG_LED_Process_Data 	led_process_data;
//消息处理句柄
typedef void (*BH_MsgHandler_Callback)(u8* pbuf, int len ,ProtocolDeviceInfoTypeDef devInfo);

//命令处理结构体
__packed typedef struct 
{
	u16						command;		//指令
	BH_MsgHandler_Callback 	msghandler ;	//处理句柄
}TAG_MSG_TBL;


int NetControlReceiveProcess(u8* pbuf, int len); 
int NetControlSendInspection(void);

void respond_CMD_TEST_download_app(ProtocolPackTypeDef *msg);
void respond_CMD_TEST_run_iap(ProtocolPackTypeDef *msg);
void respond_CMD_TEST_set_dispMode(ProtocolPackTypeDef *msg);
void respond_CMD_TEST_debug(ProtocolPackTypeDef *msg);

void udpTest_send_set_dispMode(void *p, uint16 len);
void udpTest_send_download_app(void *p, uint16 len);
void udpTest_send_run_iap(void *p, uint16 len);

#endif











