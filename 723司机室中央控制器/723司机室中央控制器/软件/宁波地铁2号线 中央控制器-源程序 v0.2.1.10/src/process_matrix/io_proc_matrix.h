//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ���Զ����� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:halt_ato.c

//*�ļ�����:�г�ͨ�����߹�����

//*�ļ�����:mmaple

//*��������:2010��12��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#ifndef IO_PROC_MATRIX_H
#define IO_PROC_MATRIX_H

void io_check_table_init(uint8 pin_cmd, uint8 trigger,uint8 level, uint8 level_bak,uint8 num,uint8 num_max,io_handler_callback handler);
void io_check_init(void);
void io_check_level_proc(void);



#endif




