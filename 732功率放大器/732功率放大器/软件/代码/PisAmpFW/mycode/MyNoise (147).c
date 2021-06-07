
//*****************************************************//
//      MyNoise.c
//*****************************************************//

#include "MyAll.h"


int NoiseTable_dB[40] = {62, 63, 67,  68, 70, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 89, 90, 92, 94, 95, 96.5, 98, 99.5, 102, 103.5, 105, 106.5, 108, 109.5};

//int NoiseTable_Adv[12] =  {12, 25, 40, 60, 80, 100, 140, 170, 260, 400, 800, 1800};

int NoiseTable_Adv[40] = {12, 18, 21,  32, 40, 50, 60, 65 , 70, 75, 80, 90, 100, 110, 120, 130, 140, 150, 152, 156, 158, 160, 164, 165, 170, 180, 190, 195, 200};

//int NoiseTable_Adv[12] =  {12, 25, 40, 60, 85, 135, 200, 240, 300, 500, 1000, 1800};

//int NoiseTable_SampleV[12]={10, 60, 150, 300, 500, 700, 900, 1200, 1500, 2000, 2500, 3000};

int NoiseTable_SampleV[12] = {10, 60, 150, 300, 500, 700, 900, 1100, 1300, 1500, 1700, 1900};

int NoiseMode;

int MyNoise1SampleFlag ;

int Noise12BufIndex;

int Noise1Value;
int Noise2Value;

int Noise1DB;
int Noise2DB;

int NoiseDB;

int NoiseMyDB;
int NoiseOtherDB;

///////////////////////////////////////////////////

int NoiseNewMyValue;
int NoiseNewMyDb;

int NoiseNewSensor1Buf[100];
int NoiseNewSensor2Buf[100];
int NoiseNewSensorBufIndex;

int NoiseNewSensor1Value;
int NoiseNewSensor2Value;

int NoiseNewSensor1Db;
int NoiseNewSensor2Db;

int NoiseNewSensorDb;

int NoiseNewOtherDb;

////////////////////////////////////////////////////

u32 Noise1Buf[SAMPLE_NUM];
u32 Noise2Buf[SAMPLE_NUM];


void NoiseInit(void)
{
}

void Noise10ms(void)
{
    /*
        int i;
        int sum;
    
    
        Noise1Buf[Noise12BufIndex] = AdcNewGetValue1();
    
        Noise2Buf[Noise12BufIndex] = AdcNewGetValue2();
    
        Noise12BufIndex ++;
    
        if(Noise12BufIndex >= 100)
        {
            Noise12BufIndex = 0;
    
            sum = 0;
            for(i=0; i<100; i=i++)
            {
                sum = sum + Noise1Buf[i];
    
            }
    
            Noise1Value = sum / 100;
    
    
            sum = 0;
            for(i=0; i<30; i=i++)
            {
                sum = sum + Noise2Buf[i];
    
            }
    
            Noise2Value = sum / 100;
    
    
    
            Noise1DB = Noise1Value;
            Noise2DB = Noise2Value;
    
            Noise1DB = NoiseGetDB(Noise1Value);
            Noise2DB = NoiseGetDB(Noise2Value);
    
    
            if(NoiseDetectState == NDSTATE_NULL)
            {
                NoiseDB = 0;
    
            }
            else if(NoiseDetectState == NDSTATE_ONLY1)
            {
                NoiseDB = Noise1DB;
    
            }
            else if(NoiseDetectState == NDSTATE_ONLY2)
            {
                NoiseDB = Noise2DB;
    
            }
            else if(NoiseDetectState == NDSTATE_BOTH)
            {
                if(Noise1DB > Noise2DB)
                {
                    NoiseDB = Noise1DB;
    
                }
                else
                {
                    NoiseDB = Noise2DB;
    
                }
    
            }
    
    
    //      NoiseMyDB = NoiseGetMyDB();
    
    //      CommanderSendMyNoise(NoiseMyDB);
    
    //      NoiseOtherDB = NoiseCalculateOtherDB(NoiseDB, NoiseMyDB);
    
    //      AudioSetNdOffset(NoiseOtherDB);
    
    
    //      CommanderSendMyNoise(NoiseDB);
    
            AudioSetNdOffset(NoiseDB);
    
    
    
        }
    
    */
}

