//*****************************************************//

//*****************************************************//

#include "MyAll.h"

int MyTmCnt10us;
int MyTmCnt250us;

int MyTmCnt10ms;
int MyTmCnt20ms;
int MyTmCnt25ms;

int MyTmCnt50ms;
int MyTmCnt100ms;
int MyTmCnt200ms;
int MyTmCnt500ms;
int MyTmCnt1000ms;
int MyTmCnt2000ms;

int MyTmCnt5000ms;

int MyNoiseSampleFlag;

extern u8 volume_1s;

void SysTick_Init(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
    /* Configure Systick clock source as HCLK */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    /* SystTick configuration: an interrupt every 10ms */
    RCC_GetClocksFreq(&RCC_Clocks);
    //SysTick_Config(RCC_Clocks.HCLK_Frequency / 100); // 10ms
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000); // 1ms
}


void SysTick_Isr(void)
{
    MyTmCnt10us++;
    MyTmCnt10ms++;
    MyTmCnt20ms++;
    MyTmCnt25ms++;
    MyTmCnt50ms++;
    MyTmCnt100ms++;
    MyTmCnt200ms++;
    MyTmCnt500ms++;
    MyTmCnt1000ms++;
    MyTmCnt2000ms++;	
	MyTmCnt5000ms++;
}


void TimerOff(void)
{
    SysTick->CTRL = ~(SysTick_CTRL_CLKSOURCE_Msk |
                      SysTick_CTRL_TICKINT_Msk |
                      SysTick_CTRL_ENABLE_Msk);
}


void Timer1_Init(void)
{
}


void Timer1_Isr(void)
{
}


void MyTimer25(void)
{
    Noise25ms();
}


void MyTimer10(void)
{
    Key10ms();
    Noise10ms();
    Audio10ms();
    App10ms();
}

void MyTimer20(void)
{
}

void MyTimer50(void)
{
    Net50ms();
    Lwip50ms();
}

void MyTimer100(void)
{
    App100ms();
    Audio100ms();
    
    if (AudioPlayInfo.EnableFlag > 0)
    {
        LED1Flash();
        LED2Flash();
    }
    
    StorageInfoSaveProcess();
    Key100ms();
    SelfTest100ms();
    Noise100ms();
    TftpClient100ms();
}


void MyTimer200(void)
{
    Audio200ms();
}


void MyTimer500(void)
{
    if (AudioPlayInfo.EnableFlag < 1)
    {
        LED1Flash();
        LED2Flash();
    }
    
    Net500ms();
    Audio500ms();
    Commander500ms();
    SelfTest500ms();
}


void MyTimer1000(void)
{
    static u8 s_volume_1s_bak = 0;
    App1000ms();
    Noise1000ms();
    
    if (s_volume_1s_bak != volume_1s)
    {
        s_volume_1s_bak = volume_1s;
        AudioSetVolume(volume_1s);
    }
}


void MyTimer2000(void)
{
}







