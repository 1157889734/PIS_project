
//*****************************************************//
//		MyNet.c
//*****************************************************//



/* Includes ------------------------------------------------------------------*/
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "ethernetif.h"
#include "main.h"
//#include "netconf.h"
#include <stdio.h>
#include "MyAll.h"



u8 NetLocalMac[6];

u8 NetLocalIp[4];
u8 NetRouterIp[4];
u8 NetMaskIp[4];

u8 NetShowIp[4];

u8 NetBuf[1280];

u8 *pNetSendBuf; 
int NetSendBufSize;

int NetStartingFlag;

int NetListenSendFlag;

u8 *pNetReceiveBuf;
int NetReceiveBufSize;
u16 NetDispLen;
u8 roll_speed;
u8 PackNum;
u8 Color;
u8 roll;
u8 speed;
//u8 NetDispCont[5120];
u8 NetDispCont[MAX_REV_LEN];


u8 work_mode=4;
u8 content_flag=0;
//u16 NetDispLen=32;
//u8 NetDispCont[1600]={0x00, 0x00,0x00, 0x10,0x02, 0x10,0x02, 0x20,0x02, 0x40,0x3F, 0xF8,0x00,0x00,0x00,0x00,0x7F, 0xF0,0x01,0x08,0x02,0x08,0x06,0x08,0x04,0x08,0x00,0x70,0x00,0x00,0x00,0x00};
//u8 NetDispCont[5120]={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0x24,0x10,0x22,0x60,0x21,0x80,0x26,0x41,0x39,0x32,0x02,0x04 ,0x0C,0x18,0xF0,0x60,0x13,0x80,0x10,0x60,0x10,0x18} ;
//µ˜ ‘

int NetInit()
{
	u32 temp;
	

	Delay(10000);

	NetLocalMac[0] = 0x5e;
	NetLocalMac[1] = 0x45;
	NetLocalMac[2] = 0xa2;
	NetLocalMac[3] = 0xa8;	//168
	NetLocalMac[4] = 0x65;	//101
	NetLocalMac[5] = 0x64;	//100

	NetLocalIp[0] = 192;
	NetLocalIp[1] = 168;
	NetLocalIp[2] = 101;
	//NetLocalIp[3] = 100;
	NetLocalIp[3] = 101;

	NetRouterIp[0] = 192;
	NetRouterIp[1] = 168;
	NetRouterIp[2] = 101;
	NetRouterIp[3] = 1;

	NetMaskIp[0] = 255;
	NetMaskIp[1] = 255;
	NetMaskIp[2] = 255;
	NetMaskIp[3] = 0;
	

	StorageInfoRead();


	NetLocalMac[3] = NetLocalIp[1];
	NetLocalMac[4] = NetLocalIp[2];
	NetLocalMac[5] = NetLocalIp[3];


	pNetSendBuf = NetBuf;
	
	NetStartingFlag = 1;


	Delay(10000);

	EthernetInit();

	Delay(10000);

//	temp = ETH_ReadPHYRegister(1,2);

	temp = temp;
	
//	SwitchInit();
    
	/* Initilaize the LwIP stack */
  	LwipInit();

	Delay(10000);

	ProtocolInit();

  	HttpdInit();
	

	return 0;
}


/*void NetProcess(void)
{
		
	NetPlayclkSendProcess();

}*/



void Net50ms(void)
{

	

}



void Net500ms(void)
{

	NetControlSendInspection();
	

}





u32 NetIp4toIp32(u8* ip4)
{
	u32 ip32;

	ip32 = ((*(ip4))<<24) | ((*(ip4+1))<<16) | ((*(ip4+2))<<8) | (*(ip4+3));

	return ip32;

}