//char abcd[512];

void  Noise25ms(void)
{
	int i = 0;
	int sum = 0;
	int num = 0;
	
    MyNoise1SampleFlag ++;
    Noise1Buf[Noise12BufIndex] = AdcGetFilterValue1();
    Noise2Buf[Noise12BufIndex] = AdcGetFilterValue2();
	
	//sprintf(abcd, "===========noise is %d, %d\n", Noise1Buf[Noise12BufIndex], Noise2Buf[Noise12BufIndex]);
    //CommanderSendString(abcd);
    
    Noise12BufIndex ++;
    
    if (Noise12BufIndex >= SAMPLE_NUM)
    {
    	for (i = 0; i < SAMPLE_NUM; i++)
    	{
			sum = sum + Noise1Buf[i];
			num++;
		}

		Noise1DB = sum / num;
		sum = 0;
		num = 0;

		for (i = 0; i < SAMPLE_NUM; i++)
    	{
			sum = sum + Noise2Buf[i];
			num++;
		}
		Noise2DB = sum / num;
		
        Noise12BufIndex = 0;

		Noise1DB = (20*log10(Noise1DB / 40) + 60);//使噪音和db值成线性关系
		Noise2DB = (20*log10(Noise2DB / 40) + 60);//使噪音和db值成线性关系

//		sprintf(abcd, "noise is %d, %d\n", Noise1DB, Noise2DB);
//       CommanderSendString(abcd);
#if 0		
        Noise1Value = (int)AdcMedianFilterValue1();
        Noise2Value = (int)AdcMedianFilterValue2();
        Noise1DB = NoiseGetDB(Noise1Value);
        Noise2DB = NoiseGetDB(Noise2Value);
#endif
        
        if (NoiseDetectState == NDSTATE_NULL)
        {
            NoiseDB = 0;
            MyNoiseSampleFlag = NoiseDB;
        }
        else if (NoiseDetectState == NDSTATE_ONLY1)
        {
            NoiseDB = Noise1DB;
            MyNoiseSampleFlag = NoiseDB;
        }
        else if (NoiseDetectState == NDSTATE_ONLY2)
        {
            NoiseDB = Noise2DB;
            MyNoiseSampleFlag = NoiseDB;
        }
        else if (NoiseDetectState == NDSTATE_BOTH)
        {
            if (Noise1DB > Noise2DB)
            {
                NoiseDB = Noise1DB;
            }
            else
            {
                NoiseDB = Noise2DB;
            }
            
            MyNoiseSampleFlag = NoiseDB;
        }
        
        //    NoiseMyDB = NoiseGetMyDB();
        //    CommanderSendMyNoise(NoiseMyDB);
        //    NoiseOtherDB = NoiseCalculateOtherDB(NoiseDB, NoiseMyDB);
        //    AudioSetNdOffset(NoiseOtherDB);
        //    CommanderSendMyNoise(NoiseDB);
        //    AudioSetNdOffset(NoiseDB);
    }
}

void Noise100ms(void)
{
    //  NoiseNewGetMyDB();
    //  NoiseNewProsess();
}



void Noise1000ms(void)
{
    NoiseGet3sSmoothingFilterValue();
}


int NoiseGetDB(int adv)
{
    int odb;
    int i;
    int flag;
    i = 0;
    flag = 0;
    
    //  adv = adv ;
    while ((flag == 0) && (i < 20))
    {
        if (adv <= NoiseTable_Adv[i])
        {
            odb = NoiseTable_dB[i];
            flag = 1;
        }
        
        i++;
    }
    
    if (flag == 0)
    {
        odb = 95;
    }
    
    return odb;
}


