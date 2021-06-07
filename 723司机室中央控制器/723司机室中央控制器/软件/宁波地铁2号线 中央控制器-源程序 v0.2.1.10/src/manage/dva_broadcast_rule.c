//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ���ֱ�վ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:dva.c
//*�ļ�����:���ֱ�վ��
//*�ļ�����:mmaple
//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"

#define DVA_BROADCAST_URGENT_PLAY_NUM_MAX			(FILE_LIST_NUM_MAX)

//Ԥ��վ
#define DVA_BROADCAST_RULE_PRE_WELCOME_INDEX			(000) //��ӭ�ʣ����ģ����У�Ԥ��վ
#define DVA_BROADCAST_RULE_PRE_DIR_INDEX			(100) //���ģ����У�Ԥ��վ
#define DVA_BROADCAST_RULE_PRE_NON_DES_INDEX		(200) //���ģ����У�Ԥ��վ
#define DVA_BROADCAST_RULE_PRE_DES_INDEX				(300) //���ģ����У�Ԥ��վ
#define DVA_BROADCAST_RULE_PRE_END_INDEX			(400) //���ģ����У�Ԥ��վ

//��վ
#define DVA_BROADCAST_RULE_ARR_NON_DES_INDEX		(000) //���ģ����У�Ԥ��վ
#define DVA_BROADCAST_RULE_ARR_DES_INDEX				(100) //���ģ����У�Ԥ��վ


void dva_broadcast_rule_init(void)
{

}

void dva_broadcast_rule_get_pre_list(uint16* pre_list, uint8* language_list,uint16* pre_list_num)
{

	uint8 index=0;
	station_info_t station_info;
	pisc_get_station_info(&station_info);
	
	pre_list[index]=DVA_BROADCAST_RULE_PRE_WELCOME_INDEX+station_info.next_station;
	language_list[index]=LANGUAGE_C;
	index++;
	pre_list[index]=DVA_BROADCAST_RULE_PRE_DIR_INDEX+station_info.end_station;
	language_list[index]=LANGUAGE_C;
	index++;
	if(station_info.next_station!=station_info.end_station)
	{
		pre_list[index]=DVA_BROADCAST_RULE_PRE_NON_DES_INDEX+station_info.next_station;
		language_list[index]=LANGUAGE_C;
		index++;
	}
	else
	{
		pre_list[index]=DVA_BROADCAST_RULE_PRE_DES_INDEX+station_info.next_station;
		language_list[index]=LANGUAGE_C;
		index++;
	}
	pre_list[index]=DVA_BROADCAST_RULE_PRE_END_INDEX+station_info.next_station;
	language_list[index]=LANGUAGE_C;
	index++;

	//ƴ�Ӷ���
	*pre_list_num=index;
}

void dva_broadcast_rule_get_arr_list(uint16* list, uint8* language_list, uint16* list_num)
{

	uint8 index=0;
	station_info_t station_info;
	pisc_get_station_info(&station_info);
	
	if(station_info.next_station!=station_info.end_station)
	{
		list[index]=DVA_BROADCAST_RULE_ARR_NON_DES_INDEX+station_info.next_station;
		
		language_list[index]=LANGUAGE_C;
		index++;
	}
	else
	{
		list[index]=DVA_BROADCAST_RULE_ARR_DES_INDEX+station_info.next_station;
		
		language_list[index]=LANGUAGE_C;
		index++;
	}

	//ƴ�Ӷ���
	*list_num=index;
}

void dva_broadcast_rule_get_urgent_list(uint16* list, uint8* language_list, uint16* list_num)
{
	list[0]=broadcast_get_urgent_no();
	language_list[0]=LANGUAGE_C;
	list[1]=broadcast_get_urgent_no();
	language_list[1]=LANGUAGE_E;
	*list_num=2;
}



