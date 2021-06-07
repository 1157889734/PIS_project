//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& PC������� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:setup.c
//*�ļ�����:PC�������
//*�ļ�����:mmaple
//*��������:2011��8��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "../include/include.h"


//CMD1
#define PTU_SET_TIME			0x0102


#define PTU_GET_TIME			0x0202

#define PTU_ACK_TIME			0x0302


static void ptu_set_time(tba_bus_pack_t *ReceiveMsg);
static void ptu_get_time(tba_bus_pack_t *ReceiveMsg);



//��״̬�������
static dev_proc_t ptu_process_data_table_M[] = 
{
	{TAB_BUS_PACK_HEAD_LEN-4, 		0,		BIT_16,	EQUAL,	PTU_SET_TIME,	(MsgHandler_Callback)ptu_set_time				},	//DCP�������л�
	{TAB_BUS_PACK_HEAD_LEN-4, 		0, 	BIT_16, EQUAL,	PTU_GET_TIME,	(MsgHandler_Callback)ptu_get_time				},	//DCP�������л�


	{0,	0,	0,	0,		0,	NULL													}
};
//��״̬�������
static dev_proc_t ptu_process_data_table_S[] = 
{	

	{0,	0,	0,	0,		0,	NULL													}
};

static mode_matrix_t  ptu_process_table[]=
{
	{PISC_STATUS_M,  ptu_process_data_table_M,},			//��״̬�������
	{PISC_STATUS_S,  ptu_process_data_table_S,},		//��״̬�������
	
	{0, NULL,},
};

//״̬������
static cmd_matrix_t  ptu_cmd_process_table[]=
{
	{CTRL_CMD_DEFAULT,  ptu_process_table,},			//��״̬�������
	
	{0, NULL,},
};

void ptu_init(void)
{
	 data_proc_matrix_add_device_to_matrix_table(DEV_TYPE_PTU, ptu_cmd_process_table);	 
}


static void ptu_set_time(tba_bus_pack_t *ReceiveMsg)
{
	uint8 time_str[32]={0};
	uint8 time_set_str[32]={0};
	printf("ptu_set_time:\r\n");
	print_buf(ReceiveMsg->app_data,6);
	
	sprintf((char *)&time_str[0],"%02d",ReceiveMsg->app_data[2]); //��
	sprintf((char *)&time_str[2],"%02d",ReceiveMsg->app_data[3]); //��
	sprintf((char *)&time_str[4],"%02d",ReceiveMsg->app_data[4]); //ʱ
	sprintf((char *)&time_str[6],"%02d",ReceiveMsg->app_data[5]); //��
	sprintf((char *)&time_str[8],"%04d",ReceiveMsg->app_data[0]|(ReceiveMsg->app_data[1]<<8)); //��					
	sprintf((char *)&time_str[12],".%02d",ReceiveMsg->app_data[6]); //��
	
	
	sprintf((char *)time_set_str,"date %s",time_str);
						
	printf("time is %s\r\n",time_set_str);
	system((const char *)time_set_str);
	
	//��һ�ζ�ʱ��д��Ӳ��ʱ��
	system("hwclock -w");
}

static void ptu_get_time(tba_bus_pack_t *ReceiveMsg)
{
	time_t timep;
	uint8 send_buf_tmp[16];
	uint16 send_len_tmp=0;
	//�����ʽ���Ҫʵ�ʲ���
	printf("*****time: %d\r\n",(uint32)time(&timep));
	printf("ctime: %s\r\n",(uint8 *)ctime(&timep));
	pisc_local_get_time(send_buf_tmp);
	send_len_tmp=7;

	print_buf(send_buf_tmp,send_len_tmp);
	//������ʾ����
	ctrl_port_send_cmd(0xffff,DEV_TYPE_PTU,0xff,PTU_ACK_TIME,send_buf_tmp,send_len_tmp);

}

