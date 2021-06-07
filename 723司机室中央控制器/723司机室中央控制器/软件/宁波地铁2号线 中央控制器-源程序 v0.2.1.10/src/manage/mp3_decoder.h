//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&��ʱ��0��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:timer0.h
//*�ļ�����:��ʱ��0��������
//*�ļ�����: mmaple
//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#ifndef MP3_DECODER_H
#define MP3_DECODER_H

//�ļ��б�����ļ�����
#define FILE_LIST_NUM_MAX		64

//�ļ��б�����ļ�������
#define FILE_NAME_LENGTH_MAX		256


//int mp3_decoder_play_list(uint8 channel,uint16 *list_buf, uint16 list_num);
int mp3_decoder_play_list(uint8 channel,uint8 *path,uint16 list_num);
void mp3_decoder_stop_play(uint8 channel);
extern void mp3_decoder_set_pcm_data(uint16 *buf, uint16 len);
uint8 mp3_decoder_get_pcm_data(uint16 *buf, uint16 len);
void	mp3_decoder_thread_install(void);
void mp3_decoder_set_run_flag(uint8 onoff);

uint8 mp3_decode_get_is_playing(void);


#endif

