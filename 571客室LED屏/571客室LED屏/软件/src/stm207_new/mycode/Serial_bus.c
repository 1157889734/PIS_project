
#include  "MyAll.h"

TAG_LED_Process_Data		led_process_data = {RUN_STATUS_OK,LED_SW_VERSION_1,LED_SW_VERSION_2,LED_SW_VERSION_3,LED_SW_VERSION_4};

/***************************************************************************/
/*指令索引表													     */
/***************************************************************************/
static const TAG_MSG_TBL pEvt_PTU_LOCAL_LOCAL_Tbl[] = 
{
	{PRTCL_SET_DEV_IP_ADDR,					Set_ip_addr_process	    },
//	{SET_DEV_MAC_ADDR,						Set_mac_addr_process	    },
	{PRTCL_SET_IP_AUTO,						Set_ip_auto_process	    },
	{PRTCL_DOWNLOAD_LED_CONTENT,			Download_led_content_process	  },
	{PRTCL_LED_TOUCH_DISP,					led_touch_disp_process					},
	{PRTCL_SET_LED_ROLLING_SPEED,            	Set_led_roll_speed_process      },
	{PRTCL_SET_LED_WORK_MODE,				Set_led_work_mode_process},
	//{PRTCL_RETURN_LED_CONTENT,                	Return_led_content_process        },
	{PRTCL_RETURN_LED_ROLLING_SPEED,          	Return_roll_speed_process    },    
	{PRTCL_ASK_DEV_IP,                				Ask_dev_ip_process    },  
//	{RETURN_MAC,                					Return_mac_process    },  
//{PRTCL_ASK_VERSION_NUM,                		Ask_version_num_process    },  
	{NULL,										NULL				            },
};

TAG_Disp_Info netCNDispInfo, netENDispInfo;
TAG_protocol_Disp_Info tmpProtocolDispInfo;



void reset_TAG_Disp_Info(TAG_Disp_Info *p)
{
	memset(p, 0xff, sizeof(TAG_Disp_Info));
	p->dispDataLen = 0;
	p->totalPackNum = 0;
	p->currentPackNumber = 0;
	p->dispColor = 0;
	p->dispKind = 0;
}

void reset_TAG_protocol_Disp_Info(TAG_protocol_Disp_Info *p)
{
	memset(p, 0xff, sizeof(TAG_protocol_Disp_Info));
	p->totalPackNum = 0;
	p->currentPackNumber = 0;
	p->dispColor = 0;
	p->dispKind = 0;
}

void clr_dispinfo(void)
{

	reset_TAG_Disp_Info(&netCNDispInfo);
	reset_TAG_Disp_Info(&netCNDispInfo);
	reset_TAG_protocol_Disp_Info(&tmpProtocolDispInfo);
}

int NetControlReceiveProcess(u8* pbuf, int len)
{
	u16 keyword;
	u8 index;
	u8* buf;
	int length;
	
	ProtocolDeviceInfoTypeDef devInfo;
	
	pNetReceiveBuf = pbuf;
	NetReceiveBufSize = len;

	#if 0
	if(len< 21)   //数据长度必须>=21个字节
	{
		 led_process_data.run_status=RUN_STATUS_FAULT;
		return -1;

	}

       
	if(ProtocolRcvHeadCheck(pNetReceiveBuf) != 0)
	{
		 led_process_data.run_status=RUN_STATUS_FAULT;
		return -1;

	} 
	#endif
	
	keyword = ProtocolRcvGetKeyword(pNetReceiveBuf);
	index = 0;
	
	while(pEvt_PTU_LOCAL_LOCAL_Tbl[index].command != NULL)
	{
		if((keyword == pEvt_PTU_LOCAL_LOCAL_Tbl[index].command) && (pEvt_PTU_LOCAL_LOCAL_Tbl[index].msghandler != NULL))
		{
			buf=ProtocolRcvGetDataPointer(pNetReceiveBuf);
			length=ProtocolRcvGetDataLength(pNetReceiveBuf);
			devInfo=ProtocolRcvGetSrcInfo(pNetReceiveBuf);
			pEvt_PTU_LOCAL_LOCAL_Tbl[index].msghandler(buf,length,devInfo);
			break;
		}
		index++;
	}

	return 0;
}

//发送LED屏过程数据
int NetControlSendInspection(void)
{
	ProtocolSndProcessDataPack(pNetSendBuf, &NetSendBufSize, led_process_data.run_status, roll_speed, led_process_data.software_version_1, led_process_data.software_version_2, led_process_data.software_version_3, led_process_data.software_version_4);

	UdpControlSend(pNetSendBuf, NetSendBufSize);
	 
	return 0;

}

