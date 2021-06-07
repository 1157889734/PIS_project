
//*****************************************************//
//      MyI2s.c
//*****************************************************//


#include "MyAll.h"




/* Mask for the bit EN of the I2S CFGR register */
#define I2S_ENABLE_MASK                 0x0400



u8 DmaPlayMem0[DMAPLAY_PACK_SIZE];
u8 DmaPlayMem1[DMAPLAY_PACK_SIZE];


u8 DmaListenMem0[DMALISTEN_PACK_SIZE];
u8 DmaListenMem1[DMALISTEN_PACK_SIZE];


int DmaPlayFlag;




void I2s2_Init(void)
{
    I2S_InitTypeDef I2S_InitStructure;
    RCC_I2SCLKConfig(RCC_I2S2CLKSource_Ext);
    //  RCC_PLLI2SConfig();
    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* CODEC_I2S peripheral configuration */
    SPI_I2S_DeInit(SPI2);
    I2S_InitStructure.I2S_AudioFreq = 44100;
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    /* Initialize the I2S peripheral with the structure above */
    I2S_Init(SPI2, &I2S_InitStructure);
    /* The I2S peripheral will be enabled only in the EVAL_AUDIO_Play() function
       or by user functions if DMA mode not enabled */
    I2S_Cmd(SPI2, ENABLE);
}



void I2s2Down(void)
{
    I2S_Cmd(SPI2, DISABLE);
    /* Enable the I2S DMA Stream*/
    DMA_Cmd(DMA1_Stream4, DISABLE);
    /* Enable the I2S DMA request */
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
}


void I2s2Up(void)
{
    I2S_Cmd(SPI2, ENABLE);
    /* Enable the I2S DMA Stream*/
    DMA_Cmd(DMA1_Stream4, ENABLE);
    /* Enable the I2S DMA request */
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
}






void DmaPlay_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the DMA clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    /* Configure the DMA Stream */
    DMA_Cmd(DMA1_Stream4, DISABLE);
    DMA_DeInit(DMA1_Stream4);
    DMA_DoubleBufferModeConfig(DMA1_Stream4, (u32)DmaPlayMem1, DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA1_Stream4, ENABLE);
    /* Set the parameters to be configured */
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4000380C;
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)DmaPlayMem0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = (u32)(DMAPLAY_PACK_SIZE / 2);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    //      DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream4, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);
    DMA_ITConfig(DMA1_Stream4, DMA_IT_HT, ENABLE);
    //  DMA_ITConfig(AUDIO_MAL_DMA_STREAM, DMA_IT_HT, ENABLE);
    //  DMA_ITConfig(AUDIO_MAL_DMA_STREAM, DMA_IT_TE | DMA_IT_FE | DMA_IT_DME, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Enable the I2S DMA Stream*/
    DMA_Cmd(DMA1_Stream4, ENABLE);
    /* Enable the I2S DMA request */
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
}





void DmaPlay_Isr(void)
{
    Debuger = Debuger;
    
    if (DMA_GetITStatus(DMA1_Stream4, DMA_IT_TCIF4) == SET)
    {
        DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);
        Debuger = Debuger;
        DmaPlayWriteLeft();
        DmaPlayWriteRight();
        DmaPlayFlag = 1;
        AudioPlayClockSend();
    }
    
    if (DMA_GetITStatus(DMA1_Stream4, DMA_IT_HTIF4) == SET)
    {
        DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_HTIF4);
        Debuger = Debuger;
    }
}




void DmaPlayWriteLeft(void)
{
    int i;
    s16 *pdest;
    s16 *psrc;
    
    if (DMA_GetCurrentMemoryTarget(DMA1_Stream4) == 0)
    {
        pdest = (s16 *)(DmaPlayMem1);
    }
    else
    {
        pdest = (s16 *)(DmaPlayMem0);
    }
    
    psrc = (s16 *)(pPlayLeftFifo + (PlayLeftConsumeIndex * PLAY_PACK_SIZE));
    
    for (i = 0; i < DMAPLAY_PACK_SIZE / 4; i++)
    {
        *(pdest + 2 * i) = *(psrc + i);
    }
    
    //  PlayLeftConsumeByteIndex = PlayLeftConsumeIndex * PLAY_PACK_SIZE;
    PlayLeftBytesToRead = PlayLeftBytesToRead - PLAY_PACK_SIZE;
    
    if (PlayLeftBytesToRead < 0)
    {
        PlayLeftBytesToRead = 0;
    }
    
    PlayLeftBytesToWrite = PlayLeftBytesToWrite + PLAY_PACK_SIZE;
    
    if (PlayLeftBytesToWrite > (PLAY_PACK_SIZE * PLAY_PACK_NUM))
    {
        PlayLeftBytesToWrite = (PLAY_PACK_SIZE * PLAY_PACK_NUM);
    }
    
    memset((u8 *)((u32)pPlayLeftFifo + (PlayLeftConsumeIndex * PLAY_PACK_SIZE)), 0, PLAY_PACK_SIZE);
    PlayLeftConsumeIndex = IndexAdd1(PlayLeftConsumeIndex, PLAY_PACK_NUM);
}



