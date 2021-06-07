#ifndef _74HC595__
#define _74HC595__



#define	LED_COL_SUM	144					//���������� 16


//���ư�˿�ӳ��


//#define	GPIO_PORT_IN_R2		GPIOB
//#define	GPIO_PORT_IN_G2		GPIOB
#define	GPIO_PORT_IN_R2		GPIOE
#define	GPIO_PORT_IN_G2		GPIOE



#define	GPIO_PORT_A			GPIOE
#define	GPIO_PORT_B			GPIOE
#define	GPIO_PORT_C			GPIOE
#define	GPIO_PORT_D			GPIOE
#define	GPIO_PORT_IN_E		GPIOB



#define	GPIO_PORT_IN_R1		GPIOE
#define	GPIO_PORT_IN_G1		GPIOE


#define	GPIO_PORT_RCK			GPIOE
#define	GPIO_PORT_CLK			GPIOB

#define	GPIO_PIN_IN_R2			GPIO_Pin_12
#define	GPIO_PIN_IN_G2			GPIO_Pin_14
#define	GPIO_PIN_A				GPIO_Pin_7
#define	GPIO_PIN_B				GPIO_Pin_8
#define	GPIO_PIN_C				GPIO_Pin_9
#define	GPIO_PIN_D				GPIO_Pin_10
#define	GPIO_PIN_IN_E			GPIO_Pin_11
#define	GPIO_PIN_IN_R1			GPIO_Pin_11
#define	GPIO_PIN_IN_G1			GPIO_Pin_13
#define	GPIO_PIN_RCK			GPIO_Pin_15
#define	GPIO_PIN_CLK			GPIO_Pin_10


//��ʾ��˿�ӳ��
#define	GPIO_PORT_595_G2		GPIO_PORT_IN_G2
#define	GPIO_PORT_595_R2		GPIO_PORT_IN_R2
#define	GPIO_PORT_138_A		GPIO_PORT_A
#define	GPIO_PORT_138_B		GPIO_PORT_B
#define	GPIO_PORT_138_C		GPIO_PORT_C
#define	GPIO_PORT_138_D		GPIO_PORT_D
#define	GPIO_PORT_138_E		GPIO_PORT_IN_E
#define	GPIO_PORT_595_R1		GPIO_PORT_IN_G1    //
#define	GPIO_PORT_595_G1		GPIO_PORT_IN_R1    //
#define	GPIO_PORT_595_RCK		GPIO_PORT_RCK
#define	GPIO_PORT_595_CLK		GPIO_PORT_CLK

#define	GPIO_PIN_595_R2		GPIO_PIN_IN_R2
#define	GPIO_PIN_595_G2		GPIO_PIN_IN_G2
#define	GPIO_PIN_138_A		GPIO_PIN_A
#define	GPIO_PIN_138_B			GPIO_PIN_B
#define	GPIO_PIN_138_C			GPIO_PIN_C
#define	GPIO_PIN_138_D		GPIO_PIN_D
#define	GPIO_PIN_138_E			GPIO_PIN_IN_E
#define	GPIO_PIN_595_G1		GPIO_PIN_IN_R1     // �����Ƿ���
#define	GPIO_PIN_595_R1		GPIO_PIN_IN_G1    //
#define	GPIO_PIN_595_RCK		GPIO_PIN_RCK
#define	GPIO_PIN_595_CLK		GPIO_PIN_CLK


 #define 	set_CLK()		{GPIO_SetBits(GPIO_PORT_595_CLK, GPIO_PIN_595_CLK);/*Delay(1);*/}
 #define 	clr_CLK()		{GPIO_ResetBits(GPIO_PORT_595_CLK, GPIO_PIN_595_CLK);/*Delay(1);*/}
 #define	set_RCK()		{GPIO_SetBits(GPIO_PORT_595_RCK, GPIO_PIN_595_RCK);/*Delay(1);*/}
 #define 	clr_RCK()		{GPIO_ResetBits(GPIO_PORT_595_RCK, GPIO_PIN_595_RCK);/*Delay(1);*/}
 

 #define 	set_GREEN1()	{GPIO_SetBits(GPIO_PORT_595_G1, GPIO_PIN_595_G1);/*Delay(1);*/}
 #define 	clr_GREEN1()	{GPIO_ResetBits(GPIO_PORT_595_G1, GPIO_PIN_595_G1);/*Delay(1);*/}
 #define	set_RED1()		{GPIO_SetBits(GPIO_PORT_595_R1, GPIO_PIN_595_R1);/*Delay(1);*/}
 #define 	clr_RED1()		{GPIO_ResetBits(GPIO_PORT_595_R1, GPIO_PIN_595_R1);/*Delay(1);*/}
 #define 	set_GREEN2()	{GPIO_SetBits(GPIO_PORT_595_G2, GPIO_PIN_595_G2);/*Delay(1);*/}
 #define 	clr_GREEN2()	{GPIO_ResetBits(GPIO_PORT_595_G2, GPIO_PIN_595_G2);/*Delay(1);*/}
 #define	set_RED2()		{GPIO_SetBits(GPIO_PORT_595_R2, GPIO_PIN_595_R2);/*Delay(1);*/}
 #define 	clr_RED2()		{GPIO_ResetBits(GPIO_PORT_595_R2, GPIO_PIN_595_R2);/*Delay(1);*/}


#define set_138A()		{GPIO_SetBits(GPIO_PORT_138_A, GPIO_PIN_138_A);/*Delay(1);*/}
#define clr_138A()		{GPIO_ResetBits(GPIO_PORT_138_A, GPIO_PIN_138_A);/*Delay(1);*/}

#define set_138B()		{GPIO_SetBits(GPIO_PORT_138_B, GPIO_PIN_138_B);/*Delay(1);*/}
#define clr_138B()		{GPIO_ResetBits(GPIO_PORT_138_B, GPIO_PIN_138_B);/*Delay(1);*/}

#define set_138C()		{GPIO_SetBits(GPIO_PORT_138_C, GPIO_PIN_138_C);/*Delay(1);*/}
#define clr_138C()		{GPIO_ResetBits(GPIO_PORT_138_C, GPIO_PIN_138_C);/*Delay(1);*/}

#define set_138D()		{GPIO_SetBits(GPIO_PORT_138_D, GPIO_PIN_138_D);/*Delay(1);*/}
#define clr_138D()		{GPIO_ResetBits(GPIO_PORT_138_D, GPIO_PIN_138_D);/*Delay(1);*/}

#define clr_138E()		{GPIO_SetBits(GPIO_PORT_138_E, GPIO_PIN_138_E);/*Delay(1);*/}
#define set_138E()		{GPIO_ResetBits(GPIO_PORT_138_E, GPIO_PIN_138_E);/*Delay(1);*/}


extern uint8 red[LED_COL_SUM][2];
extern uint8 green[LED_COL_SUM][2];

void Refresh_74HC595_status(void);
void Device_74HC595_init(void);
void HC595_GPIO_config(void);
void turn_off_screen_clrbuf(void);
void clr_led_buf(void);

#endif

