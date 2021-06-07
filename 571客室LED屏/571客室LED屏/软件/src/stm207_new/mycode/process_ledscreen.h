

#ifndef __process_ledscreen_h
#define __process_ledscreen_h


#define COLOR_NONE			0
#define COLOR_GREEN			2
#define COLOR_RED			1
#define COLOR_YELLOW		3


//注意修改

#define	FILL_ROLL_HEAD				(LED_COL_SUM-10)	  
#define	FILL_ROLL_TAIL				(LED_COL_SUM-1)	  
#define   LEDBUF_ROW_GRP			2

#define   LEDBUF_TMP1_COL_SUM		(MAX_REV_LEN/2)
#define   LEDBUF_TMP_COL_SUM		(FILL_ROLL_HEAD+LEDBUF_TMP1_COL_SUM+FILL_ROLL_TAIL)   
#define   LED_SUM_BYTE				288                   //32*9  9个字 //10个字32*10iiii

extern uint8	ledbuf_tmp1[LEDBUF_TMP1_COL_SUM][LEDBUF_ROW_GRP];	//显示数据备份,协议包数据的直接拷贝
extern uint8	ledbuf_tmp[LEDBUF_TMP_COL_SUM][LEDBUF_ROW_GRP];	//显示数据备份
extern uint8	change_flag;

extern const uint8 software_version[4];
extern uint8 ptu_SetMode;

void screen_roll(uint16 roll_col_sum, uint8 color);

#endif




