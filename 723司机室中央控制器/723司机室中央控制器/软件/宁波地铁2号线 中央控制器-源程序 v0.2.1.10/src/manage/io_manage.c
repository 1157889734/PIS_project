//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&�㲥����&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:broadcast.c

//*�ļ�����:�㲥����

//*�ļ�����:mmaple

//*��������:2011��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

//IO�����ʱ�䣬��λ����
#define IO_CHECK_INTERVAL_MS		(50)


static pthread_t io_manage_thread_install_id;


void io_manage_init(void)
{

}

static void* io_manage_thread(void* param)
{	
	printf("io_manage_thread start....\r\n");

	while(1)
	{
		usleep(IO_CHECK_INTERVAL_MS*1000);
		io_check_level_proc();
	}
}
void	io_manage_thread_install(void)
{
	//�����߳�
	//pthread_create(&io_manage_thread_install_id, NULL, (void*)io_manage_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	ThreadCreate(&io_manage_thread_install_id,  io_manage_thread, NULL); 	//PA�ڲ�Э�����ݲɼ��̴߳���
	return;
}




