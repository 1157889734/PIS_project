//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ����ͨ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: net_manager.c
//*�ļ�����: ����ͨ��
//*�ļ�����: mmaple
//*��������: 2009/7
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

//�㲥��Ƶ
#define FEP_AUDIO_LOCAL_PORT		(53152)
#define FEP_AUDIO_REMOTE_PORT	(53151)
#define FEP_AUDIO_REMOTE_IP		("192.168.101.255")

static socklen_t socklen=0;
static int cmd_socket_fd=-1;
static struct sockaddr_in localaddr,remoteaddr;


static pthread_t fep_audio_thread_id; 		//pa������·��

//***********************************************************************************************************************
//��������:�����������
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
static void*  fep_audio_thread(void* param)
{	
	uint8 cmd_recv_buf[64];//���ջ�����
	int length=0;
	
	printf("fep_audio_thread start....\r\n");
	
	
	//��SOCKET��ַ�ṹ�ĳ���
	socklen = sizeof(struct sockaddr_in);	
	//����UDP�׽���	
	cmd_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(cmd_socket_fd<0)
	{
		printf("socket creating err in udptalk\n");
		exit(1);
	}			
	//��䱾��IP�Ͷ˿�
	memset(&localaddr,0,socklen);
	localaddr.sin_family=AF_INET;
	localaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	localaddr.sin_port=htons(FEP_AUDIO_LOCAL_PORT);
	//���Է�IP�Ͷ˿�--���͵�ʱ������
	memset(&remoteaddr,0,socklen);
	remoteaddr.sin_family=AF_INET;	

	//�󶨱��ض˿�
	if(bind(cmd_socket_fd, (struct sockaddr *)&localaddr, socklen)<0)
	{	
		printf("bind local address err in udptalk!\n");
		exit(2);
	}


//�ȴ�MP3������㹻�İ����ٽ����������ֳ�ʵ��ʹ��ʱӦ�ò���Ҫ
#if 0
	while(1)
	{
		if(mp3_decoder_get_init_flag())
		{
			break;
		}
		usleep(100*1000);
		//printf("wait for mp3 init...\r\n");		
	}
	printf("mp3 init ok...\r\n"); 	
#endif	

	while(1)
	{		

		//��ȡsocket		
		length=recvfrom(cmd_socket_fd, cmd_recv_buf,sizeof(cmd_recv_buf), 0, (struct sockaddr *)&remoteaddr, &socklen);
		
		//�ж��Ƿ�������
		if(length>0)
		{
			//printf("recv fep: %d\r\n",length);
			//print_buf(cmd_recv_buf,length);
			//���ݵ�ǰ�㲥���ͣ����ò��ź���
			broadcast_send_audio();

		}
	}
	

	
}
   
   
void	fep_audio_thread_install(void)
{
	//�����߳�
	//pthread_create(&fep_audio_thread_id, NULL, (void*)fep_audio_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	ThreadCreate(&fep_audio_thread_id,  fep_audio_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	return;
}

                                          
