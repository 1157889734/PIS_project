//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 读声卡数据 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*文件名称:read_soundcard.h

//*文件作用:读声卡数据

//*文件作者:mmaple

//*创建日期:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "../include/include.h"



#define	WRITE	0x01
#define	READ	0x02


static uint16 audio_read_buf3[AUDIO_PACKET_SIZE_BYTE];


//fifo 左右声道发送缓冲队列
unsigned short audio_left_write_fifo[AUDIO_FIFO_SIZE][AUDIO_CHANNEL_SIZE_SHORT];
unsigned short audio_right_write_fifo[AUDIO_FIFO_SIZE][AUDIO_CHANNEL_SIZE_SHORT];
//fifo数据读入位置指示
int audio_left_write_fifo_in=0;
int audio_right_write_fifo_in=0;
//fifo数据读出位置指示
int audio_left_write_fifo_out=0;
int audio_right_write_fifo_out=0;

//读到新的声卡数据
static uint8 soundcard_get_data_flag=0;

//音频录制设备描述符
static int audio_record_fd=-1;
//音频播放设备描述符
int audio_play_fd=-1;


//读声卡时，第一个字节是哪个声道的数据
//static uint8 front_channel=CHANNEL_RIGHT;
static uint8 front_channel=0;



static pthread_t soundcard_read_data_thread_id;

//***********************************************************************************************************************
//函数作用:音频设备初始化
//参数说明:
//注意事项:
//返回说明:无
//***********************************************************************************************************************
static int soundcard_audio_init(int sample_rate, int sample_bits, int channels, int rw)
{
	int i=0;
	int fd=-1;
	
	
	//打开设备	读写方式打开 可以同时录音和播放
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
	
	//设置打开方式
	i=0;
	//ioctl(fd,SNDCTL_DSP_RESET,&i);//复位
	i=0;
	//ioctl(fd,SNDCTL_DSP_SYNC,&i);//同步方式
	
	//设置采样率
	i=sample_rate;
	if(ioctl(fd,SNDCTL_DSP_SPEED,&i)<0)
	{
		//fprintf(stderr, "设置采样率 %d 失败:%s ",i,strerror(errno));
		//return -1;
	}
	if(i!=sample_rate)
	{
		//fprintf (stderr, "不支持采样率:%d, 强制设置为:%d ",sample_rate,i);
		//fprintf(stderr, "sample_rate: %d error:%s\n ",i,strerror(errno));
		printf("sample_rate is %d\n", sample_rate);
		//return -1;
	}

	//设置采样精度
	i=AFMT_S16_LE;
	if (ioctl(fd,SNDCTL_DSP_SETFMT,&i)<0)
	{
		//fprintf(stderr, "设置采样精度 %d 失败:%s ",i,strerror(errno));
		printf("SNDCTL_DSP_SETFMT set error\n");
		return -1;
	}
	if(i!=AFMT_S16_LE)
	{
		fprintf (stderr, "不支持采样精度:%d, 强制设置为:%d ",AFMT_S16_LE,i);
		//return -1;
	}
		
	//设置声道
	i=channels;
	if((ioctl(fd,SNDCTL_DSP_CHANNELS,&i))<0)
	{
		fprintf(stderr, "设置声道 %d 失败:%s ",i,strerror(errno));
		return -1;
	}
	if(i!=channels)
	{
		fprintf (stderr, "不支持声道:%d, 强制设置为:%d ",channels,i);
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
		//从声卡读数据
		read_size=read(audio_record_fd,audio_read_buf3,sizeof(audio_read_buf3));

		//有数据从声卡读出到fifo缓冲队列
		if(read_size>0)
		{
			//单声道处理，放入单声道fifo队列
			int i;
			short * src_p=(short *)audio_read_buf3;
			short * dst_right_p=(short *)audio_right_write_fifo[audio_right_write_fifo_in];
			short * dst_left_p=(short *)audio_left_write_fifo[audio_left_write_fifo_in];
			//获得声卡新数据
			soundcard_get_data_flag=1;
			
			//左声道在前
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
					//错误，无音频时，数据不一定是多少 
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

//没声音 ，不知道为什么
#if 0
			read_num++;
			if(read_num%100==0)
			{
				printf("read soundcard data: %d\r\n",read_size/2);
				print_buf(audio_right_write_fifo[audio_right_write_fifo_in],30);
			}
			broadcast_audio_send_audio((uint8 *)&audio_right_write_fifo[audio_right_write_fifo_in],1024);

#endif
			//fifo队列读出位置++，如果已经到达队列尾部，则返回头部
			if(++audio_left_write_fifo_in>=AUDIO_FIFO_SIZE)audio_left_write_fifo_in=0;
			if(++audio_right_write_fifo_in>=AUDIO_FIFO_SIZE)audio_right_write_fifo_in=0;
		}
	}		
}

//***********************************************************************************************************************
//函数作用:音频数据从声卡读取写入缓冲区 线程
//参数说明:
//注意事项:
//返回说明:无
//***********************************************************************************************************************
void soundcard_init(void)
{
#if 0
	//初始化音频录制设备	
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

	//读取声卡数据线程
	//pthread_create(&soundcard_read_data_thread_id, NULL, soundcard_read_data_thread,NULL);
	ThreadCreate(&soundcard_read_data_thread_id,  soundcard_read_data_thread,NULL);

}