int NetSetLocalIp4(u8 ip1, u8 ip2, u8 ip3, u8 ip4)
{
	
	/*if(ip1 < 128)
	{
		return -1;
	}
	if(ip1 > 247)
	{
		return -1;
	}*/
	
	
	if(ip1 > 255)
	{
		return -1;
	}

	if(ip2 > 255)
	{
		return -1;
	}
	if(ip3 > 255)
	{
		return -1;
	}
	if(ip4 > 255)
	{
		return -1;
	}

	
	NetLocalIp[0] = ip1;
	NetLocalIp[1] = ip2;
	NetLocalIp[2] = ip3;
	NetLocalIp[3] = ip4;

	
	Delay(1000);
	StorageInfoSave();
	Delay(1000);
	StorageInfoSaveProcess();
	Delay(1000);
	Delay(1000);
	

	Delay(100000);
	Delay(100000);	
	NVIC_SystemReset();
	Delay(10000);
	Delay(10000);
	

	return 0;

}

int NetSetLocalIp32(u32 ip)
{
	u8 ip1;
	u8 ip2;
	u8 ip3;
	u8 ip4;

	   
	ip1 = (u8)(ip>>24);
	ip2 = (u8)(ip>>16);
	ip3 = (u8)(ip>>8);
	ip4 = (u8)(ip);
	
	if(ip1 < 128)
	{
		return -1;
	}
	if(ip1 > 247)
	{
		return -1;
	}
	if(ip2 > 255)
	{
		return -1;
	}
	if(ip3 > 255)
	{
		return -1;
	}
	if(ip4 > 255)
	{
		return -1;
	}
	

	NetLocalIp[0] = ip1;
	NetLocalIp[1] = ip2;
	NetLocalIp[2] = ip3;
	NetLocalIp[3] = ip4;
	

	return 0;

}

//…Ë÷√IP µÿ÷∑
 void Set_ip_addr_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)	
{
	u8 ip_addr[4],i;
	u8* ppack;
	if(len<4) return;
	
	ppack = pbuf;
	
	for(i=0;i<4;i++)
	{
		ip_addr[3-i]=*(ppack+i);
	}

	NetSetLocalIp4(ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
}

//…Ë÷√macµÿ÷∑
void  Set_mac_addr_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	u8 i;
	u8* ppack;
	if(len<6) return;
	ppack = pbuf;
	//±æ…Ë±∏MACµÿ÷∑
	for(i=0;i<6;i++)
	{
		NetLocalMac[5-i] = *(ppack+i);
	}
	EthernetInit();

	Delay(10000);

	/* Initilaize the LwIP stack */
	LwipInit();

	Delay(10000);
}


//∏˘æ› ’µΩ1∫≈÷–—Îøÿ÷∆∆˜∑¢¿¥µƒπ˝≥Ã ˝æ›£¨◊‘∂Ø…Ë÷√ip,  1∫≈÷–øÿµƒip4  «2

void Set_ip_auto_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	u8 ip[4];
	//u8* ppack;
	cnt=0; 
	reset=0;
	//≈–∂œ «1∫≈÷–—Îøÿ÷∆∆˜∑¢¿¥µƒπ˝≥Ã ˝æ›
	if(info.DevType==PRTCL_DEVTYPE_CC && info.DevId==FirstCCtrl_ID)
	if(info.DevType==PRTCL_DEVTYPE_CC )
	{
		//if ((DevId - FirstLED_ID+1) > IP_resSUM) 
		if (DevId > IP_resSUM) 
		{
			//≥¨π˝‘§¡Ù ˝¡ø
			return;
		}

		ip[0] = (u8)(info.Ip32>>24);
		ip[1] = (u8)(info.Ip32>>16);
		ip[2] = (u8)(info.Ip32>>8);
		ip[3] = (u8)(info.Ip32);
		ip[3] = 2+IP_offset+ DevId-1;                // 1∫≈÷–—Îøÿ÷∆∆˜µƒip4Œ™2
		
		if ((ip[0] < 128) || (ip[0] > 247) || (ip[1] > 255) || (ip[2] > 255) || (ip[3] > 255)) {
			//‘§…Ë÷√ip≤ª∫œ∑®
			return;
		}
		
		if ((ip[0] == NetLocalIp[0])&& (ip[1] == NetLocalIp[1])&&(ip[2] == NetLocalIp[2])&&(ip[3] == NetLocalIp[3])) 
		{
			//‘§…Ëip”Î±æ…Ìipœ‡Õ¨
			if (TrainId != info.TrainId) 
			{
				TrainId = info.TrainId;
				Delay(1000);
				StorageInfoSave();
				Delay(1000);
				StorageInfoSaveProcess();
				Delay(1000);
				Delay(1000);
				//return;
			}
		}
		else 
		{
			TrainId = info.TrainId;
			NetSetLocalIp4(ip[0], ip[1], ip[2], ip[3]);
			return;
		}
	}
	
}

