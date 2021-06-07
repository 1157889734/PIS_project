//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&�㲥����&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:broadcast.c

//*�ļ�����:�㲥����

//*�ļ�����:mmaple

//*��������:2011��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

static pthread_t train_manage_thread_install_id;

void train_manage_init(void)
{
}
void train_manage_uninit(void)
{
}

static void* train_manage_thread(void* param)
{	
	static uint8 num_tmp=0;
	printf("train_manage_thread start....\r\n");

	while(1)
	{
		usleep(500*1000);
		num_tmp++;
		//�������ݷ���
		pisc_local_send_default_data();
		//��������ļ������ȼ�
		broadcast_get_conf_pri();

		//����
		if(pisc_get_master_status())
		{
			//5����
			if((num_tmp%10)==0)
			{
				//��ͷ����ʾ
				head_led_send_content();
				//��������ʾ
				lcu_led_send_content();
				//�����������ٶ�
				lcu_led_roll_sec();
				//��̬��ͼ����
				dmp_set_light_level();
				//�㲥���ȼ�
				broadcast_send_pri();
				//����ֵ
				broadcast_send_vol();
				//��ȡ�����ļ���Խվ��Ϣ
				pisc_update_jump_stations_from_conf();
			}
			if((num_tmp%2)==0)
			{
				//����ʱ��
				pisc_local_send_time();
			}
		}
	}

}
void	train_manage_thread_install(void)
{
	//�����߳�
	//pthread_create(&train_manage_thread_install_id, NULL, (void*)train_manage_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	ThreadCreate(&train_manage_thread_install_id, train_manage_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	return;
}



