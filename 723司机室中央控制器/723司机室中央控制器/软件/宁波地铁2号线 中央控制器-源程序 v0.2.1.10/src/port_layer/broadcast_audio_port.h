//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ������ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: net_manager.h

//*�ļ�����: ������

//*�ļ�����: mmaple

//*��������: 2009/7
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef BROADCAST_AUDIO_H
#define BROADCAST_AUDIO_H

#define BROADCAST_AUDIO_DATA_SIZE		(1024)


void	 broadcast_audio_thread_install(void);
void broadcast_audio_send_audio(uint8 operate_dev_type, uint8 operate_dev_id,uint8 *buf, uint16 length);

#endif

