//*******************************************************//
//						MyNet.h								//
//*******************************************************//

#ifndef _MYNET_H
#define  _MYNET_H

#include "MyAll.h"




extern u8 NetLocalMac[6];

extern u8 NetLocalIp[4];
extern u8 NetRouterIp[4];
extern u8 NetMaskIp[4];

extern u8 NetShowIp[4];


extern int NetStartingFlag;

extern int NetListenSendFlag;

extern u8 NetBaseIp[4];

extern u8 NetLocalBroadcastIp[4];



int NetInit(void);


void NetProcess(void);

void Net50ms(void);

void Net500ms(void);



int NetSetLocalIp4(u8 ip1, u8 ip2, u8 ip3, u8 ip4);



u32 NetIp4toIp32(u8* ip4);





int NetControlReceiveProcess(u8* pbuf, int len);

int NetControlReceiveVolume(void);

int NetControlReceiveInspection(void);

int NetControlReceiveSelfTestCmd(void);




int NetControlSendInspection(void);

int NetControlSendSelfTestState(int state);

int NetControlSendSelfTestReport(void);



int NetBroadcastReceiveProcess(u8* pbuf, int len);



int NetTalkReceiveProcess(u8* pbuf, int len);

int NetTalkSend(u8* pbuf, int len);

int NetTalkTestLeftSend(u8* pbuf, int len);
int NetTalkTestRightSend(u8* pbuf, int len);



int NetPlayclkReceiveProcess(u8* pbuf, int len);
int NetPlayclkSendProcess(void);


int NetGetBaseIp(u32 cc_ip);		//this is new for ningbo2
int NetSetBaseIp(void);		//this is new for ningbo2





#endif


