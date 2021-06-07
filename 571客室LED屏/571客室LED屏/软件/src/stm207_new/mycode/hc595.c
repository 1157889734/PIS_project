#include "MyAll.h"
#include "stm32f2xx_gpio.h"

#define	NOselect138_No	17


uint8 red[LED_COL_SUM][2];
uint8 green[LED_COL_SUM][2];


typedef struct 
{
	uint8  row_index;
	
	struct 
	{
		uint8	d	:1;
		uint8	e	:1;
		uint8	c	:1;
		uint8	b	:1;
		uint8	a	:1;
		uint8	res	:3;
	}status;

}TAG_LED_ROW_SELECT;

const TAG_LED_ROW_SELECT led_row_select[] = {
	{1,		{0,	0,	0,	0,	0,	7}	},	//L1,17
	{2,		{0,	0,	0,	0,	1,	7}	},	//L2,18
	{3,		{0,	0,	0,	1,	0,	7}	},	//L3,19
	{4,		{0,	0,	0,	1,	1,	7}	},	//L4,20
	{5,		{0,	0,	1,	0,	0,	7}	},	//L5,21
	{6,		{0,	0,	1,	0,	1,	7}	},	//L6,22
	{7,		{0,	0,	1,	1,	0,	7}	},	//L7,23
	{8,		{0,	0,	1,	1,	1,	7}	},	//L8,24
	{9,		{1,	0,	0,	0,	0,	7}	},	//L9
	{10,		{1,	0,	0,	0,	1,	7}	},	//L10
	{11,		{1,	0,	0,	1,	0,	7}	},	//L11
	{12,		{1,	0,	0,	1,	1,	7}	},	//L12
	{13,		{1,	0,	1,	0,	0,	7}	},	//L13
	{14,		{1,	0,	1,	0,	1,	7}	},	//L14
	{15,		{1,	0,	1,	1,	0,	7}	},	//L15
	{16,		{1,	0,	1,	1,	1,	7}	},	//L16
	{17,		{1,	1,	0,	0,	0,	7}	},	//不选择
	{NULL,	{1,	1,	0,	0,	0,	7}	},	//不选择
		
};

void clr_led_buf(void)
{

	memset(red, 0xff, sizeof(red));
	memset(green, 0xff, sizeof(green));
}

void turn_off_screen_clrbuf(void)
{
	set_138E();
	clr_led_buf();
	
}

//n>16 no select
void select_138(uint8 n)
{
	//uint8 index;

	//index = 0;
	//while (led_row_select[index].row_index != NULL) {
		//if (led_row_select[index].row_index == n) {
		
		if (led_row_select[(n -1)].status.a) {
			set_138A();
		}
		else {
			clr_138A();
		}

		if (led_row_select[(n -1)].status.b) {
			set_138B();
		}
		else {
			clr_138B();
		}

		if (led_row_select[(n -1)].status.c) {
			set_138C();
		}
		else {
			clr_138C();
		}

		if (led_row_select[(n -1)].status.d) {
			set_138D();
		}
		else {
			clr_138D();
		}
		if (led_row_select[(n -1)].status.e) {
			set_138E();
		}
		else {
			clr_138E();
		}

#if 0
			if (led_row_select[(n -1)].status.e) {
				set_138E();
			}
			else {
				clr_138E();
			}
#endif
			//break;
		//}

	//}
}


void Device_74HC595_init(void)
{
	clr_CLK();
	clr_RCK();
}


void HC595_GPIO_config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
  	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7
			| GPIO_Pin_8
			|GPIO_Pin_9
			|GPIO_Pin_10
			|GPIO_Pin_11
			|GPIO_Pin_12
			|GPIO_Pin_13
			|GPIO_Pin_14
			|GPIO_Pin_15;


	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12
			|GPIO_Pin_13;*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10
			|GPIO_Pin_11;

	GPIO_Init(GPIOB, &GPIO_InitStructure);


	Device_74HC595_init();

	select_138(NOselect138_No);

	clr_led_buf();


}

