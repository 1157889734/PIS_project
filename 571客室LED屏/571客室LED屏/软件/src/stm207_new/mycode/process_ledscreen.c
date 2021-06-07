#include "MyAll.h"



//������buf ������ͬ
uint8	ledbuf_tmp1[LEDBUF_TMP1_COL_SUM][LEDBUF_ROW_GRP];	//��ʾ���ݱ���,Э������ݵ�ֱ�ӿ���
uint8	ledbuf_tmp[LEDBUF_TMP_COL_SUM][LEDBUF_ROW_GRP];	//��ʾ���ݱ���
uint16	roll_col_sum_tmp = 0;			//��ʾ���������ֽ�������
uint8	color_tmp = COLOR_NONE;
uint16	roll_col_num = 0;


uint8 ptu_SetMode = 0;	//����ģʽ
extern uint8 download_flag;
extern uint16 NetDispLen;
//����ܱ䶯.����ܷ�������.svn source code version ǧ��λ.svn source code versionʮ��λ
const uint8 software_version[4] = {1, 1, 16, 53};


//����ʱ��
const char build_date_str[]	=__DATE__;	//���ڸ�ʽ��"Dec 22 2010"    ����������ĺ�
//const char build_date_str[]=__DATE2__;	//���ڸ�ʽ��"12/22/10"
const char build_time_str[]	=__TIME__;	//ʱ���ʽ��"10:16:14"

void screen_roll(uint16 roll_col_sum, uint8 color)
{
	
	uint16	col_sum;								//��������������������������������������������������������������������
	uint16	fill_colsum_head;		//ledbuf_tmpͷ�����Ŀ�����
	
	fill_colsum_head = FILL_ROLL_HEAD;


//�����������Ƿ��и���
//��,�����´������濪ʼ���

	if(download_flag)
	{
		if(NetDispLen>9216)
		{
			NetDispLen=9216;
		}
		if(memcmp(ledbuf_tmp[fill_colsum_head], ledbuf_tmp1[0], NetDispLen) !=0|| ((color_tmp != color))||(roll_col_sum_tmp != roll_col_sum))	//memcmp ���Ϊ0
		{
			roll_col_sum_tmp = roll_col_sum;
			color_tmp = color;
			memset(red, 0xff, sizeof(red));
			memset(green, 0xff, sizeof(green));
			// ��ʱ�������㲢�����ֵ
			memset(ledbuf_tmp, 0xff, sizeof(ledbuf_tmp));
			memcpy(ledbuf_tmp[fill_colsum_head], ledbuf_tmp1[0], NetDispLen);//roll_col_sum_tmp*LEDBUF_ROW_GRP);						
			roll_col_num = 0;
		}
	}

	//�����ܵ�����
	col_sum =  roll_col_sum_tmp + fill_colsum_head;


	//��ɫ�ж�
	if ((color_tmp != COLOR_RED) && (color_tmp != COLOR_GREEN) && (color_tmp != COLOR_YELLOW)) {
		//��ɫ��Ч�����ʾ
		memset(red, 0xff, sizeof(red));
		memset(green, 0xff, sizeof(green));
		
	}
	else {
		switch (color_tmp) {
			
		case COLOR_GREEN:
			memcpy(green, ledbuf_tmp[roll_col_num], LED_SUM_BYTE);  //����һ����320���ֽ�
			break;
					
		case COLOR_RED:
			
			memcpy(red, ledbuf_tmp[roll_col_num], LED_SUM_BYTE);  
			break;
					
		case COLOR_YELLOW:
			memcpy(green, ledbuf_tmp[roll_col_num], LED_SUM_BYTE);
			memcpy(red, ledbuf_tmp[roll_col_num], LED_SUM_BYTE);
			break;
					
		default:
			break;
		}
		
	}


	//memcpy(&green[0][0], &green_tmp[0][0], sizeof(green));
	//memcpy(&red[0][0], &red_tmp[0][0], sizeof(red));


	// ����Դ���ݵ��к�
	//roll_col_num += div;
	roll_col_num++;
	if (roll_col_num >= col_sum) {
		roll_col_num = 0;
		
		if(change_flag)
		{
			change_flag=0;
		}
		else
		{
			change_flag=1;	
		}

	}
	
	
}
#if 0
typedef struct {
	uint8 mode;
	uint8 *param;
	uint16 len;
}TAG_SEL_MODE;

TAG_SEL_MODE sel_screen_MODE = {
	SCREEN_MODE_softwareVersion,
	NULL,
	0
};
#endif


#if 0
void LedScreen_process(void)
{
	uint8 index;
	uint8 new_mode;
	uint8 flag;
//	static uint16 col;
	static TAG_SEL_MODE mode_tmp = {0, 0, 0};
	static uint8 tmp = 1;
//	static uint16 cnt = 0;
	//static uint32 timer_1 = 0;
	//static uint8 mode_index = 0;

	if (tmp) {
		
		tmp =0;
		memset(&sel_screen_MODE, 0, sizeof(sel_screen_MODE));
		set_dispmode(mode_index_tbl[0]);
		//set_dispmode(0);
	}

#if 0
	if (timer0_check_timer(&timer_1, (uint32)TIMING_10s)) {
		mode_index++;
		if (mode_index >= sizeof(mode_index_tbl)) {
			mode_index = 0;
		}
		set_dispmode(mode_index_tbl[mode_index]);
	}
#endif

	index = 0;
	flag = 0;

	while (screen_mode_disp_tbl[index].screen_dispMode_Callback != NULL) {
		if (screen_mode_disp_tbl[index].mode == sel_screen_MODE.mode) {
			if (memcmp(&mode_tmp, &sel_screen_MODE,sizeof(TAG_SEL_MODE)) == 0) {
				new_mode = 0;
			}
			else {
				memcpy(&mode_tmp, &sel_screen_MODE,sizeof(TAG_SEL_MODE));
				new_mode = 1;
			}
			screen_mode_disp_tbl[index].screen_dispMode_Callback(new_mode, sel_screen_MODE.param, sel_screen_MODE.len);
			flag = 1;
			break;
		}
		index++;
	}

	if (!flag) {
		turn_off_screen_clrbuf();
	}
	else {
		/*
		if(refresh_flag)
		{
			refresh_flag = 0;
			screen_roll(col, COLOR_RED);
		}*/
		
		if(timer2_flag)
		{
			timer2_flag = 0;
			Refresh_74HC595_status();
		}
	}
	
}  

#endif














