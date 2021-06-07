//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&定时器0驱动程序&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*文件名称:timer0.h
//*文件作用:定时器0驱动程序
//*文件作者: mmaple
//*创建日期:2007年5月
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#ifndef MP3_DECODER_H
#define MP3_DECODER_H

//文件列表最多文件个数
#define FILE_LIST_NUM_MAX		64

//文件列表最大文件名长度
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