int NoiseGetMyDB(void)
{
    int odb;
    int i;
    int flag;
    i = 0;
    flag = 0;
    
    while ((flag == 0) && (i < 10))
    {
        if (SampleV <= NoiseTable_SampleV[i])
        {
            odb = NoiseTable_dB[i];
            flag = 1;
        }
        
        i++;
    }
    
    if (flag == 0)
    {
        odb = 95;
    }
    
    odb = odb + 3;
    
    if (odb > 100)
    {
        odb = 95;
    }
    
    return odb;
}



int NoiseCalculateOtherDB(int total_db, int my_db)
{
    int other_db;
    static int s_no_speak_flag = 0;
    static int s_original_noise;
    other_db = 0;
    
    if ((total_db > 100) || (total_db < 60))
    {
        return 0;
    }
    
    if ((my_db > 100) || (my_db < 60))
    {
        return 0;
    }
    
    if (my_db <= 65)
    {
        s_no_speak_flag ++;
    }
    else
    {
        s_no_speak_flag = 0;
    }
    
    if (s_no_speak_flag > 3)
    {
        other_db = total_db;
        s_original_noise = total_db;
        CommanderSendString("aaa\n");
    }
    else
    {
        if (total_db <= (my_db - 15))
        {
            other_db = total_db;
            CommanderSendString("bbb\n");
        }
        else if (total_db <= (my_db - 6))
        {
            other_db = s_original_noise;
            CommanderSendString("bbb\n");
        }
        else if (total_db <= my_db)
        {
            if (my_db > 79)
            {
                other_db = s_original_noise;
                CommanderSendString("ccc\n");
            }
            else
            {
                other_db = s_original_noise;
                CommanderSendString("ddd\n");
            }
        }
        else if (total_db <= (my_db + 3))
        {
            if (my_db > 79)
            {
                other_db = s_original_noise;
                CommanderSendString("eee1\n");
            }
            else
            {
                other_db = s_original_noise;
                CommanderSendString("eee2\n");
            }
        }
        else if (total_db <= (my_db + 6))
        {
            if (my_db > 83)
            {
                other_db = s_original_noise;
                CommanderSendString("fff\n");
            }
            else if (my_db > 79)
            {
                other_db = s_original_noise;
                CommanderSendString("fff1\n");
            }
            else
            {
                other_db = s_original_noise;
                CommanderSendString("fff2\n");
            }
        }
        else if (total_db <= (my_db + 9))
        {
            if (my_db > 83)
            {
                other_db = s_original_noise;
                CommanderSendString("ggg\n");
            }
            else if (my_db > 79)
            {
                other_db = s_original_noise;
                CommanderSendString("ggg1\n");
            }
            else
            {
                other_db = s_original_noise;
                CommanderSendString("ggg2\n");
            }
        }
        else if (total_db <= (my_db + 12))
        {
            if (my_db > 83)
            {
                other_db = s_original_noise;
                CommanderSendString("hhh\n");
            }
            
            if (my_db > 79)
            {
                other_db = s_original_noise;
                CommanderSendString("hhh1\n");
            }
            else
            {
                other_db = total_db - 9;
                CommanderSendString("hhh2\n");
            }
        }
        else if (total_db <= (my_db + 15))
        {
            if (my_db > 83)
            {
                other_db = s_original_noise;
                CommanderSendString("iii\n");
            }
            
            if (my_db > 79)
            {
                other_db = total_db - 12;
                CommanderSendString("iii1\n");
            }
            else
            {
                other_db = total_db - 9;
                CommanderSendString("iii2\n");
            }
        }
        else if (total_db <= (my_db + 18))
        {
            if (my_db > 83)
            {
                other_db = s_original_noise;
                CommanderSendString("jjj\n");
            }
            
            if (my_db > 79)
            {
                other_db = total_db - 9;
                CommanderSendString("jjj1\n");
            }
            else
            {
                other_db = total_db - 6;
                CommanderSendString("jjj2\n");
            }
        }
        else
        {
            other_db = total_db - 3;
            CommanderSendString("kkk\n");
        }
    }
    
    return other_db;
}


