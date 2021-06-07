//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 控制线程 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*文件名称:ctrl.h

//*文件作用:控制线程

//*文件作者:mmaple

//*创建日期:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#include "../include/include.h"

#define PRINTF_BUF_SIZE 16*1024
static char s_MsgBuf[PRINTF_BUF_SIZE];
static ClMutexLock s_PrintfMutex;


//***********************************************************************************************************************
//函数作用:打印函数
//参数说明:
//注意事项:
//返回说明:无
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




