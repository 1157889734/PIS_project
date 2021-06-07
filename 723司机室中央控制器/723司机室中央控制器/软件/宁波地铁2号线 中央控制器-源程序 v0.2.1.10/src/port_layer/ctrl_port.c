//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ����ͨ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: net_manager.c

//*�ļ�����: ����ͨ��

//*�ļ�����: mmaple

//*��������: 2009/7
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

//�㲥��Ƶ
#define RECV_CTRL_LOCAL_PORT		(50152)
#define CTRL_REMOTE_PORT	(50152)
#define CTRL_REMOTE_IP		("192.168.101.255")
//#define CTRL_REMOTE_IP_HEX		(0xff65a8c0)
#define CTRL_REMOTE_IP_HEX		(0xc0a865ff)

//����ʱ�ı��ض˿ں�
#define SEND_CTRL_LOCAL_PORT		(50151)



static socklen_t socklen=0;
static int cmd_socket_fd=-1;
//static struct sockaddr_in localaddr,remoteaddr;


static socklen_t send_socklen=0;
static int send_cmd_socket_fd=-1;
static struct sockaddr_in send_localaddr,send_remoteaddr;


static pthread_t ctrl_port_thread_id;

//***********************************************************************************************************************
//��������:���������ܷ�������
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
static void ctrl_port_send_data(uint8 *buf, uint16 length)
{
	send_remoteaddr.sin_port=htons(CTRL_REMOTE_PORT);
	if(inet_pton(AF_INET,CTRL_REMOTE_IP,&send_remoteaddr.sin_addr)<=0)
	{
		printf("Wrong source IP address: %s\n",CTRL_REMOTE_IP);
		return;
	}
	//printf("ctrl_port_send_data:\r\n");
	//print_buf(buf,length);
	//����
	sendto(send_cmd_socket_fd,buf,length,0,(struct sockaddr *)&send_remoteaddr,send_socklen);
}

//***********************************************************************************************************************
//��������:
//����˵��:
//ע������:
//����˵��:
//***********************************************************************************************************************
void ctrl_port_send_cmd(uint16 dst_train_id, uint8 dst_dev_type, uint8 dst_dev_id,uint16 cmd, uint8 *buf, uint16 len)
{
	uint8 send_buf_tmp[PISC_DATA_MAX_SIZE];
	uint16 send_len=0;

	//���
	pisc_pack_data(dst_train_id,dst_dev_type,dst_dev_id,CTRL_REMOTE_IP_HEX,
								0x0001,DEV_TYPE_PISC,pisc_local_get_my_dev_id(),pisc_local_get_my_dev_ip(),
								cmd,
								buf,len,send_buf_tmp,&send_len);

	//����
	ctrl_port_send_data(send_buf_tmp,send_len);
	//��ӡ��ʾ
	debug_info_print_proc(DEBUG_INFO_TYPE_SEND,dst_dev_type,dst_dev_id,CTRL_REMOTE_PORT,cmd,send_buf_tmp,send_len);

}

static void ctrl_port_send_init(void)
{
	int 	    yes;
	int                set;	

	//��SOCKET��ַ�ṹ�ĳ���
	send_socklen = sizeof(struct sockaddr_in);	
	//����UDP�׽���	
	send_cmd_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(send_cmd_socket_fd<0)
	{
		printf("socket creating err in udptalk\n");
		exit(1);
	}			

	yes = 1;
	set = setsockopt(send_cmd_socket_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	
	//��䱾��IP�Ͷ˿�
	memset(&send_localaddr,0,socklen);
	send_localaddr.sin_family=AF_INET;
	send_localaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	send_localaddr.sin_port=htons(SEND_CTRL_LOCAL_PORT);
	//���Է�IP�Ͷ˿�--���͵�ʱ������
	memset(&send_remoteaddr,0,send_socklen);
	send_remoteaddr.sin_family=AF_INET;	

	//�󶨱��ض˿�
	if(bind(send_cmd_socket_fd, (struct sockaddr *)&send_localaddr, send_socklen)<0)
	{	
		printf("send_bind local address err in udptalk, port: %d\r\n",send_localaddr.sin_port);
		exit(2);
	}


}

//***********************************************************************************************************************
//��������:�����������
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
static void* ctrl_port_thread(void* param)
{	
	uint8 cmd_recv_buf[1024];//���ջ�����
	tba_bus_pack_t *tba_bus_p=(tba_bus_pack_t *)cmd_recv_buf;
	int length=0;
	static struct sockaddr_in localaddr,remoteaddr;

	int 	    yes;
	int                set;	
	printf("ctrl_port_thread start....\r\n");
	
	
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
	localaddr.sin_port=htons(RECV_CTRL_LOCAL_PORT);
	//���Է�IP�Ͷ˿�--���͵�ʱ������
	memset(&remoteaddr,0,socklen);
	remoteaddr.sin_family=AF_INET;	

	//�󶨱��ض˿�
	if(bind(cmd_socket_fd, (struct sockaddr *)&localaddr, socklen)<0)
	{	
		printf("bind local address err in udptalk, port: %d\r\n",localaddr.sin_port);
		exit(2);
	}

	ctrl_port_send_init();

	while(1)
	{		
		//��ȡsocket		
		length=recvfrom(cmd_socket_fd, cmd_recv_buf,sizeof(cmd_recv_buf), 0, (struct sockaddr *)&remoteaddr, &socklen);
		
		//�ж��Ƿ�������
		if(length>0)
		{
			//if(tba_bus_p->src_dev_type==0x01)
			{
				//printf("recv pisc data, dev_type: 0x%x dev_id: %d, cmd: 0x%xtba_bus_p->cmd\r\n",tba_bus_p->src_dev_type,tba_bus_p->src_dev_id,tba_bus_p->cmd);
				//print_buf(cmd_recv_buf,20);
			}
			//��ӡ��ʾ
			debug_info_print_proc(DEBUG_INFO_TYPE_RECV,tba_bus_p->src_dev_type,tba_bus_p->src_dev_id,RECV_CTRL_LOCAL_PORT,tba_bus_p->cmd,(uint8 *)tba_bus_p,TAB_BUS_PACK_HEAD_LEN+tba_bus_p->app_length);
			//�豸״̬ok
			dev_status_set_dev_status(tba_bus_p->src_dev_type,tba_bus_p->src_dev_id,DEV_STATUS_OK);
			//��������
			data_proc_matrix_Dispatch(tba_bus_p->src_dev_type,tba_bus_p->src_dev_id,tba_bus_p->cmd,(uint8 *)tba_bus_p,TAB_BUS_PACK_HEAD_LEN+tba_bus_p->app_length,0);
		}			
	}
}
void	ctrl_port_thread_install(void)
{
	//�����߳�
	//pthread_create(&ctrl_port_thread_id, NULL, (void*)ctrl_port_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	ThreadCreate(&ctrl_port_thread_id, ctrl_port_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	return;
}


                                          
