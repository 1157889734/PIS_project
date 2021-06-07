//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �����߳� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:ctrl.h

//*�ļ�����:�����߳�

//*�ļ�����:mmaple

//*��������:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#include "../include/include.h"

#define PRINTF_BUF_SIZE 16*1024
static char s_MsgBuf[PRINTF_BUF_SIZE];
static ClMutexLock s_PrintfMutex;


//***********************************************************************************************************************
//��������:��ӡ����
//����˵��:
//ע������:
//����˵��:��
//***********************************************************************************************************************
void print_buf(unsigned char *buf, unsigned short len)
{
	printf("print_buf: %d\n",len);
	while(len--)printf("%02x ", *buf++);
	printf("\n");
}

void PfDumpPrint(const char *file, int line, const char *format, ... )
{	
	char	*pMsgBuf, *pBasename;
	int 	nMsgLen;	
	
	va_list ap;
	va_start( ap, format );
	
	pBasename = (char *)basename( file );
	
	s_PrintfMutex.Lock();
	
	sprintf( s_MsgBuf, "%s %d:", pBasename, line );
	pMsgBuf = s_MsgBuf + strlen(s_MsgBuf);
	nMsgLen = sizeof(s_MsgBuf) - strlen(s_MsgBuf);
	vsnprintf( pMsgBuf, nMsgLen, format, ap );	
	fprintf( stderr, "%s", s_MsgBuf ); 
	
	s_PrintfMutex.Unlock();
	
	va_end( ap );	
}




