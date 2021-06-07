//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ���������� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:read_soundcard.h

//*�ļ�����:����������

//*�ļ�����:mmaple

//*��������:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"



#define	WRITE	0x01
#define	READ	0x02


static uint16 audio_read_buf3[AUDIO_PACKET_SIZE_BYTE];


//fifo �����������ͻ������
unsigned short audio_left_write_fifo[AUDIO_FIFO_SIZE][AUDIO_CHANNEL_SIZE_SHORT];
unsigned short audio_right_write_fifo[AUDIO_FIFO_SIZE][AUDIO_CHANNEL_SIZE_SHORT];
//fifo���ݶ���λ��ָʾ
int audio_left_write_fifo_in=0;
int audio_right_write_fifo_in=0;
//fifo���ݶ���λ��ָʾ
int audio_left_write_fifo_out=0;
int audio_right_write_fifo_out=0;

//�����µ���������
static uint8 soundcard_get_data_flag=0;

//��Ƶ¼���豸������
static int audio_record_fd=-1;
//��Ƶ�����豸������
int audio_play_fd=-1;


//������ʱ����һ���ֽ����ĸ�����������
//static uint8 front_channel=CHANNEL_RIGHT;
static uint8 front_channel=0;



static pthread_t soundcard_read_data_thread_id;

//***********************************************************************************************************************
//��������:��Ƶ�豸��ʼ��
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
static int soundcard_audio_init(int sample_rate, int sample_bits, int channels, int rw)
{
	int i=0;
	int fd=-1;
	
	
	//���豸	��д��ʽ�� ����ͬʱ¼���Ͳ���
	if(rw == READ)
	{
		if((fd=open("/dev/dsp",O_RDONLY | O_SYNC))<0)
		//if((fd=open("/dev/dsp",O_RDWR | O_SYNC))<0)
		{
			printf("hello Can't open /dev/dsp \n");
			return -1;
		}	
	}
#if 1
	else if(rw == WRITE)
	{
		if((fd=open("/dev/dsp",O_WRONLY | O_SYNC))<0)
		{
			printf("Can't open /dev/dsp \n");
			return -1;
		}	
	}
#endif	
	
	//���ô򿪷�ʽ
	i=0;
	//ioctl(fd,SNDCTL_DSP_RESET,&i);//��λ
	i=0;
	//ioctl(fd,SNDCTL_DSP_SYNC,&i);//ͬ����ʽ
	
	//���ò�����
	i=sample_rate;
	if(ioctl(fd,SNDCTL_DSP_SPEED,&i)<0)
	{
		//fprintf(stderr, "���ò����� %d ʧ��:%s ",i,strerror(errno));
		//return -1;
	}
	if(i!=sample_rate)
	{
		//fprintf (stderr, "��֧�ֲ�����:%d, ǿ������Ϊ:%d ",sample_rate,i);
		//fprintf(stderr, "sample_rate: %d error:%s\n ",i,strerror(errno));
		printf("sample_rate is %d\n", sample_rate);
		//return -1;
	}

	//���ò�������
	i=AFMT_S16_LE;
	if (ioctl(fd,SNDCTL_DSP_SETFMT,&i)<0)
	{
		//fprintf(stderr, "���ò������� %d ʧ��:%s ",i,strerror(errno));
		printf("SNDCTL_DSP_SETFMT set error\n");
		return -1;
	}
	if(i!=AFMT_S16_LE)
	{
		fprintf (stderr, "��֧�ֲ�������:%d, ǿ������Ϊ:%d ",AFMT_S16_LE,i);
		//return -1;
	}
		
	//��������
	i=channels;
	if((ioctl(fd,SNDCTL_DSP_CHANNELS,&i))<0)
	{
		fprintf(stderr, "�������� %d ʧ��:%s ",i,strerror(errno));
		return -1;
	}
	if(i!=channels)
	{
		fprintf (stderr, "��֧������:%d, ǿ������Ϊ:%d ",channels,i);
		//return -1;
	}

	return fd;
}


uint8 soundcard_get_data(uint8 channel,uint16 *audio_buf, uint16* audio_len)
{

#if 1
	if(CHANNEL_RIGHT==channel)
	{
		if(audio_right_write_fifo_out!=audio_right_write_fifo_in)
		{
			//memcpy((uint8 *)audio_buf,(uint8 *)audio_read_buf3,1024);
			memcpy((uint8 *)audio_buf,(uint8 *)audio_right_write_fifo[audio_right_write_fifo_out],1024);
			*audio_len=1024;

			audio_right_write_fifo_out++;
			if(audio_right_write_fifo_out>=AUDIO_FIFO_SIZE)audio_right_write_fifo_out=0;
			
			return 1;
		}
		else return 0;
	}
	else if(CHANNEL_LEFT==channel)
	{
		if(audio_left_write_fifo_out!=audio_left_write_fifo_in)
		{
			//memcpy((uint8 *)audio_buf,(uint8 *)audio_read_buf3,1024);
			memcpy((uint8 *)audio_buf,(uint8 *)audio_left_write_fifo[audio_left_write_fifo_out],1024);
			*audio_len=1024;

			audio_left_write_fifo_out++;
			if(audio_left_write_fifo_out>=AUDIO_FIFO_SIZE)audio_left_write_fifo_out=0;
			
			return 1;
		}
		else return 0;
	}
#endif

#if 1
	if(soundcard_get_data_flag)
	//if(1)
	{
		if(channel==CHANNEL_LEFT)
		{
			memcpy((uint8 *)audio_buf,(uint8 *)audio_left_write_fifo[audio_left_write_fifo_out],1024);
			*audio_len=1024;

			audio_left_write_fifo_out++;
			if(audio_left_write_fifo_out>=AUDIO_FIFO_SIZE)audio_left_write_fifo_out=0;
			
		}
		else
		{
			memcpy((uint8 *)audio_buf,(uint8 *)audio_right_write_fifo[audio_right_write_fifo_out],1024);
			*audio_len=1024;

			audio_right_write_fifo_out++;
			if(audio_right_write_fifo_out>=AUDIO_FIFO_SIZE)audio_right_write_fifo_out=0;
		}
		//soundcard_get_data_flag=0;
		return BH_TRUE;
	}
	else
	{
		return BH_FALSE;
	}
#endif	
}