// -------------------------


typedef void (*MsgHandler_udp_TEST_recv)(ProtocolPackTypeDef *msg);

typedef struct
{
	uint16	cmd;
	MsgHandler_udp_TEST_recv	msghandler;
} TAG_Evt_udp_TEST_recv;

const TAG_Evt_udp_TEST_recv Evt_udp_TEST_recv_Tbl[] =
{

#ifdef IAP_PROG
	{CMD_TEST_download_app,		respond_CMD_TEST_download_app	},
#else
	{CMD_TEST_run_iap,			respond_CMD_TEST_run_iap		},
	{CMD_TEST_set_dispMode,		respond_CMD_TEST_set_dispMode	},
#endif
	{CMD_TEST_debug,			respond_CMD_TEST_debug		},
	{null,							NULL								}

};
void respond_CMD_TEST_debug(ProtocolPackTypeDef *msg)
{
	UdpTestSend((uint8 *)msg, msg->DataLength + sizeof(ProtocolPackTypeDef) - sizeof(ProtocolDataTypeDef));
}

void respond_CMD_TEST_run_iap(ProtocolPackTypeDef *msg)
{
	//run_iap_prog();
	set_run_iap_req(1);
}

void respond_CMD_TEST_download_app(ProtocolPackTypeDef *msg)
{
	TAG_download_app_req *p = (TAG_download_app_req *)msg->DataBuf.Buf;
	unsigned char ip[4];
	uint8 filename_len;
	filename_len = p->filename_len;

	if (filename_len == 0 || (filename_len == 255))
	{
		// 文件名最长 255
		return;
	}

	if (*(p->filename + filename_len) != '\0')
	{
		//判读文件名字符串结束符
		return;
	}

	memcpy(ip, p->ip, 4);
	tftp_cli_start(TFTP_RRQ, (char *)p->filename, MODE_OCTET, ip);
}

void respond_CMD_TEST_set_dispMode(ProtocolPackTypeDef *msg)
{
	uint8 mode;

	mode = msg->DataBuf.Buf[0];

	if (mode > 3)
	{
		mode = 0;
	}

	if (mode == ptu_SetMode)
	{
		return;
	}

	if (mode == 0)  	//正常显示模式
	{
		ptu_SetMode = mode;
		clr_led_buf();
		//clr_dispinfo();
		//set_dispmode(SCREEN_MODE_stationID);
	}
	else if (mode == 1)  	//坏点检测模式
	{
		ptu_SetMode = mode;
		clr_led_buf();
		//clr_dispinfo();
		//set_dispmode(SCREEN_MODE_test);
	}
	else if (mode == 2)  	//版本显示模式
	{
		ptu_SetMode = mode;
		clr_led_buf();
		//clr_dispinfo();
		//set_dispmode(SCREEN_MODE_softwareVersion);
	}
	else if (mode == 3)  	//静态显示模式
	{
		ptu_SetMode = mode;
		clr_led_buf();
		//clr_dispinfo();
		//set_dispmode(SCREEN_MODE_static_test);
	}
	else
	{
		return;
	}
}
int UdpTestReceiveProcess(u8 *pbuf, int len)
{
	ProtocolPackTypeDef *p = (ProtocolPackTypeDef *)pbuf;
	ProtocolHeadTypeDef *phead = (ProtocolHeadTypeDef *)pbuf;
	uint8 index;

	/*if (p->DataLength + sizeof(ProtocolPackTypeDef) - sizeof(ProtocolDataTypeDef) != len)
	{
		// 数据长度 错误
		return -1;
	}*/


	if (phead->HeadMark != 0x7E)
	{
		return -1;
	}

	if ((phead->DestInfo.DevType != DevType) && (phead->DestInfo.DevType != 0xFF))
	{
		return -1;
	}

	if ((phead->DestInfo.DevId != DevId) && (phead->DestInfo.DevId  != 0xFF))
	{
		return -1;
	}

	if ((phead->DestInfo.Ip32 != NetIp4toIp32(NetLocalIp)) && (phead->DestInfo.Ip32 != 0xFFFFFFFF) && (phead->DestInfo.Ip32 != (NetIp4toIp32(NetLocalIp) | 0x000000FF)))
	{
		return -1;
	}

#if 1

	if (phead->SrcInfo.DevType != DevType)
	{
		//不是同类设备发来的 命令，不执行
		return -1;
	}

#endif

	index = 0;

	while (Evt_udp_TEST_recv_Tbl[index].msghandler != NULL)
	{
		if (Evt_udp_TEST_recv_Tbl[index].cmd == p->KeyWord)
		{
			Evt_udp_TEST_recv_Tbl[index].msghandler(p);
			break;
		}

		index++;
	}

	return 0;
}



