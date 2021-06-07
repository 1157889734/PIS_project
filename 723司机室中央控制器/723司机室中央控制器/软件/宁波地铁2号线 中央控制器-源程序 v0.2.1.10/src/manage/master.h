//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �������� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:master.h
//*�ļ�����:��������
//*�ļ�����:
//*��������:2007��7��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#ifndef MASTER_H
#define MASTER_H

#define MASTER_STATUS		(1)
#define SLAVE_STATUS	(0)


//������
#define MASTER_TYPE_KEY	(0x11)
#define MASTER_TYPE_OTHER_PISC_ERROR	(0x21)
#define MASTER_TYPE_DEV_ID_LOW	(0x31)
//������
#define SLAVE_TYPE_INIT	(0x10)
#define SLAVE_TYPE_OTHER_KEY	(0x20)
#define SLAVE_TYPE_DVA_ERROR	(0x30)
#define SLAVE_TYPE_APU_ERROR	(0x40)
#define SLAVE_TYPE_DEV_ID_HIGH	(0x50)


void master_set_timeout_num_add(void);
void master_clear_timeout_num(void);
void master_proc(void);
void master_init_master_slave_type(void);


#endif


