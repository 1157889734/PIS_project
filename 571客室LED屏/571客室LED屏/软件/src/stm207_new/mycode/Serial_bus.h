
#ifndef  _SERIAL_BUS_H
#define  _SERIAL_BUS_H

#include "MyAll.h"


#define		IP_offset				(124)		//��һ���� ���1���пص�ipƫ��
#define		IP_resSUM				(16)		//PIS ϵͳ�г�ͷ����Ԥ��ip����
#define 		PRTCL_HEADS_LEN			 21	

#define 		 FirstCCtrl_ID					(0x01)	// 1 CCtrl ID
#define 		 FirstLED_ID					(0x01)	// 1 LED  ID

extern u8 Download_flag;


typedef struct {
	
	uint8	run_status;			 //����״̬
	uint8	software_version_1;	 //����汾���ֽ�1
	uint8	software_version_2;	 //����汾���ֽ�2
	uint8	software_version_3;	 //����汾���ֽ�3
	uint8	software_version_4;	 //����汾���ֽ�4
	
}TAG_LED_Process_Data;	    	//����LED���������

//TAG_LED_Process_Data 	led_process_data;
//��Ϣ������
typedef void (*BH_MsgHandler_Callback)(u8* pbuf, int len ,ProtocolDeviceInfoTypeDef devInfo);

//�����ṹ��
__packed typedef struct 
{
	u16						command;		//ָ��
	BH_MsgHandler_Callback 	msghandler ;	//������
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











