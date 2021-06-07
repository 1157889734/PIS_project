//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&��ʱ��0��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:timer0.h
//*�ļ�����:��ʱ��0��������
//*�ļ�����:mmaple
//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef MANAGE_H
#define MANAGE_H


#include "sys.h"
#include "dev_status.h"
#include "broadcast.h"
#include "master.h"
#include "log.h"
#include "dva_broadcast_rule.h"
#include "mp3_decoder.h"
#include "train_manage.h"
#include "io_manage.h"
#include "debug_info_manage.h"


//����Ѳ���ṹ
typedef struct
{
	uint8 dev_id;			//�豸��
	uint16 interval;		//Ѳ���� 0xFFFF--��������Ѳ��  0--��������Ѳ��	
	uint8 poll_error_num;		//�����Ѳ������---ͨ����������
	uint8 poll_error_max_num;		//�����Ѳ������---ͨ����������
	uint8 dev_status;
}__attribute((packed))token_polling_table_t;


#endif

