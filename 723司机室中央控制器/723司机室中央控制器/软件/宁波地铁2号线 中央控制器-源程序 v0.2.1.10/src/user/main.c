//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ������ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: main.c
//*�ļ�����: ������
//*�ļ�����:  mmaple
//*��������: 2012��3��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "../include/include.h"

static void init(void)
{
	FiPrint("init...\r\n");

	//ϵͳ��Ϣ��ʼ��
	sys_init();
	//ģ���ʼ��
	module_init();
	//�̳߳�ʼ��
	thread_init();
}
static void uninit()
{
	FiPrint("uninit...\r\n");
}
int main(int argc, char **argv)
{
	printf( "***Start main, compile datetime:%s %s!!!\r\n", __DATE__, __TIME__ );

	init();
	sleep(2);
	while(1)
	{
		//printf("sleep 10s\r\n");
		sleep(1);
	}	
	uninit();

}