static void soundcard_init_front_channel(uint32 sum_front,uint32 sun_back)
{
	if(sum_front>sun_back)
	{
		front_channel=CHANNEL_LEFT;
		printf("left is front\r\n");
	}
	else
	{
		front_channel=CHANNEL_RIGHT;
		printf("right is front\r\n");
	}
}

static uint8 soundcard_get_front_channel(void)
{
	return front_channel;
}


static void *soundcard_read_data_thread(void *param)
{
	int num_temp2=0;

	uint32 sum1=0;
	uint32 sum2=0;	

	int read_size=0;

	audio_record_fd = soundcard_audio_init(AUDIO_SAMPLE_SPEED,AUDIO_SAMPLE_BITS,2, READ);
	if(audio_record_fd<0)
	{
		printf("hello, audio_init error: fd=%d\n", audio_record_fd);
		exit(-1);
	}	

	while(1)
	{
		static uint16 read_num=0;
		//memset((uint8 *)audio_read_buf3,0,sizeof(audio_read_buf3));
		//������������
		read_size=read(audio_record_fd,audio_read_buf3,sizeof(audio_read_buf3));

		//�����ݴ�����������fifo�������
		if(read_size>0)
		{
			//�������������뵥����fifo����
			int i;
			short * src_p=(short *)audio_read_buf3;
			short * dst_right_p=(short *)audio_right_write_fifo[audio_right_write_fifo_in];
			short * dst_left_p=(short *)audio_left_write_fifo[audio_left_write_fifo_in];
			//�������������
			soundcard_get_data_flag=1;
			
			//��������ǰ
			if(front_channel==CHANNEL_LEFT)
			{
				for(i=0;i<AUDIO_SAMPLE_NUM;i++)
				{
					*dst_left_p++=*src_p++;
					*dst_right_p++=*src_p++;							
				}						
			}
			else if(front_channel==CHANNEL_RIGHT)
			{
				for(i=0;i<AUDIO_SAMPLE_NUM;i++)
				{
					*dst_right_p++=*src_p++;			
					*dst_left_p++=*src_p++;
				}						
			}
#if 1			
			else
			{
				
				for(i=0;i<AUDIO_SAMPLE_NUM;i++)
				{
					//��������Ƶʱ�����ݲ�һ���Ƕ��� 
					if((audio_read_buf3[i*2]&0xff00)>>8==0xff)sum1++;
					if((audio_read_buf3[i*2]&0xff00)>>8==0xfe)sum2++;
				}
				//printf("sum1: %d, sum2: %d\r\n");
				//print_buf(audio_read_buf3,30);
				
				num_temp2+=1;
				if(num_temp2%30==0&&num_temp2)
				{
					soundcard_init_front_channel(sum1,sum2);
				}
			}					
#endif		


#if 0
			printf("right: %d\r\n",read_size);
			print_buf(audio_right_write_fifo[audio_right_write_fifo_in],30);
			
			broadcast_audio_send_audio(audio_right_write_fifo[audio_right_write_fifo_in],read_size/2);
#endif

//û���� ����֪��Ϊʲô
#if 0
			read_num++;
			if(read_num%100==0)
			{
				printf("read soundcard data: %d\r\n",read_size/2);
				print_buf(audio_right_write_fifo[audio_right_write_fifo_in],30);
			}
			broadcast_audio_send_audio((uint8 *)&audio_right_write_fifo[audio_right_write_fifo_in],1024);

#endif
			//fifo���ж���λ��++������Ѿ��������β�����򷵻�ͷ��
			if(++audio_left_write_fifo_in>=AUDIO_FIFO_SIZE)audio_left_write_fifo_in=0;
			if(++audio_right_write_fifo_in>=AUDIO_FIFO_SIZE)audio_right_write_fifo_in=0;
		}
	}		
}

//***********************************************************************************************************************
//��������:��Ƶ���ݴ�������ȡд�뻺���� �߳�
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
void soundcard_init(void)
{
#if 0
	//��ʼ����Ƶ¼���豸	
	audio_play_fd = soundcard_audio_init(AUDIO_SAMPLE_SPEED,AUDIO_SAMPLE_BITS,2, WRITE);
	if(audio_play_fd<0)
	{
		printf("audio_init error: fd=%d\n", audio_play_fd);
		exit(-1);
	}

	audio_record_fd = soundcard_audio_init(AUDIO_SAMPLE_SPEED,AUDIO_SAMPLE_BITS,2, READ);
	if(audio_record_fd<0)
	{
		printf("hello, audio_init error: fd=%d\n", audio_record_fd);
		exit(-1);
	}	
	printf("soundcard_init(), audio_play_fd: %d, audio_record_fd: %d...\r\n",audio_play_fd,audio_record_fd);

	sleep(3);
#endif	

	//��ȡ���������߳�
	//pthread_create(&soundcard_read_data_thread_id, NULL, soundcard_read_data_thread,NULL);
	ThreadCreate(&soundcard_read_data_thread_id,  soundcard_read_data_thread,NULL);

}




