//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ������ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����: net_manager.h

//*�ļ�����: ������

//*�ļ�����: mmaple

//*��������: 2009/7
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef CTRL_PORT_H
#define CTRL_PORT_H


//void ctrl_port_send_cmd(uint16 cmd, uint8 *buf, uint16 len);
void ctrl_port_send_cmd(uint16 dst_train_id, uint8 dst_dev_type, uint8 dst_dev_id,uint16 cmd, uint8 *buf, uint16 len);
void	ctrl_port_thread_install(void);

#endif

