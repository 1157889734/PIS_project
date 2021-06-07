//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 主函数 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*文件名称: main.c
//*文件作用: 主函数
//*文件作者:  mmaple
//*创建日期: 2012年3月
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "../include/include.h"

static void init(void)
{
	FiPrint("init...\r\n");

	//系统信息初始化
	sys_init();
	//模块初始化
	module_init();
	//线程初始化
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


