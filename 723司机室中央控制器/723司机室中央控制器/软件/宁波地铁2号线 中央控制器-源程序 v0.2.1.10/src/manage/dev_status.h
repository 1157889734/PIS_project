//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �г�ͨ�����߹����� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:dev_status.h

//*�ļ�����:�г�ͨ�����߹�����

//*�ļ�����:mmaple

//*��������:2011��1��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#ifndef DEV_STATUS_H
#define DEV_STATUS_H

//Ѳ�������
#define DEV_STATUS_TABLE_NUM		192	 //һֱ����
//#define DEV_STATUS_TABLE_NUM		228	//  6*(8����̬+ 2��led +1 ��lcu + 2�������� +) + 2 *(1��tms +1 ��ý�� + 3��dva + 1����ͷ��)

#define DEV_STATUS_OK				(1)
#define DEV_STATUS_ERROR			(2)
#define DEV_STATUS_NO_DEV		(3)

//�����豸
#define DEV_TYPE_ALL		0xFF	//ȫ���豸
#define DEV_ID_ALL			0xFF	//ȫ���豸
#define DEV_IP_ALL			0xFF	//ȫ���豸


//�豸����
#define DEV_TYPE_PISC	(0x01)
#define DEV_TYPE_DCP	(0x02)
#define DEV_TYPE_TMS	(0x03)
#define DEV_TYPE_RECON	(0x04)
#define DEV_TYPE_RECORDER	(0x05)
//#define RESERVE	(0x06)
#define DEV_TYPE_DMP	(0x07)
#define DEV_TYPE_EHP	(0x08)
#define DEV_TYPE_LCU_LED	(0x09) //ý���������0x09
#define DEV_TYPE_HEAD_LED	(0x0A)
#define DEV_TYPE_AMP	(0x0B)
#define DEV_TYPE_SWITCH	(0x0C)
#define DEV_TYPE_PTU	(0x0D)




//��ʼ���豸��Ч״̬
void dev_status_init_dev_valid(uint8 dev_type);
//����豸���豸״̬��
uint8 dev_status_add_dev(uint8 dev_type,uint8 dev_id,uint8 status);

//����豸״̬
uint8 dev_status_get_dev_status(uint8 dev_type,uint8 dev_id);
//�����豸״̬
void dev_status_set_dev_status(uint8 dev_type, uint8 dev_id, uint8 status);
void	dev_status_thread_install(void);


#endif