typedef void (*MsgHandler_udpTest_send)(void *p, uint16 len);

typedef struct
{
	uint16	cmd;
	MsgHandler_udpTest_send	msghandler;
} TAG_Evt_udpTest_send;



const TAG_Evt_udpTest_send Evt_udpTest_send_Tbl[] =
{
#ifdef IAP_PROG
	{CMD_TEST_download_app,		udpTest_send_download_app	},
#else
	{CMD_TEST_run_iap,			udpTest_send_run_iap			},
	{CMD_TEST_set_dispMode,		udpTest_send_set_dispMode	},
#endif
	{CMD_TEST_debug,			NULL						},
	{null,						NULL						}
};

void udpTest_send_process(uint16 keyword, void *p, uint16 len)
{
	uint16	index;

	index = 0;

	while (Evt_udpTest_send_Tbl[index].msghandler != NULL)
	{
		if (Evt_udpTest_send_Tbl[index].cmd == keyword)
		{
			Evt_udpTest_send_Tbl[index].msghandler(p, len);
			break;
		}

		index++;
	}
}

void read_local_info(void)
{
	ProtocolLocalInfo.DevType = DevType;
	ProtocolLocalInfo.DevId = DevId;
	ProtocolLocalInfo.TrainId = TrainId;
	ProtocolLocalInfo.Ip32 = NetIp4toIp32(NetLocalIp);

}

void pis_pack_data(ProtocolDeviceInfoTypeDef dst_info,
                   ProtocolDeviceInfoTypeDef src_info,
                   uint16 cmd,
                   uint8 *src_data, uint16 src_len,
                   uint8 *pack_data, uint16 *pack_len)
{
	ProtocolPackTypeDef *p_pack;

	p_pack = (ProtocolPackTypeDef *)pack_data;

	//head
	p_pack->Head.DestInfo = dst_info;
	p_pack->Head.SrcInfo = src_info;
	p_pack->Head.HeadMark = 0x7e;

	//cmd
	p_pack->KeyWord = cmd;

	//data
	mem_cpy((uint8 *)p_pack->DataBuf.Buf, (uint8 *) src_data, src_len);
	p_pack->DataLength = src_len;

	//length
	*pack_len = sizeof(ProtocolPackTypeDef) - DATA_MAX_SIZE + src_len;
}

void udpTest_send_download_app(void *p, uint16 len)
{
	uint16 packet_len = sizeof(ProtocolPackTypeDef) - sizeof(ProtocolDataTypeDef) +  20 + len;
	uint8 *p_buf;
	//uint8 mode = *((uint8 *)p);
	read_local_info();
	p_buf = malloc(packet_len);
	pis_pack_data(ProtocolBroadInfo, ProtocolLocalInfo, CMD_TEST_download_app, (uint8 *)p, len, p_buf, &packet_len);
	UdpTestSend(p_buf, packet_len);
	free(p_buf);
}
void udpTest_send_run_iap(void *p, uint16 len)
{
#if 0
	read_local_info();
	pis_pack_data(ProtocolBroadInfo, ProtocolLocalInfo, CMD_TEST_run_iap, NULL, NULL, pack_data, &pack_len);
	UdpTestSend(pack_data, pack_len);
#endif

	uint16 packet_len = sizeof(ProtocolPackTypeDef) - sizeof(ProtocolDataTypeDef) + 20;
	uint8 *p_buf;

	read_local_info();
	p_buf = malloc(packet_len);
	pis_pack_data(ProtocolBroadInfo, ProtocolLocalInfo, CMD_TEST_run_iap, NULL, NULL, p_buf, &packet_len);
	UdpTestSend(p_buf, packet_len);
	free(p_buf);
}
void udpTest_send_set_dispMode(void *p, uint16 len)
{
	uint16 packet_len = sizeof(ProtocolPackTypeDef) - sizeof(ProtocolDataTypeDef) + 20;
	uint8 *p_buf;
	//uint8 mode = *((uint8 *)p);
	read_local_info();
	p_buf = malloc(packet_len);
	pis_pack_data(ProtocolBroadInfo, ProtocolLocalInfo, CMD_TEST_set_dispMode, (uint8 *)p, 1, p_buf, &packet_len);
	UdpTestSend(p_buf, packet_len);
	free(p_buf);
}




