//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ���������� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:read_soundcard.h
//*�ļ�����:����������
//*�ļ�����:mmaple
//*��������:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

//ͷ�ļ�����SOUNDCARD_H�ĺ궨��
#ifndef SOUNDCARD_H_H
#define SOUNDCARD_H_H

#define AUDIO_SAMPLE_SPEED	(44100)
//��Ƶ����������
#define AUDIO_SAMPLE_NUM	512
//��Ƶ��������
#define AUDIO_SAMPLE_BITS	16
//��Ƶ���г���
#define AUDIO_FIFO_SIZE		10

//��Ƶ���ն˿�
#define AUDIO_RECV_PORT		3000
//ÿһ·��Ƶһ�����ݵĻ�������С ��λ/short
#define AUDIO_CHANNEL_SIZE_SHORT	(AUDIO_SAMPLE_NUM) //AUDIO_SAMPLE_NUM*10*2 �ֽ�
//�������һ�����ݵĴ�С ��λ/�ֽ�
#define AUDIO_PACKET_SIZE_BYTE (AUDIO_SAMPLE_NUM*AUDIO_SAMPLE_BITS/8) //����������ݰ� �ֽ���


//ͨ���Ŷ���
#define CHANNEL_LEFT	1
#define CHANNEL_RIGHT	2

//������ʼ��
void soundcard_init(void);
//��ȡ��������
uint8 soundcard_get_data(uint8 channel,uint16 *audio_buf, uint16* audio_len);

#endif



