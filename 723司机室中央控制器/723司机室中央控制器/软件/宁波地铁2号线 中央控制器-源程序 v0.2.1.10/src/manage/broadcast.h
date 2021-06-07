//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �㲥���� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:broadcast.h

//*�ļ�����:�㲥����

//*�ļ�����:mmaple

//*��������:2011��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#ifndef BROADCAST_H
#define BROADCAST_H


//�㲥����
#define BROADCAST_PRE	 	   0x01//Ԥ��վ
#define BROADCAST_ARRIVE      0x02//��վ��վ
#define BROADCAST_CLOSE_DOOR  0x03//������ʾ�� 
#define BROADCAST_TEST        0x04//�㲥����
#define BROADCAST_SKIP        0x05//����վ�㲥��־
#define BROADCAST_FORCAST     0x06//�㲥Ԥʾ��
#define BROADCAST_URGENT      0x07//�����㲥
#define BROADCAST_OCC	       0x08//OCC�㲥
#define BROADCAST_MEDIA	       0x09//ý��㲥
#define BROADCAST_LIVE      0x0A//�����㲥
#define BROADCAST_NONE 	   0x10//�ޱ�վ


//���ȼ�
#define PRI_OCC			1
#define PRI_URGENT		2
#define PRI_LIVE		3
#define PRI_CLOSE_DOOR	4
#define PRI_STATION		5
#define PRI_MEDIA		6
#define PRI_TEST		7
#define PRI_NONE		0xff
#define PRI_PLAYOVER		0xfe


void broadcast_init(void);
void broadcast_proc(uint8 operate_dev_type, uint8 operate_dev_id,uint8 pisc_broadcast_type);
void broadcast_stop_proc(uint8 pisc_broadcast_type);
void broadcast_get_conf_pri(void);
void broadcast_send_audio(void);
void broadcast_send_pri(void);
void broadcast_set_broadcast_type(uint8 pisc_broadcast_c);
uint8 broadcast_get_broadcast_type(void);
void broadcast_set_broadcast_operate_dev_type(uint8 operate_dev_type);
uint8 broadcast_get_broadcast_operate_dev_type(void);
void broadcast_set_broadcast_operate_dev_id(uint8 operate_dev_id);
uint8 broadcast_get_broadcast_operate_dev_id(void);
void broadcast_set_broadcast_cycle_flag(uint8 cycle_flag);
uint8 broadcast_get_broadcast_cycle_flag(void);


void broadcast_set_occ_play_over_dva_flag(uint8 flag);
uint8 broadcast_get_pri(uint8 operate_dev_type, uint8 operate_dev_id,uint8 pisc_broadcast_c);
void broadcast_set_urgent_no(uint8 urgent_no);
uint8 broadcast_get_urgent_no(void);
void broadcast_send_vol(void);

void	broadcast_thread_install(void);

#endif


