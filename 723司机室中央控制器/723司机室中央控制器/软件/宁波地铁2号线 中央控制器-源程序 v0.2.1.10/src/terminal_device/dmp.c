//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ���ֱ�վ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:dva.c
//*�ļ�����:���ֱ�վ��
//*�ļ�����:mmaple
//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

#define DMP_SET_LIGHT_LEVEL	(0x020C)

void dmp_init(void)
{	

}

void dmp_set_light_level(void)
{
	uint8 temp_str[32]={0};
	if(GetValueFromEtcFile(PISC_CONF_PATH,"dmp","light_level",(char *)temp_str,sizeof(temp_str)-1)==0)
	{
		pisc_set_dmp_light(atoi((const char *)temp_str));
	}	
}



