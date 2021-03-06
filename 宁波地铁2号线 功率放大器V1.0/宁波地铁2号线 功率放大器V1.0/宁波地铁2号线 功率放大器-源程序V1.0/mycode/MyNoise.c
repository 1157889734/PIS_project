
//*****************************************************//
//		MyNoise.c
//*****************************************************//


#include "MyAll.h"





int NoiseTable_dB[12] =  	{62,	65, 	68, 	71, 	74, 	77, 	80, 	83, 	86, 	89, 	92, 	95};

int NoiseTable_Adv[12] = 	{12, 	25, 	40, 	60, 	85, 	135, 	200, 	240, 	300, 	500, 	1000, 1800};

//int NoiseTable_SampleV[12]={10,	60, 	150, 	300, 	500, 	700, 	900,	1200,1500,2000,2500,3000};

int NoiseTable_SampleV[12]={10,	60, 	150, 	300, 	500, 	700, 	900,	1100,1300,1500,1700,1900};





int Noise1Buf[100];
int Noise2Buf[100];

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







void NoiseInit(void)
{

	


}




void Noise10ms(void)
{

	int i;
	int sum;


	Noise1Buf[Noise12BufIndex] = AdcGetFilterValue1();

	Noise2Buf[Noise12BufIndex] = AdcGetFilterValue2();


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

		
//		NoiseMyDB = NoiseGetMyDB();

//		CommanderSendMyNoise(NoiseMyDB);

//		NoiseOtherDB = NoiseCalculateOtherDB(NoiseDB, NoiseMyDB);

//		AudioSetNdOffset(NoiseOtherDB);



		AudioSetNdOffset(NoiseDB);
		


	}




}


void Noise100ms(void)
{

//	NoiseNewGetMyDB();

	NoiseNewProsess();


}





int NoiseGetDB(int adv)
{
	int odb;

	int i;
	int flag;

	i = 0;
	flag = 0;

	while((flag == 0) && (i < 10))
	{
		if(adv<=NoiseTable_Adv[i])
		{
			odb = NoiseTable_dB[i];

			flag = 1;
		}

		i++;

	}

	if(flag == 0)
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

	while((flag == 0) && (i < 10))
	{
		if(SampleV <= NoiseTable_SampleV[i])
		{
			odb = NoiseTable_dB[i];

			flag = 1;
		}

		i++;

	}

	if(flag == 0)
	{
		odb = 95;

	}

	odb = odb + 3;
	if(odb > 100)
	{
		odb = 95;

	}

	return odb;

}



int NoiseCalculateOtherDB(int total_db, int my_db)
{
	int other_db;

	static int no_speak_flag = 0;

	static int original_noise;


	other_db = 0;

	if((total_db > 100) || (total_db < 60))
	{
		return 0;

	}

	if((my_db > 100) || (my_db < 60))
	{
		return 0;

	}
	

	if(my_db <= 65)
	{
		no_speak_flag ++; 
			
	}
	else
	{
		no_speak_flag = 0;

	}


	if(no_speak_flag > 3)
	{

		other_db = total_db;

		original_noise = total_db;

		CommanderSendString("aaa\n");

	}
	else
	{
		if(total_db <= (my_db-15))
		{
			other_db = total_db;

			CommanderSendString("bbb\n");

		}
		else if(total_db <= (my_db-6))
		{
			other_db = original_noise;

			CommanderSendString("bbb\n");

		}
		else if(total_db <= my_db)
		{
			if(my_db > 79)
			{
				other_db = original_noise;

				CommanderSendString("ccc\n");

			}
			else
			{
				other_db = original_noise;

				CommanderSendString("ddd\n");

			}

		}
		else if(total_db <= (my_db+3))
		{
			if(my_db > 79)
			{
				other_db = original_noise;

				CommanderSendString("eee1\n");

			}
			else
			{
				other_db = original_noise;

				CommanderSendString("eee2\n");

			}

		}
		else if(total_db <= (my_db+6))
		{
			if(my_db > 83)
			{
				other_db = original_noise;

				CommanderSendString("fff\n");

			}
			else if(my_db > 79)
			{
				other_db = original_noise;

				CommanderSendString("fff1\n");

			}
			else
			{
				other_db = original_noise;

				CommanderSendString("fff2\n");

			}
		}
		else if(total_db <= (my_db+9))
		{
			if(my_db > 83)
			{
				other_db = original_noise;

				CommanderSendString("ggg\n");

			}
			else if(my_db > 79)
			{
				other_db = original_noise;
				CommanderSendString("ggg1\n");

			}
			else
			{
				other_db = original_noise;

				CommanderSendString("ggg2\n");

			}

		}
		else if(total_db <= (my_db+12))
		{
			if(my_db > 83)
			{
				other_db = original_noise;

				CommanderSendString("hhh\n");

			}
			if(my_db > 79)
			{
				other_db = original_noise;

				CommanderSendString("hhh1\n");

			}
			else
			{
				other_db = total_db - 9;

				CommanderSendString("hhh2\n");

			}

		}
		else if(total_db <= (my_db+15))
		{
			if(my_db > 83)
			{
				other_db = original_noise;

				CommanderSendString("iii\n");

			}
			if(my_db > 79)
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
		else if(total_db <= (my_db+18))
		{
			if(my_db > 83)
			{
				other_db = original_noise;

				CommanderSendString("jjj\n");

			}
			if(my_db > 79)
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





int NoiseNewProsess(void)
{

	NoiseNewMyValue = AudioInputSampleV;


//	CommanderSendMyNoiseNew(NoiseNewMyValue);


	NoiseNewSensor1Value = AdcNewGetValue1();
	NoiseNewSensor2Value = AdcNewGetValue2();

//	CommanderSendSensorNoiseNew(NoiseNewSensor1Value, NoiseNewSensor2Value);


	return 0;

}


int NoiseNewGetMyDB(void)
{

	NoiseNewMyValue = AudioInputSampleV;


//	CommanderSendMyNoiseNew(NoiseNewMyValue);


	return 0;

}