void Set_led_work_mode_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	//u8 ip_addr[4],i;
	u8* ppack;
	
	if(len<1) return;
	
	ppack = pbuf;
	
	work_mode=*(ppack);

}

void led_touch_disp_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
}

/*void Download_led_content_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	u8 tmp_buf[1024];
	static u16 len1 ;
	u16  tmp_len;
	u16 i;
	static u8 flag;
	//int NetDispLen;
	//u8 NetDispCont[1024];
	u8 NetType;
	u8 NetUDFlag;
	u8 StationNum;
	//u8 PackNum;
	u8 *ppack;

	ppack=pbuf;

	//ProtocolDataTypeDef* ppack;
	//ppack= (ProtocolDataTypeDef *)pbuf;
	
	tmp_len=len-4;
	
	NetType=*ppack;
	NetUDFlag=*(ppack+1);
	StationNum=*(ppack+2);
	PackNum=*(ppack+3);	
	
       if((NetType>0x11)||(NetType<0x01))
       {
		ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, PackNum,info);
		//ProtocolSndDownResponse(pNetSendBuf, &NetSendBufSize, NetType,NetUDFlag,StationNum,PackNum,info);
		UdpControlSend(pNetSendBuf, NetSendBufSize);
		return;
       }
	else
	{
		if(NetType==0x16)
		{
			if(StationNum>0x28||StationNum<0x01)
			{
				ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, PackNum,info);
				UdpControlSend(pNetSendBuf, NetSendBufSize);
				return;
			}
			
		}
		else
		{
			if(StationNum>0x64||StationNum<0x01)
			{
				ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, PackNum,info);
				UdpControlSend(pNetSendBuf, NetSendBufSize);
				return;
			}
		}
		
	}
	   
	if((NetUDFlag!=0x01)&&(NetUDFlag!=0x02))
	{
		ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, PackNum,info);
		UdpControlSend(pNetSendBuf, NetSendBufSize);
		return;
	}

	if(PackNum>0xff)
	{
		ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, PackNum,info);
		UdpControlSend(pNetSendBuf, NetSendBufSize);
		return;
	}
	
	if(PackNum==0x01)		// £”‡1 ∞¸
	{
		len1=tmp_len;
		memcpy(tmp_buf, ppack +4,len1);
		memcpy(NetDispCont, ppack +4,len1);
		flag=1;
		return;
	}					
	
	if(PackNum==0x00)	// £”‡0∞¸
	{
		
		
		//for(i=0;i<tmp_len;i++)
		//{
		//	tmp_buf[i]= *(ppack +4+i);
		//}
		
		memcpy(tmp_buf,ppack+4,tmp_len);
		
		if(flag==1)
		{
			
			
			memcpy(&NetDispCont[len1],tmp_buf,tmp_len);
			flag=0;
			NetDispLen=len1+tmp_len;
			len1=0;
		}
		else
		{
			

			memcpy(NetDispCont,tmp_buf,tmp_len);
			NetDispLen=tmp_len;
		}
		
		tmp_len=0;
	}
	
	for(i=0;i<NetDispLen;i++)
	{
		if(i%2)
		{
			ledbuf_tmp1[i/2][1] = NetDispCont[i]^0xff;	
			//ledbuf_tmp1[i/2][1] = NetDispCont[i];
		}	
		else
		{
			ledbuf_tmp1[(i/2)][0] = NetDispCont[i]^0xff;
			//ledbuf_tmp1[i/2][0] = NetDispCont[i];
		}
	} 

}*/

uint8 download_flag = 1;


//LED∆¡œ‘ æƒ⁄»›¥¶¿Ì
void Download_led_content_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
//	u8 tmp_buf[1024];
	static u16 len1 ;
	u16  tmp_len;
	u16 i;       
	static u8 current_pack = 0;
