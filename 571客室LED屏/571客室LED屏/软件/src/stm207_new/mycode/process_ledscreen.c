#include "MyAll.h"



//ÕâÁ½¸öbuf ³¤¶ÈÏàÍ¬
uint8	ledbuf_tmp1[LEDBUF_TMP1_COL_SUM][LEDBUF_ROW_GRP];	//ÏÔÊ¾Êý¾Ý±¸·Ý,Ð­Òé°üÊý¾ÝµÄÖ±½Ó¿½±´
uint8	ledbuf_tmp[LEDBUF_TMP_COL_SUM][LEDBUF_ROW_GRP];	//ÏÔÊ¾Êý¾Ý±¸·Ý
uint16	roll_col_sum_tmp = 0;			//ÏÔÊ¾Êý¾Ý×ÝÏò×Ö½ÚÊý±¸·Ý
uint8	color_tmp = COLOR_NONE;
uint16	roll_col_num = 0;


uint8 ptu_SetMode = 0;	//Õý³£Ä£Ê½
extern uint8 download_flag;
extern uint16 NetDispLen;
//Ö÷¿ò¼Ü±ä¶¯.Ö÷¿ò¼Ü·¢²¼´ÎÊý.svn source code version Ç§°ÙÎ».svn source code versionÊ®¸öÎ»
const uint8 software_version[4] = {1, 1, 16, 53};


//±àÒëÊ±¼ä
const char build_date_str[]	=__DATE__;	//ÈÕÆÚ¸ñÊ½£º"Dec 22 2010"    ±àÒëÆ÷¶¨ÒåµÄºê
//const char build_date_str[]=__DATE2__;	//ÈÕÆÚ¸ñÊ½£º"12/22/10"
const char build_time_str[]	=__TIME__;	//Ê±¼ä¸ñÊ½£º"10:16:14"

void screen_roll(uint16 roll_col_sum, uint8 color)
{
	
	uint16	col_sum;								//×ÜÁÐÊý¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾¡¾
	uint16	fill_colsum_head;		//ledbuf_tmpÍ·²¿Ìî³äµÄ¿ÕÁÐÊý
	
	fill_colsum_head = FILL_ROLL_HEAD;


//»º³åÇøÊý¾ÝÊÇ·ñÓÐ¸üÐÂ
//ÓÐ,ÔòÖØÐÂ´Ó×îÓÒÃæ¿ªÊ¼¹öÆ

	if(download_flag)
	{
		if(NetDispLen>9216)
		{
			NetDispLen=9216;
		}
		if(memcmp(ledbuf_tmp[fill_colsum_head], ledbuf_tmp1[0], NetDispLen) !=0|| ((color_tmp != color))||(roll_col_sum_tmp != roll_col_sum))	//memcmp ÏàµÈÎª0
		{
			roll_col_sum_tmp = roll_col_sum;
			color_tmp = color;
			memset(red, 0xff, sizeof(red));
			memset(green, 0xff, sizeof(green));
			// ÁÙÊ±»º´æÇåÁã²¢Ìî³äÐÂÖµ
			memset(ledbuf_tmp, 0xff, sizeof(ledbuf_tmp));
			memcpy(ledbuf_tmp[fill_colsum_head], ledbuf_tmp1[0], NetDispLen);//roll_col_sum_tmp*LEDBUF_ROW_GRP);						
			roll_col_num = 0;
		}
	}

	//¼ÆËã×ÜµÄÁÐÊý
	col_sum =  roll_col_sum_tmp + fill_colsum_head;


	//ÑÕÉ«ÅÐ¶Ï
	if ((color_tmp != COLOR_RED) && (color_tmp != COLOR_GREEN) && (color_tmp != COLOR_YELLOW)) {
		//ÑÕÉ«ÎÞÐ§Çå¿ÕÏÔÊ¾
		memset(red, 0xff, sizeof(red));
		memset(green, 0xff, sizeof(green));
		
	}
	else {
		switch (color_tmp) {
			
		case COLOR_GREEN:
			memcpy(green, ledbuf_tmp[roll_col_num], LED_SUM_BYTE);  //¿½±´Ò»ÆÁ¹²320¸ö×Ö½Ú
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


	// µ÷ÕûÔ´Êý¾ÝµÄÁÐºÅ
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














