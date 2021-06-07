/*
 * @Descripttion: 
 * @vesion: 
 * @Author: sunzhguy
 * @Date: 2020-05-26 14:59:56
 * @LastEditor: sunzhguy
 * @LastEditTime: 2020-12-08 10:34:20
 */
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ϵͳģ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:sys.c
//*�ļ�����:ϵͳģ��
//*�ļ�����:
//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#include "../include/include.h"


void sys_init(void)
{	
	soundcard_init();
	io_init();
	led_init();
	data_proc_matrix_init();

}
void module_init(void)
{	
	broadcast_init();
	train_manage_init();
	pisc_local_init();	//�������ݳ�ʼ��,�豸�ſ����ں���ĳ�ʼ�����õ�
	dcp_init();
	pisc_init();
	tms_init();	
	dva_init();//DVA�豸��ʼ��
	media_init();
	ptu_init();
	occ_init();
}

void thread_init(void)
{
	//������������
	fep_audio_thread_install();
	//�㲥��Ƶ������ʼ��
	broadcast_audio_thread_install();
	//���߿��ƶ˿�
	ctrl_port_thread_install();
	//�г����й��̹���
	train_manage_thread_install();
	//�豸״̬����
	dev_status_thread_install();	
	//io��ƽ���
	io_manage_thread_install();
	//MP3����
	mp3_decoder_thread_install();
	//�㲥
	broadcast_thread_install();

}



