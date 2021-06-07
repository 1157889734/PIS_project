//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ����ͨ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: net_manager.c

//*�ļ�����: ����ͨ��

//*�ļ�����: mmaple

//*��������: 2009/7
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"



//�㲥��Ƶ
#define BROADCAST_AUDIO_LOCAL_PORT		(51151)
#define BROADCAST_AUDIO_REMOTE_PORT	(51152)
//#define BROADCAST_AUDIO_REMOTE_IP		("192.168.101.108")
#define BROADCAST_AUDIO_REMOTE_IP		("192.168.101.255")
#define BROADCAST_AUDIO_REMOTE_IP_HEX		(0xc0a865ff)

//��������С
#define AUDIO_BUF_SIZE	1024

//������Ƶ������
#define AUDIO_SEND_CMD			0x0004


static socklen_t socklen=0;
static int cmd_socket_fd=-1;
static struct sockaddr_in localaddr,remoteaddr;

//��������
typedef struct
{
	uint8 broadcast_type;
	uint8 priority;
	uint8 buf[AUDIO_BUF_SIZE];
}__attribute((packed))broadcast_audio_t;


static pthread_t broadcast_audio_thread_id;



//***********************************************************************************************************************
//��������:��������
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
static void broadcast_audio_send_buf(uint8 *buf, uint16 length)
{
	uint8 send_buf_tmp[PISC_DATA_MAX_SIZE];
	uint16 send_len=0;

	//���
	pisc_pack_data(0,0xff,0xff,BROADCAST_AUDIO_REMOTE_IP_HEX,
								0,DEV_TYPE_PISC,pisc_local_get_my_dev_id(),pisc_local_get_my_dev_ip(),
								AUDIO_SEND_CMD,
								buf,length,send_buf_tmp,&send_len);

#if 0
		uint16 len_tmp=0;
		static uint32 num_tmp=0;	
		num_tmp++;
		if((num_tmp%100)==0)
		{
			printf("broadcast_audio_send_buf: %d\r\n",send_len);
			print_buf(send_buf_tmp,30);

		}
	#endif	



	
	//����
	length=sendto(cmd_socket_fd,send_buf_tmp,send_len,0,(struct sockaddr *)&remoteaddr,socklen);
}

//***********************************************************************************************************************
//��������:��������
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
void broadcast_audio_send_audio(uint8 operate_dev_type, uint8 operate_dev_id,uint8 *buf, uint16 length)
{
	broadcast_audio_t broadcast_audio;
	broadcast_audio.broadcast_type=broadcast_get_broadcast_type();
	broadcast_audio.priority=broadcast_get_pri(operate_dev_type,operate_dev_id,broadcast_get_broadcast_type());
	memcpy((uint8 *)&broadcast_audio.buf,buf,length);

	//����
	broadcast_audio_send_buf((uint8 *)&broadcast_audio,sizeof(broadcast_audio_t));
}


static void* broadcast_audio_thread(void* param)
{	
	printf("broadcast_audio_thread start....\r\n");

	int 	    yes;
	int      set;	
	
	
	//��SOCKET��ַ�ṹ�ĳ���
	socklen = sizeof(struct sockaddr_in);	
	//����UDP�׽���	
	cmd_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(cmd_socket_fd<0)
	{
		printf("socket creating err in udptalk\n");
		exit(1);
	}			
	yes = 1;
	set = setsockopt(cmd_socket_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	
	//��䱾��IP�Ͷ˿�
	memset(&localaddr,0,socklen);
	localaddr.sin_family=AF_INET;
	localaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	localaddr.sin_port=htons(BROADCAST_AUDIO_LOCAL_PORT);
	//���Է�IP�Ͷ˿�--���͵�ʱ������
	memset(&remoteaddr,0,socklen);
	remoteaddr.sin_family=AF_INET;	
	remoteaddr.sin_port=htons(BROADCAST_AUDIO_REMOTE_PORT);
	if(inet_pton(AF_INET,BROADCAST_AUDIO_REMOTE_IP,&remoteaddr.sin_addr)<=0)
	{
		printf("Wrong source IP address: %s\n",BROADCAST_AUDIO_REMOTE_IP);
		return NULL;
	}	

	//�󶨱��ض˿�
	if(bind(cmd_socket_fd, (struct sockaddr *)&localaddr, socklen)<0)
	{	
		printf("****bind local address err in udptalk, port: %d\r\n",localaddr.sin_port);
		exit(2);
	}

	while(1)
	{		
		sleep(10);
	}
	

	
}
   
   
void	broadcast_audio_thread_install(void)
{
	//�����߳�
	//pthread_create(&broadcast_audio_thread_id, NULL, (void*)broadcast_audio_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	ThreadCreate(&broadcast_audio_thread_id,  broadcast_audio_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	return;
}