void DmaPlayWriteRight(void)
{
    int i;
    s16 *pdest;
    s16 *psrc;
    
    if (DMA_GetCurrentMemoryTarget(DMA1_Stream4) == 0)
    {
        pdest = (s16 *)(DmaPlayMem1);
    }
    else
    {
        pdest = (s16 *)(DmaPlayMem0);
    }
    
    psrc = (s16 *)(pPlayRightFifo + (PlayRightConsumeIndex * PLAY_PACK_SIZE));
    PlayRightConsumeIndex = IndexAdd1(PlayRightConsumeIndex, PLAY_PACK_NUM);
    
    for (i = 0; i < DMAPLAY_PACK_SIZE / 4; i++)
    {
        *(pdest + 2 * i + 1) = *(psrc + i);
    }
}



/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////



void I2s3_Init(void)
{
    I2S_InitTypeDef I2S_InitStructure;
    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    /* CODEC_I2S peripheral configuration */
    SPI_I2S_DeInit(SPI3);
    I2S_InitStructure.I2S_AudioFreq = 44100;
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
    I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    /* Initialize the I2S peripheral with the structure above */
    I2S_Init(SPI3, &I2S_InitStructure);
    /* The I2S peripheral will be enabled only in the EVAL_AUDIO_Play() function
       or by user functions if DMA mode not enabled */
    I2S_Cmd(SPI3, ENABLE);
}


void I2s3Down(void)
{
    I2S_Cmd(SPI3, DISABLE);
    /* Enable the I2S DMA Stream*/
    DMA_Cmd(DMA1_Stream2, DISABLE);
    /* Enable the I2S DMA request */
    SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Rx, DISABLE);
}


void I2s3Up(void)
{
    I2S_Cmd(SPI3, ENABLE);
    /* Enable the I2S DMA Stream*/
    DMA_Cmd(DMA1_Stream2, ENABLE);
    /* Enable the I2S DMA request */
    SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Rx, ENABLE);
}




void DmaListen_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the DMA clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    /* Configure the DMA Stream */
    DMA_Cmd(DMA1_Stream2, DISABLE);
    DMA_DeInit(DMA1_Stream2);
    DMA_DoubleBufferModeConfig(DMA1_Stream2, (u32)DmaListenMem1, DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA1_Stream2, ENABLE);
    /* Set the parameters to be configured */
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40003C0C;
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)DmaListenMem0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = (u32)(DMALISTEN_PACK_SIZE / 2);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    //      DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream2, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);
    DMA_ITConfig(DMA1_Stream2, DMA_IT_HT, ENABLE);
    //  DMA_ITConfig(AUDIO_MAL_DMA_STREAM, DMA_IT_HT, ENABLE);
    //  DMA_ITConfig(AUDIO_MAL_DMA_STREAM, DMA_IT_TE | DMA_IT_FE | DMA_IT_DME, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	/* Enable the I2S DMA Stream*/
	DMA_Cmd(DMA1_Stream2, ENABLE);
	/* Enable the I2S DMA request */
	SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Rx, ENABLE);
}





void DmaListen_Isr(void)
{
    Debuger = Debuger;
    
    if (DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2) == SET)
    {
        DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
        DmaListenUpLoadLeft();
        DmaListenUpLoadRight();
        Debuger = Debuger;
    }
    
    if (DMA_GetITStatus(DMA1_Stream2, DMA_IT_HTIF2) == SET)
    {
        DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_HTIF2);
        Debuger = Debuger;
    }
}


void DmaListenUpLoadLeft(void)
{
    int i;
    s16 *pdest;
    s16 *psrc;
    
    if (DMA_GetCurrentMemoryTarget(DMA1_Stream2) == 0)
    {
        psrc = (s16 *)(DmaListenMem1);
    }
    else
    {
        psrc = (s16 *)(DmaListenMem0);
    }
    
    pdest = (s16 *)(pListenLeftFifo + (ListenLeftProduceIndex * LISTEN_PACK_SIZE));
    ListenLeftProduceIndex = IndexAdd1(ListenLeftProduceIndex, LISTEN_PACK_NUM);
    
    for (i = 0; i < DMALISTEN_PACK_SIZE / 4; i++)
    {
        *(pdest + i) = *(psrc + 2 * i);
    }
    
    ListenLeftFlag = 1;
}



void DmaListenUpLoadRight(void)
{
    int i;
    s16 *pdest;
    s16 *psrc;
    
    if (DMA_GetCurrentMemoryTarget(DMA1_Stream2) == 0)
    {
        psrc = (s16 *)(DmaListenMem1);
    }
    else
    {
        psrc = (s16 *)(DmaListenMem0);
    }
    
    pdest = (s16 *)(pListenRightFifo + (ListenRightProduceIndex * LISTEN_PACK_SIZE));
    ListenRightProduceIndex = IndexAdd1(ListenRightProduceIndex, LISTEN_PACK_NUM);
    
    for (i = 0; i < DMALISTEN_PACK_SIZE / 4; i++)
    {
        *(pdest + i) = *(psrc + 2 * i + 1);
    }
    
    ListenRightFlag = 1;
}



void I2sOff(void)
{
    I2s2Down();
    I2s3Down();
}