//	static u8 flag;
        
	u8 SPackNum;				//◊‹∞¸ ˝
	u8 CPackNum;				//µ±«∞∞¸
	u8 *ppack;
						// ˝æ›≤ø∑÷:◊‹∞¸ ˝°¢µ±«∞∞¸°¢—’…
	content_flag=1;
						
	//cnt=0;
	//reset=0;
	
	ppack=pbuf;
	tmp_len=len-3;

   	 SPackNum=*ppack;
	CPackNum=*(ppack+1);
	Color=*(ppack+2);
	
	if((Color!=0x01)&&(Color!=0x02)&&(Color!=0x03))
	{
		ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, CPackNum,info);
		UdpControlSend(pNetSendBuf, NetSendBufSize);
		return;
	}

	if(SPackNum>0xff||CPackNum>0xff||(SPackNum<CPackNum))
	{
		ProtocolSndShowResponse(pNetSendBuf, &NetSendBufSize, CPackNum,info);
		UdpControlSend(pNetSendBuf, NetSendBufSize);
		return;
	}
	
	//if(CPackNum!=SPackNum)
	{
		if(CPackNum == 1)    
		{
			
			memset(NetDispCont, 0, sizeof(NetDispCont));
			memset(ledbuf_tmp1, 0xff, sizeof(ledbuf_tmp1));
			download_flag = 0;
			NetDispLen = 0;
			len1 = 0;
			current_pack = 1;
		}
		
		if(current_pack == CPackNum)
		{
			//len1+=tmp_len;
			if((len1 + tmp_len) >= sizeof(NetDispCont))
			{
				SPackNum = CPackNum;
			}
			else
			{
				memcpy(&NetDispCont[len1],ppack +3,tmp_len);
				len1 += tmp_len;
				if(len1 % 2 == 1)
				{
					NetDispCont[len1]=0x00;
					len1++;
				}
				NetDispLen = len1;
				current_pack++;
			}
		}
		else
		{
			return;
		}
	}
	 	
	if(CPackNum==SPackNum)
	{
		if(NetDispLen>9216)
		{
			NetDispLen=9216;
		}

		for(i=0;i<NetDispLen;i++)
		{
			NetDispCont[i] = NetDispCont[i]^0xff  ;
		}

		memcpy(&ledbuf_tmp1[0][0],NetDispCont,NetDispLen);
		download_flag = 1;
	}
	else
	{
		return;
	}

	return;

} 

//…Ë÷√πˆ∆¡ÀŸ∂»
void Set_led_roll_speed_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{	
	//u16 speed;
	//u8 i,j;
	u8* ppack;
//	if(len>1) return;
	ppack = pbuf;
	roll_speed=*ppack;
	//roll_speed=(speed*1000)/LED_LEN;
}

//∑µªÿπˆ∆¡ÀŸ∂»
void  Return_roll_speed_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	
	ProtocolSndRollSpeedPack(pNetSendBuf, &NetSendBufSize, roll_speed,info);
	UdpControlSend(pNetSendBuf, NetSendBufSize);
} 

/* void  Return_led_content_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	ProtocolSndDispContPack(pNetSendBuf, &NetSendBufSize, * (pbuf),*( pbuf+1),*( pbuf+2),info);
	UdpControlSend(pNetSendBuf, NetSendBufSize);
}*/


//ªÿ∂¡…Ë±∏ip
 void  Ask_dev_ip_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
	ProtocolSndDevIpPack(pNetSendBuf, &NetSendBufSize, NetLocalIp[0],NetLocalIp[1],NetLocalIp[2],NetLocalIp[3],info);
	UdpControlSend(pNetSendBuf, NetSendBufSize);
}
#if 0
//ªÿ∂¡∞Ê±æ∫≈
 void Ask_version_num_process(u8* pbuf, int len,ProtocolDeviceInfoTypeDef info)
{
									         
	ProtocolSndVersionPack(pNetSendBuf, &NetSendBufSize,LED_SW_VERSION,0, info);
	UdpControlSend(pNetSendBuf, NetSendBufSize);
}
#endif



