/**
  ******************************************************************************
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/


#include "MyAll.h"


static u16 s_RandCourt = 0;
u32 Debuger;

u32 tmp;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_stm32f2xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
          system_stm32f2xx.c file
       */
    //SystemInit();
    SysTick_Init();
	
	while(MyTmCnt5000ms <= 5000);

    RCC_Configuration();
    Delay(1000);
    GPIO_Configuration();
    Delay(1000);
    LED1On();
    LED2On();
    FeedDog();
    Delay(50000);
    Delay(50000);
    FeedDog();
    Delay(50000);
    Delay(50000);
    FeedDog();
    Delay(10000);
    LED1Off();
    LED2Off();
    FeedDog();
    Delay(100000);
    LED1On();
    LED2On();
    FeedDog();
    Delay(10000);
    AppInit();
    StorageInit();
    NetInit();
    Delay(1000);
    TftpClientInit();
    Delay(1000);
    AudioInit();
    Delay(1000);
    FeedDog();
    Delay(10000);
    Delay(10000);
    Delay(10000);
    StorageInfoRead();
    FeedDog();
    Delay(10000);
    DevId = Addr;
	
    tmp = FlashReadWord(ADDR_FLASH_SECTOR_5);
    
    if (tmp != 0xffffffff)
    {
        FlashInit();
    }
    
    while (1)
    {
        AppProcess();
        LwipProcess();
        NetProcess();
        AudioProcess();
        
        if (MyTmCnt10ms >= CNT_10MS)
        {
            MyTmCnt10ms = 0;
            MyTimer10();
        }
        
        if (MyTmCnt20ms >= CNT_20MS)
        {
            MyTmCnt20ms = 0;
            MyTimer20();
        }
        
        if (MyTmCnt25ms >= CNT_25MS)
        {
            MyTmCnt25ms = 0;
            MyTimer25();
        }
        
        if (MyTmCnt50ms >= CNT_50MS)
        {
            MyTmCnt50ms = 0;
            MyTimer50();
        }
        
        if (MyTmCnt100ms >= CNT_100MS)
        {
            MyTmCnt100ms = 0;
            MyTimer100();
        }
        
        if (MyTmCnt200ms >= CNT_200MS)
        {
            MyTmCnt200ms = 0;
            MyTimer200();
        }
        
        if (MyTmCnt500ms >= CNT_500MS)
        {
            MyTmCnt500ms = 0;
            MyTimer500();
            s_RandCourt = rand() % (CNT_500MS - 1) + 1;
        }
        else if (MyTmCnt500ms == s_RandCourt)
        {
            s_RandCourt = 0xffff;
            NetControlSendInspection();
			NetControlSendNoiseSensorState();
        }
        
        if (MyTmCnt1000ms >= CNT_1000MS)
        {
            MyTmCnt1000ms = 0;
            MyTimer1000();
        }
        
        if (MyTmCnt2000ms >= CNT_2000MS)
        {
            MyTmCnt2000ms = 0;
            MyTimer2000();
        }
    }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
