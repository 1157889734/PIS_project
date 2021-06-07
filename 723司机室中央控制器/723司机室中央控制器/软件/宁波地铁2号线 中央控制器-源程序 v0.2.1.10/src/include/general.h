//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& �г�ͨ�����߽ӿ� &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//*�ļ�����:general.h

//*�ļ�����:

//*�ļ�����:

//*��������:2007��5��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#ifndef		GENERAL_H
#define		GENERAL_H



#define		FALSE	0
#define		TRUE	1

#define	EQUAL		1
#define	UNEQUAL		2
#define	WHATEVER		3
#define	BIGGER		4
#define	SMALLER		5


#define	BIT_1	0x1
#define	BIT_2	0x3
#define	BIT_3	0x7
#define	BIT_4	0xF
#define	BIT_5	0x1F
#define	BIT_6	0x3F
#define	BIT_7	0x7F
#define	BIT_8	0xFF
#define	BIT_9	0x01FF
#define	BIT_10	0x03FF
#define	BIT_11	0x07FF
#define	BIT_12	0x0FFF
#define	BIT_13	0x1FFF
#define	BIT_14	0x3FF
#define	BIT_15	0x7FFF
#define	BIT_16	0xFFFF


#ifndef NULL
#define NULL	(void *)0
#endif



//KEILC51���������ݶ���
#define xdata
#define data
#define idata
#define code const

//������������
typedef unsigned char  uint8;                   /* �޷���8λ���ͱ���                        */
typedef volatile unsigned char vuint8;                  /* �޷���16λ���ͱ���                       */
typedef signed   char  int8;                    /* �з���8λ���ͱ���                        */
typedef unsigned short uint16;                  /* �޷���16λ���ͱ���                       */
typedef volatile unsigned short vuint16;                  /* �޷���16λ���ͱ���                       */
typedef signed   short int16;                   /* �з���16λ���ͱ���                       */
typedef unsigned int   uint32;                  /* �޷���32λ���ͱ���                       */
typedef signed   int   int32;                   /* �з���32λ���ͱ���                       */
typedef float          fp32;                    /* �����ȸ�������32λ���ȣ�                 */
typedef double         fp64;                    /* ˫���ȸ�������64λ���ȣ�                 */


#define B0000 0x00
#define B0001 0x01
#define B0010 0x02
#define B0011 0x03
#define B0100 0x04
#define B0101 0x05
#define B0110 0x06
#define B0111 0x07
#define B1000 0x08
#define B1001 0x09
#define B1010 0x0A
#define B1011 0x0B
#define B1100 0x0C
#define B1101 0x0D
#define B1110 0x0E
#define B1111 0x0F



//��Ԥ����ʱ�Զ����ɱ������� packet_##fn---�Ѳ�ͬ��fn�滻��packet_����
#define __packetlist(nm, fn) \
static packetlist_t packet_##fn={nm, fn}



#endif