/*int NetControlReceiveVolume(void)
{
	u8 volume;

	volume = ProtocolRcvGetControlVolume(pNetReceiveBuf, NetReceiveBufSize, DevType, DevId);

	if(volume < 100)
	{
		AudioSetVolume(volume);

	}

	return 0;

}*/


/*int NetControlSendInspection(void)
{
	u8 priority;

	if(AudioPlayInfo.EnableFlag > 0)
	{
		priority = AudioPlayInfo.Priority;

	}
	else
	{
		priority = 255;

	}

	ProtocolSndGetInspectionPack(pNetSendBuf, &NetSendBufSize, priority, 0);

	UdpControlSend(pNetSendBuf, NetSendBufSize);


	return 0;

}*/


////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

/*int NetBroadcastReceiveProcess(u8* pbuf, int len)
{
	u32 keyword;
	u8 source_type;
	u8 source_id;

	ProtocolAudioDataTypeDef * pda;


	pNetReceiveBuf = pbuf;
	NetReceiveBufSize = len;


	if(len < 1024)
	{
		return -1;

	}

	if(ProtocolRcvHeadCheck(pNetReceiveBuf) != 0)
	{
		return -1;

	}

	keyword = ProtocolRcvGetKeyword(pNetReceiveBuf);
	source_type = ProtocolRcvGetSrcDevType(pNetReceiveBuf);
	source_id = ProtocolRcvGetSrcDevId(pNetReceiveBuf);
	

	if(keyword == PRTCL_KEYWORD_BROADCAST)
	{

	
		pda = (ProtocolAudioDataTypeDef*)(ProtocolRcvGetDataPointer(pNetReceiveBuf));

		if(AudioPlayInfo.EnableFlag < 1)
		{
			AudioPlayInfo.EnableFlag = 10;
			AudioPlayInfo.SourceType = source_type;
			AudioPlayInfo.SourceId = source_id;
			AudioPlayInfo.Priority = pda->Priority;
			
			AudioWriteFrontData((u8*)(&(pda->DaBuf)));

		}
		else
		{
			if(pda->Priority < AudioPlayInfo.Priority)
			{
				AudioPlayInfo.EnableFlag = 10;
				AudioPlayInfo.SourceType = source_type;
				AudioPlayInfo.SourceId = source_id;
				AudioPlayInfo.Priority = pda->Priority;
			
				AudioWriteFrontData((u8*)(&(pda->DaBuf)));
			
			}
			else if(pda->Priority == AudioPlayInfo.Priority)
			{
				if((AudioPlayInfo.SourceType == source_type) && (AudioPlayInfo.SourceId == source_id))
				{
					AudioPlayInfo.EnableFlag = 10;
				
					AudioWriteFrontData((u8*)(&(pda->DaBuf)));
					
				}

			}

		}

	}



	return 0;
	
} */


/*int NetBroadcastSendProcess(void)
{


	return 0;

}


int NetTalkReceiveProcess(u8* pbuf, int len)
{



	return 0;


}


int NetTalkSend(u8* pbuf, int len)
{



	return 0;


}



int NetPlayclkReceiveProcess(u8* pbuf, int len)
{

	u32 keyword;
	u8 src_id;

	pNetReceiveBuf = pbuf;
	NetReceiveBufSize = len;

	if(ProtocolRcvHeadCheck(pNetReceiveBuf) != 0)
	{
		return -1;

	}

	keyword = ProtocolRcvGetKeyword(pNetReceiveBuf);
	if(keyword == PRTCL_KEYWORD_PLAYCLK)
	{
		src_id = ProtocolRcvGetSrcDevId(pNetReceiveBuf);

		if(src_id < DevId)
		{
//			PlayClockRcvFlag ++;
//			if(PlayClockRcvFlag > 72)
			{
//				PlayClockRcvFlag = 72;
			}

		}
		
	
	}


	return 0;

}



int NetPlayclkSendProcess(void)
{

	if(PlayClockSendFlag == 1)
	{
	
		ProtocolSndGetPlayclkPack(pNetSendBuf, &NetSendBufSize, PlayClock);


		UdpPlayclkSend(pNetSendBuf, NetSendBufSize);	
		
		PlayClockSendFlag = 0;


	}
	
	return 0;

}
*/












