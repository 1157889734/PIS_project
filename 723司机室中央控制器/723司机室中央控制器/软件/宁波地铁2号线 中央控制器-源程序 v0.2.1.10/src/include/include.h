//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ϵͳģ�� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:include.h

//*�ļ�����:ͷ�ļ�����

//*�ļ�����: mmaple

//*��������:2011��4��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef INCLUDE_H
#define INCLUDE_H


#include <stdio.h>      /*��׼�����������*/
#include <stdlib.h>     /*��׼�����ⶨ��*/
#include <unistd.h>     /*Unix ��׼��������*/
#include <sys/types.h>  
#include <sys/stat.h>   
#include <fcntl.h>      /*�ļ����ƶ���*/
#include <sys/ioctl.h>
#include <termios.h>    /*PPSIX �ն˿��ƶ���*/
#include <errno.h>      /*����Ŷ���*/
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h> //�߳�


//#include <iostream.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> 
//#include <fstream.h>

#include <sys/soundcard.h>

//mpeg������
#include <ffmpeg/avutil.h>
#include <ffmpeg/avformat.h>
#include <ffmpeg/avcodec.h>

#include <stdlib.h>
#include <string.h>

#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#if 1



#include <termios.h>    /*PPSIX �ն˿��ƶ���*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <stdbool.h>
#include <sys/socket.h>//Socket������������
#include <netinet/in.h>//sockaddr_in�ṹ����
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>


//mpeg������
#include <ffmpeg/avutil.h>
#include <ffmpeg/avformat.h>
#include <ffmpeg/avcodec.h>



#include <termios.h>    /*PPSIX �ն˿��ƶ���*/
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> 


#endif


#include "general.h"
#include "config.h"

#include "../lib/lib.h"
#include "../driver/driver.h"
#include "../port_layer/port_layer.h"
#include "../operate_device/operate_device.h"
#include "../terminal_device/terminal_device.h"
#include "../process_matrix/matrix.h"
#include "../manage/manage.h"


#endif

