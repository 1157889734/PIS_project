//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �����߳� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:ctrl.h

//*�ļ�����:�����߳�

//*�ļ�����:mmaple

//*��������:2009/11
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef PRINT_H
#define PRINT_H

extern void PfDumpPrint(const char *file, int line, const char *format, ... );
extern void print_buf(unsigned char *buf, unsigned short len);


#define FiPrint( format, arg... )		PfDumpPrint( __FILE__, __LINE__, format, ##arg )



#endif