#if 0
//驱动LED屏显示中文站名
void prc_disp_CN_Station_Content()
{
	u8 i,j;
	u8 tmp=0x00;
	for(i=1;i<17;i++)
		for(j=1;j<NetCNDispLen/16+1;j++)
		{
			get_send_cn_data(i,j,&tmp);
			//发送给595进行显示
		}
	
}

//驱动LED屏显示英文内容
void prc_disp_EN_Station_Content()
{
	u8 i,j;
	u8 tmp=0x00;
	for(i=1;i<9;i++)
		for(j=1;j<NetENDispLen/8+1;j++)
		{
			get_send_en_data(i,j,&tmp);
			//发送给595进行显示
		}
}	


//获取发往芯片显示的英文数据 ,row表示行号，offset表示要显示的起始列数/8
u8 get_send_en_data(u8 row;u8 offset,u8& data)
{
	u8 i;
	u8 tmp=0x00;
	u8 t1;
	if(row>8 || row<1)	
	{
		return -1;
	}
	if(offset*8>NetENDispLen/2 || offset<1)
	{
		return -1;
	}
	offset=	(offset-1)*8;	//计算出取数据的起始指针
	for(i=0;i<8;i++)
	{
		 t1= NetENDispCont[offset+i];
		 t1=t1 &(0x01<<(9-row));
		 t1=t1<<(row-1);
		 tmp=tmp+(t1>>i);
		
	}
	data=tmp;
	return 0;
}

#endif

extern uint8 refresh_flag;


//**************显示扫描*********************
void Refresh_74HC595_status(void)
{
	static uint8	line_No = 1;
	uint8  i;
	uint8 mask = 0, offset = 0;
	//static uint8 line = 1;
	//static uint8 add_value = 1;

#if 0
	uint8*  green_status;
	uint8*  red_status;
	
	if(line_No)
	{
		green_status = green[line_No - 1];
		red_status = red[line_No - 1];
	}

	for (i = 0; i < COL_BYTE_SUM; i++) {
		
		for (j = 0; j < 8; j++) {
			
			if ((green_status[i] >> j) & 0x01) {
				set_GREEN1();
			}
			else {
				clr_GREEN1();
			}

			if ((red_status[i] >> j) & 0x01) {
				set_RED1();
			}
			else {
				clr_RED1();
			}

			set_CLK();
			clr_CLK();
		}
	
	}
#else
	mask = 0x01 << (7 - (line_No-1)%8);;	/////1 << ((line_No - 1) % 8);
	offset = (line_No - 1) /8;
	
	//memset(green, 0xFF, 320);
	for (i = 0; i < LED_COL_SUM; i++)
	{
		if(green[i][offset] & mask)
		{
			set_GREEN1();
		}
		else
		{
			clr_GREEN1();
		}
		//clr_GREEN1();

		if(red[i][offset] & mask)
		{
			set_RED1();
		}
		else
		{
			clr_RED1();
		} 

		set_CLK();
		clr_CLK();
	}
#endif
	
	//select_138(17);
	set_138E();
	Delay(1);	

	set_RCK();
	clr_RCK();
	
	select_138(line_No);
	//Delay(20);
	
	line_No++;
	if(line_No > 16) {
		line_No = 1;
	}

	if ((line_No % 16) == 1)
	{
		refresh_flag = 1;
		
	}
}



//**************显示扫描*********************
/*
void Refresh_74HC595_status(uint8 *green_status, uint8 *red_status,uint8 len)
{
	static uint8	line_No = 0;
	uint8	i, j;

	//select_138(NOselect138_No);
	
	for (i = 0; i < len; i++) {
		for (j = 0; j < 8; j++) {
			if ((green_status[i] >> j) & 0x01) {
				set_GREEN();
			}
			else {
				clr_GREEN();
			}

			if ((red_status[i] >> j) & 0x01) {
				set_RED();
			}
			else {
				clr_RED();
			}

			set_CLK();
			clr_CLK();
		}
	
	}

	
	select_138(line_No);

	set_RCK();
	clr_RCK();
	line_No++;
	if(line_No > 16) {
		line_No = 1;
	}
	
}*/

